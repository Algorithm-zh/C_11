#include<iostream>
#include<memory>
#include<functional>
using namespace std;
/*
	ֻ��һ����ռ����ָ�����ĳһ���ڴ�
*/
class Car
{
public:
	int m_num;
	Car(int num)
	{
		cout << "���͹��캯��" << num << endl;

	}
	Car()
	{
		cout << "�޲ι��캯��" << endl;
	}
	Car(string str)
	{
		cout << "�ַ������캯��" << str << endl;
	}
	~Car()
	{
		cout << "��������" << endl;
	}
	void setValue(int v)
	{
		m_num = v;
	}
	void print()
	{
		cout << "m_num : " << m_num << endl;
	}

};


int main7()
{
	
	//ͨ�����캯����ʼ��
	unique_ptr<int> ptr1(new int(2));

	//ͨ���ƶ������ʼ��
	unique_ptr<int> ptr2 = move(ptr1);//ֻ��ͨ��move�����ܸ���

	//ͨ��reset��ʼ��
	ptr2.reset(new int(8));

	//��ȡԭʼָ��
	unique_ptr<Car> ptr3(new Car(23));
	Car* p = ptr3.get();
	p->setValue(2);
	p->print();

	ptr3->setValue(3);
	ptr3->print();

	//��ռָ��ʹ��ɾ��������ָ��ɾ�������ͣ�����ֱ��ָ��ɾ����
	using funcptr = void(*)(Car*);//����һ������ָ������
	unique_ptr<Car, funcptr> ptr4(new Car("hello"), [](Car* p) {
		delete p;
		});

	//[]�Ӷ����Ͳ��ܿ��ɺ���ָ�룬ֻ���Ƿº��������Խ����ÿɵ��ö����װ����װ
	unique_ptr<Car, function<void(Car*)>> ptr5(new Car("hello"), [=](Car* p) {
		delete p;
		});

	//��ռ������ָ����Թ����������͵ĵ�ַ�����Զ��ͷ�
	unique_ptr<Car[]> ptr6(new Car[5]);


	return 0;
}
