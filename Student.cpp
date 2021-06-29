//
// Created by 漠北残月 on 2021/6/21.
//
#include <iostream>
#include <cstring>
#include <iomanip>
#include<fstream>
#include <cstdio>
#include "Student.h"

using namespace std;

void Student::set() {
    cout << "请输入学号:";
    cin >> id;
    cout << "请输入姓名:";
    cin >> name;
    cout << "请输入专业:";
    cin >> major;
    cout << "请输入年级:";
    cin >> grade;
    cout << "请输入民族:";
    cin >> nation;
}

void Student::add_new_student(Student &stu, Student &stu2) {

    fstream file("student.dat", ios::app | ios::binary);//如果没有文件，就会自动创建文件
    file.close();

    file.open("student.dat", ios::in | ios::binary);
    if (file.fail()){
        cout << "打开学生文件失败！！！" << endl;
        exit(0);
    }

    while (!file.eof())
    {
        file.read((char *) &stu2, sizeof(stu2));

        //如果之前有办过卡
        if (strcmp(stu2.id, stu.id) == 0) {
            file.close();
            throw Exist_people();
        }
    }
    file.close();

    file.open("student.dat", ios::app | ios::binary);
    file.write((char *) &stu, sizeof(stu));
    file.close();
}

void Student::delete_student(char *names) {
    int flag = 1;
    //定义文件流对象，把第一个文件除要删除数据之外的数据全部复制过去
    fstream file("student.dat", ios::in | ios::binary);
    fstream new_file("students.dat", ios::out | ios::binary);
    if (file.fail()) {
        cout << "打开饭卡文件失败！！！" << endl;
        exit(0);
    }

    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        if (strcmp(id, names) == 0) {
            flag = 0;
            continue;
        }
        new_file.write((char *) this, sizeof(*this));
    }
    file.close();
    new_file.close();
    if (flag) {
        throw None_people();
    } else {

        if (remove("student.dat")==0)
        {
            if (rename("students.dat","student.dat")==0)
            {
                cout<<"删除成功！"<<endl;
            }
        } else
            cout<<"删除学生文件失败"<<endl;
    }
}

void Student::show_all_students() {
    fstream file("student.dat", ios::in | ios::binary);
    if (file.fail()) {
        cout << "打开学生文件失败！！！" << endl;
        exit(0);
    }
    file.clear();
    file.seekg(0L, ios::beg);


    while (!file.eof()) {
        file.read((char *) this, sizeof(*this));
        if (file.fail())
            break;
        cout << "  | 学号:" << setw(10) << setiosflags(ios::left) << id << "  ";
        cout << "  | 姓名:" << setw(10) << setiosflags(ios::left) << name << "  ";
        cout << "  | 专业:" << setw(10) << setiosflags(ios::left) << major << "  ";
        cout << "  | 年级:" << setw(10) << setiosflags(ios::left) << grade << "  ";
        cout << "  | 民族:" << setw(10) << setiosflags(ios::left) << nation << "|" << endl;
    }
    cout << endl;
    file.close();
}

char *Student::return_id() {
    return id;
}

char *Student::return_name() {
    return name;
}

char *Student::return_major() {
    return major;
}

char *Student::return_grade() {
    return grade;
}

char *Student::return_nation() {
    return nation;
}

