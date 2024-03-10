#include <iostream>
#include <cxxabi.h>
#include <list>
#include <memory>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

//class	MyClass
//{
//	int	m_attr2 = 2600;
//	protected:
//		int	m_attr1 = 42;
//	public:
//		MyClass() {
//		 	cout << "Ctor par defaut " << demangle(typeid(this).name()) << endl;
//		}
//		MyClass(int a, int b) : m_attr2(b), m_attr1(a) {
//			cout << "Ctor - surcharge " << demangle(typeid(this).name()) << endl;
//		}
//		~MyClass() {
//			cout << "Detruit " << demangle(typeid(this).name()) << endl;
//		}
//
//		friend ostream &operator<<(ostream &lhs, const MyClass &rhs);
//};
//

class	MyClass2
{
	int	m_attr1 = 12;
	int	m_attr2 = 66;
	int	m_attr3 = 2600;

	public:
	MyClass2()// : m_attr1(12), m_attr2(66), m_attr3(2600)
	{
		cout << "CTOR at " << this << endl;
		cout << "ATTR1 " << m_attr1 << endl;
	}

	MyClass2(const MyClass2 &oth)
	{
		cout << "CTOR BY COPY at " << this << endl;
		cout << "object size " << sizeof (*this) << endl;
		cout << "oth " << &oth << endl;
		__raw_copy(oth);
	}

	MyClass2 operator=(const MyClass2 &oth)
	{
		cout << "operator= " << this << endl;
		__raw_copy(oth);
		return *this;
	} // a = b = c = d;
	

	MyClass2(int a, int b, int c) : m_attr1(a), m_attr2(b), m_attr3(c)
	{
		cout << "CTOR BY overload at " << this << endl;
	}

	virtual ~MyClass2()
	{
		cout << "DTOR at " << this << endl;
	}

	private:
	void __raw_copy(const MyClass2 &oth)
	{
		m_attr1 = oth.m_attr1;
		m_attr2 = oth.m_attr2;
		m_attr3 = oth.m_attr3;
	}

	friend ostream &operator<<(ostream &lhs, const MyClass2 &rhs);
};

ostream &operator<<(ostream &lhs, const MyClass2 &rhs)
{
	lhs << "MyClass2(" << rhs.m_attr1 << ", " << rhs.m_attr2 << ", " << rhs.m_attr3 << ")" << endl;
	return lhs;
}

struct Dummy
{
	int data = 666;

	~Dummy()
	{
		cout << "DTOR DUMMY" << endl;
	}
};

class MyOther : public MyClass2
{
	// tous les attributs / function members / operator sont copiees dans ma definition!
	

	int m_attr4 = 999;
	unique_ptr<Dummy> m_attr5 = make_unique<Dummy>();
	friend ostream &operator<<(ostream &lhs, const MyOther &rhs);
	public:
	MyOther()
	{
		cout << "CTOR MYOTHER" << endl;
	}

	~MyOther() override
	{
		cout << "DTORE MYOTHER" << endl;
	}
};

ostream &operator<<(ostream &lhs, const MyOther &rhs)
{
	lhs << "MyOther(" << *(const MyClass2*)&rhs
		<< ", " << rhs.m_attr4
		<< ", " << rhs.m_attr5
	       	<< ")" << endl;
	return lhs;
}

int main()
{
	unique_ptr<MyClass2> u = make_unique<MyOther>();

	cout << "MyOther :" << *u << endl;

	//list<unique_ptr<MyClass2>> ls;
	//ls.push_back(make_unique<MyClass2>());
	//ls.push_back(make_unique<MyClass2>(11, 22, 33));
	//ls.push_back(make_unique<MyClass2>(55, 66, 77));
       	////{
	////		make_unique<MyClass2>(),
	////		make_unique<MyClass2>(11,22,33),
	////		make_unique<MyClass2>(55,66,77)
	////};

	//cout << "==========" << endl;
	//for (auto &it: ls)
	//{
	//	cout << "IT : " << demangle(typeid(it).name()) << endl;
	//	cout << "OBJ " << &it << endl;
	//}

	// Construit l'objet sur la pile
	//MyClass		obj1;
	//cout << "type it = " << obj1 << endl;
	//MyClass		obj2(15, 12);
	//cout << "type it = " << obj2 << endl;
	//MyClass2 obj;

	//{
	//	MyClass2 obj2 = obj; // MyClass2 obj2(obj);
	//	cout << "ATTR " << obj2.m_attr1 << " " << obj2.m_attr2 << " " << obj2.m_attr3 << endl;
	//}
	//MyClass2 obj3;
	//obj.m_attr1 = 44;
	//obj.m_attr2 = 111;
	//obj.m_attr3 = 777;
	//obj3 = obj;
	//cout << "ATTR " << obj3.m_attr1 << " " << obj3.m_attr2 << " " << obj3.m_attr3 << endl;
	//MyClass2 obj4(55, 77, 99);
	//cout << "ATTR " << obj4.m_attr1 << " " << obj4.m_attr2 << " " << obj4.m_attr3 << endl;
	return 0;
}
