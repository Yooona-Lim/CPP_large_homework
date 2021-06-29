//3.0终于实现了，所有功能终于完成了。
//所以3.0被封印了，设为只读。
//但是产品经理有新要求......
//为了不影响原程序，特意开了新版本折腾......

//warning!!!!! 此系统的CARD类的deduct函数，只能在Clion(编译器:mingw64)下运行，VS对于文件指针的定位似乎不能回调。
//若要用，则更改成用变量计数器定位的指针即可。

//版本更新:
// 1.原来类里面自己的对象可以直接点乘访问，修改了相应的代码以减少代码量
// 2.添加了新功能:能增加食堂里的饭菜。又涉及到文件的问题，有点头秃。。。但还是做出来了
// 3.特大改动，类里面传进去的对象全部用this代替，之前的想法出了问题，类里面是可以直接操作的。
//比如 file.write((char*)&card,sizeof(card)),完全可以写成((char*)this,sizeof(*this))
// 4.美化了管理员窗口界面，具体请运行观看
// 5.新增了自动创建文件的函数，免去了要去根目录底下手动建文件
// 6.删除函数的优化，复制完文件直接删除并改名，删除用时减半。

//  (1.对卡号和学号的判断：如果有，就抛出异常：已存在卡号或者学号！
//  (2.对余额的判断：如果钱不够，就抛出异常：余额不足，请先充值！
//  (3.对查询和删除的判断：如果找不到人，就抛出异常：查无此人！
#include <iostream>
#include "Student.h"
#include "Card.h"
#include "Canteen.h"
using namespace std;
//创建三个类的对象
Student student, student2;
Card card,card2;
Canteen canteen;

char account[20];//账号
char password[7];//密码

void command_word()
{
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout << " 1.办新饭卡 2.注销饭卡 "
            "3.展示所有学生 4.展示所有饭卡 "
            "5.查询指定饭卡 6.查询消费记录 "<<endl<<
            "       7.余额充值 8.学生余额排序 9.展示食堂饭菜 "
            "10.添加食堂饭菜 11.退出 "<<endl
         << endl<< "请输入你要进行的操作:";
}

void administrator_surface() {
    int choice;//用于选择
    while (true)
    {
        command_word();//要求的命令输出屏幕，做成函数，便于管理

        cin >> choice;
        switch (choice) {
            case 1:
                student.set();
                card.set(student.return_id());

                //后面两个函数要用的数据都在上面设置了，保存在临时的对象里面。
                try {
                    student.add_new_student(student, student2);
                    card.add_new_card(card2);
                }
                catch (Student::Exist_people &){
                    cout<<"已存在此学生！"<<endl;
                }
                catch (Card::Exist_people &){
                    cout<<"已存在卡号！"<<endl;
                }

                break;
            case 2:
                try
                {
                    card.delete_special_card(student);
                }
                catch (Card::None_people &) {
                    cout << "查无此卡！" << endl;
                }
                break;
            case 3:
                student.show_all_students();
                break;
            case 4:
                card.show_all_cards();
                break;
            case 5:
                char seekID[20];
                cout << "请输入卡号: ";
                cin.ignore();
                cin >> seekID;
                card.search_card( student, seekID);
                break;
            case 6:
                char seek[20];
                cout << "请输入卡号: ";
                cin.ignore();
                cin>>seek;
                card.search_record(seek);
                break;
            case 7:
                card.deposit();
                break;
            case 8:
                card.sort_amount();
                break;
            case 9:
                canteen.show_price();
                break;
            case 10:
                canteen.add();
                canteen.set_meal_table();
                break;
            case 11:
                exit(0);
            default:
                cout << "请输入正确的命令！" << endl;
                break;
        }
    }
}

void student_surface(char *accounts) {
    fstream file("card.dat", ios::in | ios::binary);
    if (card.search_account(accounts, file))//if框内为布尔函数，存在该学生返回true，否则false.
    {
        cout << "请输入你的密码:";
        cin >> password;
        if (strcmp(password, "123456") == 0)
        {
            card.search_card( student, accounts);//找卡并输出信息
            char choice;
            while (true) {
                cout << endl << "1.刷卡买饭 2.查询消费记录 3.退出" << endl;
                cin >> choice;
                switch (choice) {
                    case '1':
                        canteen.show_price();
                        cout << "吃什么？（输入序号）" << endl;
                        int num;
                        cin >> num;

                        file.open("card.dat", ios::in | ios::out | ios::binary);
                        try {
                            card.deduct_money(accounts,  canteen, file, num);
                            card.set_record(file, canteen, num);
                        } catch (Card::Money &) {
                            cout<<"余额不足，请先充值！"<<endl;
                        }
                        break;
                    case '2':
                        card.search_record(accounts);
                        break;
                    case '3':
                        exit(0);
                    default:
                        cout << "请输入正确的操作！" << endl;
                }
            }
        } else
            cout<<"密码错误！"<<endl;
    } else
        cout<<"不存在该用户！"<<endl;
}

int main() {
    cout << "欢迎来到学生饭卡管理系统！" << endl << "请输入账号(学生账号为其卡号):";
    cin >> account;
    if (strcmp(account, "admin") == 0)//判断输入字符是否为管理员，否则跳到学生的检索
    {
        cout << "请输入管理员密码:";
        cin >> password;
        if (strcmp(password, "admin") == 0)
        {
            administrator_surface();//密码正确，执行管理员函数
        } else
            cout<<"密码错误！"<<endl;
    }
    else {
        student_surface(account);
    }
}

