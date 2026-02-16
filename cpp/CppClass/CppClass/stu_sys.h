#ifndef STU_SYS_H
#define STU_SYS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 学生类
class Student {
private:
    string name;   // 姓名
    string id;     // 学号
    double score;  // 成绩

public:
    // 构造函数
    Student(string n, string i, double s) : name(n), id(i), score(s) {}

    // 显示学生信息
    void display() const {
        cout << "学号: " << id << "\t姓名: " << name << "\t成绩: " << score << endl;
    }

    // 获取成绩（用于计算平均分）
    double getScore() const { return score; }
};

int stu_sys();

#endif // STU_SYS_H