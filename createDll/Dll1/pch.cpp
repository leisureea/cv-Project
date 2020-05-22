// pch.cpp: 与预编译标头对应的源文件
#include "pch.h"


MyClass::MyClass() {}
MyClass::~MyClass() {}

void MyClass::show_img()
{
    std::cout << "1" << endl;
    Mat img = imread("1.jpg", 1);
    if (img.empty())
    {
        std::cout << "图片打开失败" << endl;
    }
    imshow("he", img);
    waitKey(0);
}

void func()
{
    cout << "2" << endl;
}

