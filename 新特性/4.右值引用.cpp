#include<iostream>
using namespace std;
//右值引用的作用：延长模块内存的存活时间
//可以让临时空间保存下来，提高系统效率
class Test
{
public:
	int* m_num;
public:
	Test() : m_num(new int(100))
	{
		cout << "构造函数" << m_num << endl;
		
	}
	Test(const Test& a) : m_num(new int(*a.m_num))
	{
		cout << "拷贝构造函数" << endl;
	}
	//移动构造函数  复用其它对象中的资源(堆内存)
	// m_num，浅拷贝
	Test(Test&& a) : m_num(a.m_num)
	{
		a.m_num = nullptr;
		cout << "移动构造" << endl;
	}
	~Test()
	{
		cout << "析构" << endl;
		if (m_num != nullptr)
		{
			delete m_num;
			m_num = nullptr;
		}
	}

};
Test&& getObj()//将亡值，右值的一种
{
	//Test t;
	return Test();
}

template<class T>
void f1(T&& param);//需要根据传入的类型进行推导
template<class T>
int f(const T&& t);//本身是右值引用，推导结果也是右值引用

//通过右值推导T&&或者auto&&得到的是一个右值引用类型
//通过非右值(右值引用、左值、左值引用、常量右值引用、常量左值引用）推导得到的是一个左值引用类型

int main4()
{
	//右侧的对象是临时对象，属于右值，会调用移动构造函数
	Test t = getObj();
	cout << "666" << endl;

	int a = 2;
	auto&& x = 1;//auto&&推导，右值推导的结果是右值
	auto&& y = a;//左值推导是左值引用
	return 0;
}