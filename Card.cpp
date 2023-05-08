//
// Created by 漠北残月 on 2021/6/21.
//
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "Card.h"
#include "Canteen.h"
using namespace std;


void Card::set(char *s_id)
{
    strcpy(id, s_id); //传入学号，标识是哪个学生的卡
    cout << "请输入卡号:";
    cin >> card_id;
    //下面是要判断卡里面有没有重复的卡号
    cout << "请输入金额:";
    cin >> amount;
}

void Card::set_deposit_amount(int money) {
    amount += money;
}

void Card::insert_record(const char *rec, int i) {
    strcpy(record[i], rec);
}

void Card::add_new_card(Card& card2) {
    fstream file("card.dat", ios::app | ios::binary);//如果没有文件，就会自动创建文件
    file.close();

    file.open("card.dat", ios::in | ios::binary);
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    while (!file.eof())
    {
        file.read((char*)&card2, sizeof(card2));
        if (strcmp(this->card_id,card2.card_id)==0) //如果当前this的卡号和card2的卡号相同
        {
            file.close();
            throw Exist_people();   //如果卡类文件里面卡号存在且相同，就不再录入
        }
    }
    file.close();
    file.open("card.dat", ios::app | ios::binary);
    file.write((char *) this, sizeof(*this));
    file.flush();
    file.close();
}

void Card::delete_special_card(Student& stu)
{
    char deleteID[20];
    int flag = 1;

    //定义流文件对象，把第一个文件除要删除数据之外的数据全部复制过去
    fstream file("card.dat", ios::in | ios::binary);
    fstream new_file("cards.dat", ios::out | ios::binary);

    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    cout << "请输入删除的卡号: ";
    cin.ignore();
    cin.getline(deleteID, 20);

    stu.delete_student(deleteID);
    while (!file.eof())
    {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        if (strcmp(id, deleteID) == 0)
        {
            flag = 0;
            continue;
        }
        new_file.write((char *) this, sizeof(*this));
    }
    file.close();
    new_file.close();//两个都关了
    if (flag) {
        throw None_people();
    }
    else {

        if (remove("card.dat")==0)
        {
            if (rename("cards.dat","card.dat")==0)
            {
                cout<<"删除成功！"<<endl;
            }
        } else
            cout<<"删除饭卡文件失败"<<endl;
    }
}

void Card::show_all_cards() {
    fstream file("card.dat", ios::in | ios::binary);
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);

    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        cout << "  | 卡号:" << setw(10)<< setiosflags(ios::left)<< id << "  ";
        cout << "  | 金额:" << setw(10)<< setiosflags(ios::left)<< amount<<"|"<< endl;
    }
    cout << endl;
    file.close();
}

void Card::search_card(Student &stu, char *seekID) {
    fstream file("card.dat", ios::in | ios::binary);
    fstream files("student.dat", ios::in | ios::binary);
    if (file.fail() || files.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    int flag = 1;
    file.clear();
    file.seekg(0L, ios::beg);

    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;

        if (strcmp(id, seekID) == 0)
        {
            while (!files.eof())
            {
                files.read((char *) &stu, sizeof(stu));
                if (files.fail())
                    break;

                if (strcmp(id, stu.return_id()) == 0) {
                    cout << "  | 学号:" << setw(10)<< setiosflags(ios::left)<< stu.return_id() << "  ";
                    cout << "  | 姓名:" << setw(10)<< setiosflags(ios::left)<< stu.return_name() << "  ";
                    cout << "  | 专业:" << setw(10)<< setiosflags(ios::left)<< stu.return_major() << "  ";
                    cout << "  | 年级:" << setw(10)<< setiosflags(ios::left)<< stu.return_grade() << "  ";
                    cout << "  | 民族:" << setw(10)<< setiosflags(ios::left)<< stu.return_nation() << "  ";
                    if (strcmp(stu.return_nation(),"汉")!=0)
                        cout<<endl<<"少数民族可优先使用民族餐厅！";
                    flag = 0;
                    break;
                }
            }
            cout <<endl<< "  | 卡号:" << setw(10)<< setiosflags(ios::left)<< card_id << "  ";
            cout << "  | 金额:" << setw(10)<< setiosflags(ios::left)<< amount <<"|"<< endl<<endl;
            break;
        }
    }
    if (flag) {
        file.close();
        files.close();
        cout << "							查无此卡！" << endl << endl;
    }
    file.close();
    files.close();
}

