//
// Created by 漠北残月 on 2021/6/21.
//
using namespace std;
#ifndef LARGE_HOMEWORK4_0_STUDENT_H
#define LARGE_HOMEWORK4_0_STUDENT_H
class Student {
protected:
    char id[15]; //学号
    char name[20];  //姓名
    char major[20];  //专业
    char grade[8];  //年级
    char nation[14];  //民族
public:
    void set();//设置对象函数成员

    void add_new_student(Student &, Student &);//添加学生的信息至文件里
    void delete_student(char* names);
    void show_all_students();//展示所有的学生
    char *return_id();
    char *return_name();
    char *return_major();
    char *return_grade();
    char *return_nation();

    class None_people : exception {};
    class Exist_people : exception {};
    //抛出异常,按照编译器的指示继承了exception，不继承也可以跑，但是警告看着难受
};
#endif //LARGE_HOMEWORK4_0_STUDENT_H
