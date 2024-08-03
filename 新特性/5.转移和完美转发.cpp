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
		cout << "���캯��" << m_num << endl;

	}
	Test2(const Test2& a) : m_num(new int(*a.m_num))
	{
		cout << "�������캯��" << endl;
	}
	//�ƶ����캯��  �������������е���Դ(���ڴ�)
	// m_num��ǳ����
	Test2(Test2&& a) : m_num(a.m_num)
	{
		a.m_num = nullptr;
		cout << "�ƶ�����" << endl;
	}
	~Test2()
	{
		cout << "����" << endl;
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
	printValue(v);//��ֵ����
	printValue(move(v));//move��Ϊ��ֵ
	printValue(forward<T>(v));//forward��Ϊ��ֵ

	cout << endl;
}


int main5()
{
	int&& a = 1;
	testForward(a);//������ֵ���ã���Ϊ��ֵ����

	cout << endl;

	Test2 && t1 = getK();//t1�Ƿ���ֵ
	Test2 && t2 = move(t1);//��ֵ����ֻ�ܳ�ʼ����ֵ��������moveת��Ϊ��ֵ

	list<string> ls1{
		"hello","world","nihao","shijie"
	};

	list<string> ls2 = move(ls1);//��Դת�ƣ������ǿ�����ʵ���ϵ������ƶ����캯����
	for (auto ll : ls1)cout << ll << ' ';
	cout << endl;
	for (auto ll : ls2)cout << ll << ' ';
	cout << endl;


	return 0;
}