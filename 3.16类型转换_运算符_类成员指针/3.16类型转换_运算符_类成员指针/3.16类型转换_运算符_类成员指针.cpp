//类成员指针
//类成员变量指针
#include <iostream>
using namespace std;

class Grand
{
public:
	Grand() {};
	Grand(int i, int j, int k) {}

	int m_a;
	static int m_statica;
};
int Grand::m_statica = 1;//static 成员必须初始化,而不能在类内初始化。

class A :public Grand
{
public:
	A() {};
	A(int i, int j, int k, int x) :Grand(i, j, k) {};
	virtual void func() { cout << "run funcA" << endl; }
public:
	void funcPrintA() { cout << "调用A的funcPrintA（）成员函数" << endl; }

	

};

class B
{
public:
	B() {};
	B(int tv) {};
	void func() { cout << "run funcB" << endl; }
	//类中有虚函数则编译器会给该类生成虚函数表，当生成对象时，如果这个类中有虚函数，则对象中，就会有一个指向这个虚函数表的指针这个指针占有4个字节；
	
	virtual void virtualfuncprintB(int x) { cout << "调用B的vitual funcPrintB（）成员函数" << endl; }
};

class C :public A, public B
{

//public:
//	using A::A;
//	using B::B;

public:
	C() {};
	C(int i, int j, int k, int x) :A(i, j, k, x), B(i) {};
	void func() { cout << "run funcC" << endl; }

	void funcprintC(int x) { cout << "调用C的funcPrintC（）成员函数" << endl; }
	
	static void staticfuncprintC(int x) { cout << "调用C的static funcPrintC（）成员函数" << endl; }



};
int main()
{
	//一。类成员指针
	//1.1	定义一个普通的类成员函数指针

	void (C:: * pointerc)(int);	//一个成员函数指针的定义，变量名字为pc
	pointerc = &C::funcprintC;	//类成员函数指针变量pc被赋值
	//大家注意:成员函数是属于类的，不属于对象，只要有类在就有成员函数地址在。
	//但是你若要使用这个成员函数指针，就必须要把他绑定到一个类对象上才能用。
	//使用函数指针的格式："类对象名.*函数指针变量名来调用"，如果是个对象指针，调用格式"指针名->函数指针变量名"来调用
	C c;
	C* pct=nullptr;
	pct = &c;
	(c.*pointerc)(100);//对象c，调用指针变量pc所指向的成员函数:
	(pct->funcprintC)(200);//也可以用 pct调用pc所指向的成员函数;
	
	//1.2	定义一个虚函数尘缘指针
	void (B:: * virtualpointerb)(int);
	virtualpointerb = &B::virtualfuncprintB; //这是一个真正的内存地址；
	//同样和不同类成员函数调用一样，也需要绑定刀一个类对象上才能用。
	B b, * pbt;
	pbt = &b;
	b.virtualfuncprintB(800);
	pbt->virtualfuncprintB(900);

	//1.3	定义一个静态的类函数指针并赋值（有些区别）

	void(*mystaticpointerc)(int) = &C::staticfuncprintC;
	mystaticpointerc(59188888);//直接使用静态成员函数指针名即可。


	//二。//类成员变量指针
	//通过类成员变量指针给类成员变量值
	//2.1对于普通成员变量
	int Grand::* mp = &Grand::m_a; //定义一个成员变量指针。
									//并不是真正意义上的指针。
									//他不是指向内存中某个地址，而是该成员变量，与该类对象指针之间的偏移量。

	Grand testmp;
	testmp.*mp = 189;//通过类成员变量指针来修改成员变量值,等价于testmp.m_a = 189;


	//2.1对于静态成员变量
	//这种指向静态成员变量的指针，是有真正的内存地址的。
	int* staticGrand_m_a = &Grand::m_statica;//定义一个静态成员变量指针
	*staticGrand_m_a = 15988;


}