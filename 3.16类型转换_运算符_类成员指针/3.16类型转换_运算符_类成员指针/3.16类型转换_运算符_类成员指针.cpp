//���Աָ��
//���Ա����ָ��
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
int Grand::m_statica = 1;//static ��Ա�����ʼ��,�����������ڳ�ʼ����

class A :public Grand
{
public:
	A() {};
	A(int i, int j, int k, int x) :Grand(i, j, k) {};
	virtual void func() { cout << "run funcA" << endl; }
public:
	void funcPrintA() { cout << "����A��funcPrintA������Ա����" << endl; }

	

};

class B
{
public:
	B() {};
	B(int tv) {};
	void func() { cout << "run funcB" << endl; }
	//�������麯���������������������麯���������ɶ���ʱ���������������麯����������У��ͻ���һ��ָ������麯�����ָ�����ָ��ռ��4���ֽڣ�
	
	virtual void virtualfuncprintB(int x) { cout << "����B��vitual funcPrintB������Ա����" << endl; }
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

	void funcprintC(int x) { cout << "����C��funcPrintC������Ա����" << endl; }
	
	static void staticfuncprintC(int x) { cout << "����C��static funcPrintC������Ա����" << endl; }



};
int main()
{
	//һ�����Աָ��
	//1.1	����һ����ͨ�����Ա����ָ��

	void (C:: * pointerc)(int);	//һ����Ա����ָ��Ķ��壬��������Ϊpc
	pointerc = &C::funcprintC;	//���Ա����ָ�����pc����ֵ
	//���ע��:��Ա������������ģ������ڶ���ֻҪ�����ھ��г�Ա������ַ�ڡ�
	//��������Ҫʹ�������Ա����ָ�룬�ͱ���Ҫ�����󶨵�һ��������ϲ����á�
	//ʹ�ú���ָ��ĸ�ʽ��"�������.*����ָ�������������"������Ǹ�����ָ�룬���ø�ʽ"ָ����->����ָ�������"������
	C c;
	C* pct=nullptr;
	pct = &c;
	(c.*pointerc)(100);//����c������ָ�����pc��ָ��ĳ�Ա����:
	(pct->funcprintC)(200);//Ҳ������ pct����pc��ָ��ĳ�Ա����;
	
	//1.2	����һ���麯����Եָ��
	void (B:: * virtualpointerb)(int);
	virtualpointerb = &B::virtualfuncprintB; //����һ���������ڴ��ַ��
	//ͬ���Ͳ�ͬ���Ա��������һ����Ҳ��Ҫ�󶨵�һ��������ϲ����á�
	B b, * pbt;
	pbt = &b;
	b.virtualfuncprintB(800);
	pbt->virtualfuncprintB(900);

	//1.3	����һ����̬���ຯ��ָ�벢��ֵ����Щ����

	void(*mystaticpointerc)(int) = &C::staticfuncprintC;
	mystaticpointerc(59188888);//ֱ��ʹ�þ�̬��Ա����ָ�������ɡ�


	//����//���Ա����ָ��
	//ͨ�����Ա����ָ������Ա����ֵ
	//2.1������ͨ��Ա����
	int Grand::* mp = &Grand::m_a; //����һ����Ա����ָ�롣
									//���������������ϵ�ָ�롣
									//������ָ���ڴ���ĳ����ַ�����Ǹó�Ա��������������ָ��֮���ƫ������

	Grand testmp;
	testmp.*mp = 189;//ͨ�����Ա����ָ�����޸ĳ�Ա����ֵ,�ȼ���testmp.m_a = 189;


	//2.1���ھ�̬��Ա����
	//����ָ��̬��Ա������ָ�룬�����������ڴ��ַ�ġ�
	int* staticGrand_m_a = &Grand::m_statica;//����һ����̬��Ա����ָ��
	*staticGrand_m_a = 15988;


}