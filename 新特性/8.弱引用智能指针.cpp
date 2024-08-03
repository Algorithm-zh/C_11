#include<iostream>
#include<memory>
using namespace std;
//weak_ptr,���shared_ptr��

/*
	shared_ptrʹ�õ�ע�����
	1.����ʹ��һ��ԭʼ��ַ��ʼ�������������ָ��(�ᵼ���ظ�������
	2.�������ܷ��ع�����this�Ĺ�������ָ�����(�ᵼ���ظ�������
	3.��������ָ�벻��ѭ������

*/

class Animal:public enable_shared_from_this<Animal>
{
public:
	shared_ptr<Animal> getSharedPtr()
	{
		//return shared_ptr<Animal>(this);//����ע������2
		//���ع����ŵ�ǰ���������ָ����󣬱���̳�enable_shared_from_this��
		//Ȼ���������е�shared_from_this���з���
		return shared_from_this();
	}
	~Animal()
	{
		cout << "Animal����" << endl;
	}

};
struct TA;
struct TB;
struct TA
{
	shared_ptr<TB> bptr;
	//weak_ptr<TB> bptr;
	~TA()
	{
		cout << "TA����" << endl;
	}
};
struct TB
{
	shared_ptr<TA> aptr;
	~TB()
	{
		cout << "TB����" << endl;
	}
};
void testPtr()
{
	//�γ��˻�·���а�����ϵ��ѭ������,���յ����޷�����
	shared_ptr<TA> ap(new TA);
	shared_ptr<TB> bp(new TB);
	cout << "TA use_count:" << ap.use_count() << endl;
	cout << "TB use_count:" << bp.use_count() << endl;

	ap->bptr = bp;
	bp->aptr = ap;
	cout << "TA use_count:" << ap.use_count() << endl;
	cout << "TB use_count:" << bp.use_count() << endl;
}


int main()
{
	Animal* p = new Animal;
	shared_ptr<Animal> ptr1(p);
	//shared_ptr<Animal> ptr2(p);//����ע������1
	shared_ptr<Animal> ptr2 = ptr1;//��ȷ

	shared_ptr<Animal> sp1(new Animal);
	cout << "use_count: " << sp1.use_count() << endl;
	shared_ptr<Animal> sp2 = sp1->getSharedPtr();
	cout << "use_count: " << sp2.use_count() << endl;


	testPtr();
	return 0;
}
