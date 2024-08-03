#include<iostream>
#include<list>
#include <functional>
using namespace std;

//lambda本质是一个仿函数
void func(int x, int y)
{
	int a = 7;
	int b = 9;
	[=,&x]()mutable{//除了x其他都是拷贝
		int c = a;
		int d = x;
		b++;//加上mutable就可以修改,但是还是拷贝的副本，所以不影响外部b的值
	}();//加小括号调用
}


int main3()
{
	func(1, 2);

	//返回值后置，返回值比较复杂的时候需要指名返回类型
	auto f1 = []() -> list<int>
		{
			return { 1, 2 };
		};
	using ptr = void(*)(int);

	//当[]中啥都没有时，可以看作函数指针
	ptr p1 = [](int x)
		{
			cout << x << endl;
		};

	p1(444);

	//[]有东西时只能是一个仿函数,可以用包装器包装或者绑定器绑定
	function<void(int)> f2 = [=](int x)
		{
			cout << x << endl;
		};
	f2(555);

	function<void(int)> f3 = bind([=](int x)
		{
			cout << x << endl;
		}, placeholders::_1);
	f3(666);

	//直接用auto
	auto a = [=](int x)
		{
			cout << x << endl;
		};
	a(2);

	



	return 0;
}