void Card::deposit() {
    fstream file("card.dat", ios::in | ios::out | ios::binary);
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    char seekID[20];
    int money;
    int flag = 1;
    file.clear();
    file.seekg(0L, ios::beg);

    cout << "请输入卡号:";
    cin.ignore();
    cin.getline(seekID, 20);
    cout << "请输入充值金额:";
    cin >> money;

    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;

        if (strcmp(id, seekID) == 0) {
            cout << "找到充值的卡，尝试充值..." << endl;
            set_deposit_amount(money);
            file.seekp(-(sizeof(*this)), ios::cur);
            file.write((char *) this, sizeof(*this));
            flag = 0;
            cout << "充值成功！" << endl << "卡内余额为:" << amount << endl<<endl;
            break;
        }
    }
    if (flag) {
        cout << "查无此卡！！" << endl;
    }
    file.flush();
    file.close();
}

void Card::deduct_money(char *s_id, Canteen &canteen, fstream &file, int num) {


    cout << canteen.meals(num) << "价格为:￥" << canteen.prices(num) << endl; //返回吃的菜及价格
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);

    while (!file.eof())
    {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;

        if (strcmp(id, s_id) == 0) {

            if (amount<canteen.prices(num))//如果余额小于菜价
            {
                cout<<"你的余额为:"<<amount<<endl;
                throw Money();
            }

            file.seekp(-(sizeof(*this)), ios::cur);
            set_deposit_amount(-(canteen.prices(num)));
            file.write((char *) this, sizeof(*this));

            cout << "扣钱成功！" << endl;
            file.seekp(-(sizeof(*this)), ios::cur);
            file.read((char *) this, sizeof(*this));
            cout << "你的余额还剩:" << amount << endl<<endl;
            break;
        }
    }
}

void Card::set_record(fstream &file, Canteen &canteen, int num) {
    for (int i = 2; i > 0; --i)
    {
        insert_record(record[i-1], i);    //数组移动
    }
    char rec[25];

    //传进去 存储记录 的字符串rec，把改好的数据存到rec里
    canteen.return_meal_and_price(num,rec);

    insert_record(rec, 0);    //rec记录插入首部

    file.seekp(-(sizeof(*this)), ios::cur);
    file.write((char *) this, sizeof(*this));

    file.seekp(-(sizeof(*this)), ios::cur);
    file.read((char *) this, sizeof(*this));

    cout << "消费记录为:";
    for (int i = 0; i < 3; ++i) {
        cout << record[i] << "  ";
    }
    cout<<endl<<endl;
    file.flush();
    file.close();
}

void Card::search_record( char *account) {
    fstream file("card.dat", ios::in | ios::binary);
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    file.clear();
    file.seekg(0L, ios::beg);
    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;

        if (strcmp(id, account) == 0) {
            cout << "消费记录为:";
            for (int i = 0; i < 3; ++i) {
                cout << record[i] << "  ";
            }
            cout<<endl<<endl;
        }
    }
}

bool Card::search_account(char *account, fstream &file) {

    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);

    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;

        if (strcmp(id, account) == 0) {
            file.flush();
            file.close();
            return true;    //注意这时候car存的信息是，卡号相同，也就是要操作的那个信息
        }
    }
    cout << "文件中不存在这张卡，请添加。" << endl;
    file.flush();
    file.close();
    return false;
}

bool cmp(Card x,Card y)     //排序的布尔函数
{
    return x.return_amount()>y.return_amount();
}

void Card::sort_amount()
{
    fstream file("card.dat", ios::in | ios::out | ios::binary);
    if (file.fail())
    {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);
    int size=0;
    while (!file.eof()) //循环判断有多少张卡
    {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        ++size;
    }
    cout<<"共有:"<<size<<"张卡"<<endl;

    Card* p=new Card[size];//申请相应的对象数组
    cout<<"申请对象数组成功"<<endl;

    file.clear();
    file.seekg(0L, ios::beg);
    int i=0;
    while (!file.eof())
    {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        p[i]=*this;
        ++i;
    }
    cout<<"赋值成功"<<endl;
    sort(p,p+size,cmp);

    for (int j = 0; j < size; ++j) {
        cout<<j+1<<". 卡号:"<<p[j].card_id<<"  金额:"<<p[j].amount<<endl;
    }
    cout<<endl;

    delete []p;
    cout<<"删除数组成功！"<<endl<<endl;
}




int Card::return_amount() const {
    return amount;
}

