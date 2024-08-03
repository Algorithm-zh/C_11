#include<iostream>
#include<memory>
#include<functional>
using namespace std;
/*
	只能一个独占智能指针管理某一块内存
*/
class Car
{
public:
	int m_num;
	Car(int num)
	{
		cout << "整型构造函数" << num << endl;

	}
	Car()
	{
		cout << "无参构造函数" << endl;
	}
	Car(string str)
	{
		cout << "字符串构造函数" << str << endl;
	}
	~Car()
	{
		cout << "析构函数" << endl;
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
	
	//通过构造函数初始化
	unique_ptr<int> ptr1(new int(2));

	//通过移动构造初始化
	unique_ptr<int> ptr2 = move(ptr1);//只能通过move，不能复制

	//通过reset初始化
	ptr2.reset(new int(8));

	//获取原始指针
	unique_ptr<Car> ptr3(new Car(23));
	Car* p = ptr3.get();
	p->setValue(2);
	p->print();

	ptr3->setValue(3);
	ptr3->print();

	//独占指针使用删除器必须指定删除器类型，不能直接指定删除器
	using funcptr = void(*)(Car*);//定义一个函数指针类型
	unique_ptr<Car, funcptr> ptr4(new Car("hello"), [](Car* p) {
		delete p;
		});

	//[]加东西就不能看成函数指针，只能是仿函数，可以将其用可调用对象包装器包装
	unique_ptr<Car, function<void(Car*)>> ptr5(new Car("hello"), [=](Car* p) {
		delete p;
		});

	//独占的智能指针可以管理数组类型的地址，能自动释放
	unique_ptr<Car[]> ptr6(new Car[5]);


	return 0;
}
