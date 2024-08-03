#include<iostream>
#include<memory>
using namespace std;
class Person
{
public:
	int m_num;
	Person(int num)
	{
		cout << "���͹��캯��" << num << endl;

	}
	Person()
	{
		cout << "�޲ι��캯��" << endl;
	}
	Person(string str)
	{
		cout << "�ַ������캯��" << str << endl;
	}
	~Person()
	{
		cout<<"��������"<<endl;
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

//�����Լ���װһ�������,����
template<class T>
shared_ptr<T> make_share_array(int size)
{
	return shared_ptr<T>(new T[size], default_delete<T[]>);
}


int main6()
{
	//ͨ�����캯����ʼ��
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1 use_count:" << ptr1.use_count() << endl;
	//ͨ���ƶ������ʼ��
	shared_ptr<int> ptr2 = move(ptr1);
	cout << "ptr1 use_count:" << ptr1.use_count() << endl;
	cout << "ptr2 use_count:" << ptr2.use_count() << endl;
	//ͨ�����������ʼ��
	shared_ptr<int> ptr3 = ptr2;
	cout << "ptr2 use_count:" << ptr2.use_count() << endl;
	cout << "ptr3 use_count:" << ptr3.use_count() << endl;
	//ͨ��make_shared��ʼ��
	shared_ptr<int> ptr4 = make_shared<int>(8);
	shared_ptr<Person> ptr5 = make_shared<Person>(9);
	shared_ptr<Person> ptr6 = make_shared<Person>("hello world");
	//ͨ��reset��ʼ��
	ptr6.reset();//���ã����û���Ϊ0
	cout << "ptr6 use_count:" << ptr6.use_count() << endl;

	ptr5.reset(new Person());//�Ȱ�ԭ������Ķ������������ٹ����µ��ڴ�
	cout << "ptr5 use_count:" << ptr5.use_count() << endl;


	//����ָ��ʹ�÷�ʽ
	//��ȡԭʼָ��
	Person* p = ptr5.get();//get���ṩ��api�������õ����
	p->setValue(100);
	p->print();
	//ֱ��ʹ������ָ��
	ptr5->setValue(999);//���ù�����ڴ��Ӧ������ĺ������ü�ͷ����
	ptr5->print();

	//�ڶ�������Ϊɾ������ppp�����ɾ�����ѵ�һ����������ȥ�����������ⲿ���ڴ�
	shared_ptr<Person> ppp(new Person(100), [](Person* p) {
		cout << "========================" << endl;
		//�ͷ��ڴ�Ĳ���
		delete p;
	});

	//(C++11)���������Ĭ�ϵ�ɾ�������Զ�������������������飬������Ҫ�Լ�дɾ����
	shared_ptr<Person> p1(new Person[5], [](Person* t) {
		delete[]t;
	});


	cout << "===============" << endl;
	//ʹ��Ĭ�ϵ�ɾ����������������
	shared_ptr<Person> p2(new Person[5], default_delete<Person[]>());


	// ===================================
	//c++11�Ժ�����Ҳ�����Զ��ͷ��ڴ棬ֻҪָ�����������;�����
	shared_ptr<Person[]> pp1(new Person[6]);


	return 0;
}