#ifndef PCH_H_
#define PCH_H_

#include<iostream>
#include<opencv2/highgui.hpp>
using namespace std;
using namespace cv;

#ifdef SERVERDLL_EXPORTS
#define SERVERDLL_API __declspec(dllexport)
#else
#define SERVERDLL_API __declspec(dllimport)
#endif

class SERVERDLL_API MyClass
{
public:
	MyClass();
	~MyClass();
	void show_img();
private:

};

SERVERDLL_API void func();

#endif