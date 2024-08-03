#include<iostream>
#include<memory>
using namespace std;
//weak_ptr,检测shared_ptr，

/*
	shared_ptr使用的注意事项：
	1.不能使用一个原始地址初始化多个共享智能指针(会导致重复析构）
	2.函数不能返回管理了this的共享智能指针对象(会导致重复析构）
	3.共享智能指针不能循环引用

*/

class Animal:public enable_shared_from_this<Animal>
{
public:
	shared_ptr<Animal> getSharedPtr()
	{
		//return shared_ptr<Animal>(this);//错误，注意事项2
		//返回管理着当前对象的智能指针对象，必须继承enable_shared_from_this，
		//然后利用类中的shared_from_this进行返回
		return shared_from_this();
	}
	~Animal()
	{
		cout << "Animal析构" << endl;
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
		cout << "TA析构" << endl;
	}
};
struct TB
{
	shared_ptr<TA> aptr;
	~TB()
	{
		cout << "TB析构" << endl;
	}
};
void testPtr()
{
	//形成了环路，有包含关系的循环引用,最终导致无法析构
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
	//shared_ptr<Animal> ptr2(p);//错误，注意事项1
	shared_ptr<Animal> ptr2 = ptr1;//正确

	shared_ptr<Animal> sp1(new Animal);
	cout << "use_count: " << sp1.use_count() << endl;
	shared_ptr<Animal> sp2 = sp1->getSharedPtr();
	cout << "use_count: " << sp2.use_count() << endl;


	testPtr();
	return 0;
}
