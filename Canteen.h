//
// Created by 漠北残月 on 2021/6/21.
//
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#ifndef LARGE_HOMEWORK4_0_CANTEEN_H
#define LARGE_HOMEWORK4_0_CANTEEN_H
class Canteen{
private:
    char meal[20];
    int amount;
public:
    void add();//设置对象
    void set_meal_table();//把设置好的对象存进文件
    void show_price();//展示所有的价格
    char* meals(int);//返回文件的指定菜名
    int prices(int) const;//返回文件的指定价格
    void return_meal_and_price(int num,char* rec);//返回一条饭菜名及价格
};
#endif //LARGE_HOMEWORK4_0_CANTEEN_H
