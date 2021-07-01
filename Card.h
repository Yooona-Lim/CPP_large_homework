//
// Created by 漠北残月 on 2021/6/21.
//
#include "Student.h"
#include "Canteen.h"

#ifndef LARGE_HOMEWORK4_0_CARD_H
#define LARGE_HOMEWORK4_0_CARD_H
class Card{
private:
    char id[15];
    char card_id[20];
    int amount;
    char record[3][25];//消费记录
public:
    void set(char*);    //设置学号（通过传参），卡号，学号。
    void insert_record(const char[],int);
    void set_deposit_amount(int);   //更改金额
    void add_new_card(Card&);   //添加卡
    void delete_special_card(Student&);    //删除特定的卡(带上学生)
    void show_all_cards();     //展示所有的卡(卡号和金额)
    void search_card(Student&,char*);     //寻找并输出卡
    void deposit();    //存钱
    void deduct_money(char*,Canteen&,fstream&,int);   //扣钱
    void set_record(fstream&,Canteen&,int);   //设置消费记录
    void search_record(char*);    //寻找消费记录
    bool search_account(char *, fstream &);  //搜索、判断账户是否存在
    void sort_amount();//按金额排序，用动态数组.


    int return_amount() const;

    class None_people:exception{};
    class Exist_people:exception{};
    class Money:exception{};
    //抛出异常,按照编译器的指示继承了exception，不继承也可以跑，但是警告看着难受
};
#endif //LARGE_HOMEWORK4_0_CARD_H
