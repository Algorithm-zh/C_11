#include<iostream>
#include<memory>
using namespace std;
class Person
{
public:
	int m_num;
	Person(int num)
	{
		cout << "整型构造函数" << num << endl;

	}
	Person()
	{
		cout << "无参构造函数" << endl;
	}
	Person(string str)
	{
		cout << "字符串构造函数" << str << endl;
	}
	~Person()
	{
		cout<<"析构函数"<<endl;
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

//可以自己封装一个数组的,这样
template<class T>
shared_ptr<T> make_share_array(int size)
{
	return shared_ptr<T>(new T[size], default_delete<T[]>);
}


int main6()
{
	//通过构造函数初始化
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1 use_count:" << ptr1.use_count() << endl;
	//通过移动构造初始化
	shared_ptr<int> ptr2 = move(ptr1);
	cout << "ptr1 use_count:" << ptr1.use_count() << endl;
	cout << "ptr2 use_count:" << ptr2.use_count() << endl;
	//通过拷贝构造初始化
	shared_ptr<int> ptr3 = ptr2;
	cout << "ptr2 use_count:" << ptr2.use_count() << endl;
	cout << "ptr3 use_count:" << ptr3.use_count() << endl;
	//通过make_shared初始化
	shared_ptr<int> ptr4 = make_shared<int>(8);
	shared_ptr<Person> ptr5 = make_shared<Person>(9);
	shared_ptr<Person> ptr6 = make_shared<Person>("hello world");
	//通过reset初始化
	ptr6.reset();//重置，引用基数为0
	cout << "ptr6 use_count:" << ptr6.use_count() << endl;

	ptr5.reset(new Person());//先把原来管理的对象析构掉，再管理新的内存
	cout << "ptr5 use_count:" << ptr5.use_count() << endl;


	//共享指针使用方式
	//获取原始指针
	Person* p = ptr5.get();//get是提供的api，所以用点调用
	p->setValue(100);
	p->print();
	//直接使用智能指针
	ptr5->setValue(999);//调用管理的内存对应类里面的函数，用箭头调用
	ptr5->print();

	//第二个参数为删除器，ppp会调用删除器把第一个参数传进去，让其析构这部分内存
	shared_ptr<Person> ppp(new Person(100), [](Person* p) {
		cout << "========================" << endl;
		//释放内存的操作
		delete p;
	});

	//(C++11)正常情况下默认的删除器会自动析构，但是如果是数组，我们需要自己写删除器
	shared_ptr<Person> p1(new Person[5], [](Person* t) {
		delete[]t;
	});


	cout << "===============" << endl;
	//使用默认的删除器函数析构数组
	shared_ptr<Person> p2(new Person[5], default_delete<Person[]>());


	// ===================================
	//c++11以后数组也可以自动释放内存，只要指定是数组类型就行了
	shared_ptr<Person[]> pp1(new Person[6]);


	return 0;
}