//
// Created by 漠北残月 on 2021/6/21.
//
#include <iostream>
#include "Canteen.h"
using namespace std;

void Canteen::add()
{
    cout<<"请输入你要添加的菜名: ";
    cin>>meal;
    cout<<"请输入此菜的金额: ";
    cin>>amount;
}

void Canteen::set_meal_table() {
    fstream file("canteen.dat", ios::app | ios::binary);
    if (file.fail()) {
        cout << "打开食堂文件失败！！！" << endl;
        exit(0);
    }
    file.write((char *) this, sizeof(*this));
    file.flush();
    file.close();
    cout<<"添加成功！"<<endl;
}

void Canteen::show_price()
{
    fstream file("canteen.dat", ios::in | ios::binary);
    if (file.fail())
    {
        cout << "打开食堂文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);

    int i=0;
    while (!file.eof())
    {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        cout<<i+1<<". "<<meal<<" ￥: "<<amount<<endl;
        ++i;
    }
    cout<<endl;
    file.close();
}

char* Canteen::meals(int num)//返回菜名
{
    fstream file("canteen.dat", ios::in | ios::binary);
    if (file.fail())
    {
        cout << "打开食堂文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg((num-1) * sizeof(*this), ios::beg);
    file.read((char *) this, sizeof(*this));
    return meal;
}
int Canteen::prices(int num) const //返回价格
{
    fstream file("canteen.dat", ios::in | ios::binary);
    if (file.fail())
    {
        cout << "打开食堂文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg((num-1) * sizeof(*this), ios::beg);
    file.read((char *) this, sizeof(*this));
    return amount;
}

void Canteen::return_meal_and_price(int num,char* rec)
{
    fstream file("canteen.dat", ios::in | ios::binary);
    if (file.fail())
    {
        cout << "打开食堂文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg((num-1) * sizeof(*this), ios::beg);
    file.read((char *) this, sizeof(*this));

    char str[5],record[25];

    //将整型金额转换为字符串。
    itoa(amount,str,10);//(整型金额，字符金额，10进制)

    //把菜名存储在临时变量中
    strcpy(record,meal);

    //字符串拼接，并赋值。
    strcpy(rec, strcat(strcat(record, ":￥"), str) );
}
