#include<iostream>
#include<functional>
using namespace std;
/*
	1.函数指针
	2.具有operator()成员函数的类对象(仿函数)
	3.可被转换为函数指针的类对象
	4.类成员函数指针或者类成员指针
*/
void print(int num, string name)
{
	cout << "id: " << num << ", name：" << name << endl;
}
//1.函数指针，（可调用对象）
using funcptr = void(*)(int, string);

class A
{
public:
	A(const function<void(int, string)>& f) : callback(f)
	{}
	void notify(int id, string name) {
		callback(id, name);//调用通过构造函数得到的函数指针
	}
private:
	function<void(int, string)> callback;
};


class Test
{
public:
	int m_id;
	//2.重载operator()
	void operator()(string msg) {
		cout << "仿函数 " << msg << endl;
	}
	//3.将类对象转换为函数指针
	operator funcptr() {
		return world;//返回实际的函数（类型和funcptr一样）的入口地址
	};
	//属于对象，未定义对象之前不存在
	void hello(int a, string s)
	{
		cout << "hello " << s << endl;
	}
	//属于类
	static void world(int a, string s)
	{
		cout << "world " << s << endl;
	}
};

int main1()
{
#if 0
	Test t;
	t("仿函数111");//2.使用重载的小括号

	Test tt;
	tt(19, "aaa");//3.将tt对象转换为了函数指针

	//4.类成员函数指针(指向静态函数)
	funcptr f = Test::world;

	//4.定义一个指向类成员的函数指针
	using fptr = void(Test::*)(int, string);
	fptr f1 = Test::hello;

	//4.类的成员指针(变量)，（不能作为函数调用）
	using ptr1 = int Test::*;
	ptr1 pt = &Test::m_id;

	//test类型的对象
	Test ttt;
	(ttt.*f1)(1,"f1");

	ttt.*pt = 10;
#endif

	//1，包装普通函数
	function<void(int, string)> f1 = print;
	
	//2，包装类的静态函数
	function<void(int, string)> f2 = Test::world;

	//3, 包装仿函数
	Test ta;
	function<void(string)> f3 = ta;

	//4，包装转换为函数指针的对象(调world）
	Test tb;
	function<void(int, string)> f4 = tb;

	//4，包装类的成员函数(非静态)（调hello）
	Test t1;
	function<void(int, string)> f5 = bind(&Test::hello, &t1, 5, "f5");

	//4，先绑定再包装类成员变量（先绑定成变成仿函数，仿函数是可调用对象，可以包装起来）（就可以使用调用的方式）
	Test t2;
	function<int& (void)> f6 = bind(&Test::m_id, t2);
	f6() = 6;

	//调用
	f1(1, "f1");
	f2(2, "f2");
	f3("f3");
	f4(4, "f4");
	f5(5,"hhahahhahaa");
	cout << f6() << endl;

	A aa(print);
	aa.notify(1, "aa");

	A ab(Test::world);
	ab.notify(2, "ab");

	A ac(tb);
	ac.notify(3, "ac");


	return 0;
}