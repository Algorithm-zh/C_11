#include<iostream>
#include<functional>
using namespace std;
/*
	1.����ָ��
	2.����operator()��Ա�����������(�º���)
	3.�ɱ�ת��Ϊ����ָ��������
	4.���Ա����ָ��������Աָ��
*/
void print(int num, string name)
{
	cout << "id: " << num << ", name��" << name << endl;
}
//1.����ָ�룬���ɵ��ö���
using funcptr = void(*)(int, string);

class A
{
public:
	A(const function<void(int, string)>& f) : callback(f)
	{}
	void notify(int id, string name) {
		callback(id, name);//����ͨ�����캯���õ��ĺ���ָ��
	}
private:
	function<void(int, string)> callback;
};


class Test
{
public:
	int m_id;
	//2.����operator()
	void operator()(string msg) {
		cout << "�º��� " << msg << endl;
	}
	//3.�������ת��Ϊ����ָ��
	operator funcptr() {
		return world;//����ʵ�ʵĺ��������ͺ�funcptrһ��������ڵ�ַ
	};
	//���ڶ���δ�������֮ǰ������
	void hello(int a, string s)
	{
		cout << "hello " << s << endl;
	}
	//������
	static void world(int a, string s)
	{
		cout << "world " << s << endl;
	}
};

int main1()
{
#if 0
	Test t;
	t("�º���111");//2.ʹ�����ص�С����

	Test tt;
	tt(19, "aaa");//3.��tt����ת��Ϊ�˺���ָ��

	//4.���Ա����ָ��(ָ��̬����)
	funcptr f = Test::world;

	//4.����һ��ָ�����Ա�ĺ���ָ��
	using fptr = void(Test::*)(int, string);
	fptr f1 = Test::hello;

	//4.��ĳ�Աָ��(����)����������Ϊ�������ã�
	using ptr1 = int Test::*;
	ptr1 pt = &Test::m_id;

	//test���͵Ķ���
	Test ttt;
	(ttt.*f1)(1,"f1");

	ttt.*pt = 10;
#endif

	//1����װ��ͨ����
	function<void(int, string)> f1 = print;
	
	//2����װ��ľ�̬����
	function<void(int, string)> f2 = Test::world;

	//3, ��װ�º���
	Test ta;
	function<void(string)> f3 = ta;

	//4����װת��Ϊ����ָ��Ķ���(��world��
	Test tb;
	function<void(int, string)> f4 = tb;

	//4����װ��ĳ�Ա����(�Ǿ�̬)����hello��
	Test t1;
	function<void(int, string)> f5 = bind(&Test::hello, &t1, 5, "f5");

	//4���Ȱ��ٰ�װ���Ա�������Ȱ󶨳ɱ�ɷº������º����ǿɵ��ö��󣬿��԰�װ���������Ϳ���ʹ�õ��õķ�ʽ��
	Test t2;
	function<int& (void)> f6 = bind(&Test::m_id, t2);
	f6() = 6;

	//����
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