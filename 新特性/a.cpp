#include<iostream>
using namespace std;

template<class T = int, T t = 100>
class Person
{
public:
	void func(int a, int b)
	{
		cout << a << "sds " << b << endl;
	}
	void func()
	{
		cout << "asdas" << endl;
	}
};

class son : public Person<>
{
public:
	using Person::func;
	void func()
	{
		cout << "son" << endl;
	}
};

template<typename T, typename U>
auto add(T t, U u)
{
	return t + u;
}
int maina()
{
	int a = 10;
	Person<> p;
	son s;
	s.func(1,2);
	double b = 2.3;
	auto c = add(a, b);
	cout << c << endl;

	return 0;
}