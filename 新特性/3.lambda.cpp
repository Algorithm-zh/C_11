#include<iostream>
#include<list>
#include <functional>
using namespace std;

//lambda������һ���º���
void func(int x, int y)
{
	int a = 7;
	int b = 9;
	[=,&x]()mutable{//����x�������ǿ���
		int c = a;
		int d = x;
		b++;//����mutable�Ϳ����޸�,���ǻ��ǿ����ĸ��������Բ�Ӱ���ⲿb��ֵ
	}();//��С���ŵ���
}


int main3()
{
	func(1, 2);

	//����ֵ���ã�����ֵ�Ƚϸ��ӵ�ʱ����Ҫָ����������
	auto f1 = []() -> list<int>
		{
			return { 1, 2 };
		};
	using ptr = void(*)(int);

	//��[]��ɶ��û��ʱ�����Կ�������ָ��
	ptr p1 = [](int x)
		{
			cout << x << endl;
		};

	p1(444);

	//[]�ж���ʱֻ����һ���º���,�����ð�װ����װ���߰�����
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

	//ֱ����auto
	auto a = [=](int x)
		{
			cout << x << endl;
		};
	a(2);

	



	return 0;
}