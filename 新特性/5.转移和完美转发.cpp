#include<iostream>
#include<list>
#include<string>
using namespace std;
class Test2
{
public:
	int* m_num;
public:
	Test2() : m_num(new int(100))
	{
		cout << "构造函数" << m_num << endl;

	}
	Test2(const Test2& a) : m_num(new int(*a.m_num))
	{
		cout << "拷贝构造函数" << endl;
	}
	//移动构造函数  复用其它对象中的资源(堆内存)
	// m_num，浅拷贝
	Test2(Test2&& a) : m_num(a.m_num)
	{
		a.m_num = nullptr;
		cout << "移动构造" << endl;
	}
	~Test2()
	{
		cout << "析构" << endl;
		if (m_num != nullptr)
		{
			delete m_num;
			m_num = nullptr;
		}
	}

};
Test2 getK()
{
	return Test2();
}


template<typename T>
void printValue(T& t)
{
	cout << "l-value: " << t << endl;
}

template<typename T>
void printValue(T&& t)
{
	cout << "r-value: " << t << endl;
}

template<typename T>
void testForward(T&& v)
{
	printValue(v);//左值引用
	printValue(move(v));//move变为右值
	printValue(forward<T>(v));//forward变为左值

	cout << endl;
}


int main5()
{
	int&& a = 1;
	testForward(a);//传入右值引用，变为左值引用

	cout << endl;

	Test2 && t1 = getK();//t1是非右值
	Test2 && t2 = move(t1);//右值引用只能初始化右值，所以用move转换为右值

	list<string> ls1{
		"hello","world","nihao","shijie"
	};

	list<string> ls2 = move(ls1);//资源转移，而不是拷贝（实际上调用了移动构造函数）
	for (auto ll : ls1)cout << ll << ' ';
	cout << endl;
	for (auto ll : ls2)cout << ll << ' ';
	cout << endl;


	return 0;
}