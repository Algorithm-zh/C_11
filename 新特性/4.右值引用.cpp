#include<iostream>
using namespace std;
//��ֵ���õ����ã��ӳ�ģ���ڴ�Ĵ��ʱ��
//��������ʱ�ռ䱣�����������ϵͳЧ��
class Test
{
public:
	int* m_num;
public:
	Test() : m_num(new int(100))
	{
		cout << "���캯��" << m_num << endl;
		
	}
	Test(const Test& a) : m_num(new int(*a.m_num))
	{
		cout << "�������캯��" << endl;
	}
	//�ƶ����캯��  �������������е���Դ(���ڴ�)
	// m_num��ǳ����
	Test(Test&& a) : m_num(a.m_num)
	{
		a.m_num = nullptr;
		cout << "�ƶ�����" << endl;
	}
	~Test()
	{
		cout << "����" << endl;
		if (m_num != nullptr)
		{
			delete m_num;
			m_num = nullptr;
		}
	}

};
Test&& getObj()//����ֵ����ֵ��һ��
{
	//Test t;
	return Test();
}

template<class T>
void f1(T&& param);//��Ҫ���ݴ�������ͽ����Ƶ�
template<class T>
int f(const T&& t);//��������ֵ���ã��Ƶ����Ҳ����ֵ����

//ͨ����ֵ�Ƶ�T&&����auto&&�õ�����һ����ֵ��������
//ͨ������ֵ(��ֵ���á���ֵ����ֵ���á�������ֵ���á�������ֵ���ã��Ƶ��õ�����һ����ֵ��������

int main4()
{
	//�Ҳ�Ķ�������ʱ����������ֵ��������ƶ����캯��
	Test t = getObj();
	cout << "666" << endl;

	int a = 2;
	auto&& x = 1;//auto&&�Ƶ�����ֵ�Ƶ��Ľ������ֵ
	auto&& y = a;//��ֵ�Ƶ�����ֵ����
	return 0;
}