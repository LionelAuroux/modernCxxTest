#include <iostream>
#include <cxxabi.h>
#include <list>
#include <memory>
#include <map>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

class	MyClass
{
	int	m_attr1 = 12;
	int	m_attr2 = 66;
	int	m_attr3 = 2600;

	public:
	MyClass()// : m_attr1(12), m_attr2(66), m_attr3(2600)
	{
		cout << "CTOR at " << this << endl;
		cout << "ATTR1 " << m_attr1 << endl;
	}

	MyClass(const MyClass &oth)
	{
		cout << "CTOR BY COPY at " << this << endl;
		cout << "object size " << sizeof (*this) << endl;
		cout << "oth " << &oth << endl;
		__raw_copy(oth);
	}

	MyClass operator=(const MyClass &oth)
	{
		cout << "operator= " << this << endl;
		__raw_copy(oth);
		return *this;
	} // a = b = c = d;
	

	MyClass(int a, int b, int c) : m_attr1(a), m_attr2(b), m_attr3(c)
	{
		cout << "CTOR BY overload at " << this << endl;
	}

	virtual ~MyClass()
	{
		cout << "DTOR at " << this << endl;
	}

	private:
	void __raw_copy(const MyClass &oth)
	{
		m_attr1 = oth.m_attr1;
		m_attr2 = oth.m_attr2;
		m_attr3 = oth.m_attr3;
	}

	friend ostream &operator<<(ostream &lhs, const MyClass &rhs);
};

ostream &operator<<(ostream &lhs, const MyClass &rhs)
{
	lhs << "MyClass(" << rhs.m_attr1 << ", " << rhs.m_attr2 << ", " << rhs.m_attr3 << ")" << endl;
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

class MyOther : public MyClass
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
	lhs << "MyOther(" << *(const MyClass*)&rhs
		<< ", " << rhs.m_attr4
		<< ", " << rhs.m_attr5
	       	<< ")" << endl;
	return lhs;
}

int main()
{
	auto inst = make_shared<MyOther>();
	auto shared = inst;

	cout << "MyOther :" << inst.use_count() << endl;
	list<shared_ptr<MyClass>> ls;
	ls.push_back(make_shared<MyClass>());
	ls.push_back(make_shared<MyOther>());
	ls.push_back(make_shared<MyClass>(1, 2, 3));
	list<shared_ptr<MyClass>> ls2 = {make_shared<MyOther>(), make_shared<MyClass>(1, 2, 3)};
	map<string, shared_ptr<MyClass>> d = {
		{"bim", make_shared<MyClass>(5, 6, 7)},
		{"bam", make_shared<MyClass>(8, 9, 10)},
		{"boom", make_shared<MyClass>(31, 32, 33)},
	};
	for (auto it: ls2)
	{
		cout << "TYPE: " << demangle(typeid(it).name()) << endl;
		cout << "IT LIST " << *it << endl;
	}
	for (auto p: d)
	{
		cout << "Key:" << p.first << endl;
		cout << "Value:" << p.second << endl;
	}
	for (auto it: {1, 2, 3, 4, 5, 6})
	{
		cout << "T: " << demangle(typeid(it).name()) << endl;
		cout << "IT: " << it << endl;
	}
	map<string, unique_ptr<MyClass>> d2;
	d2["bim"] = make_unique<MyClass>(5, 6, 7);
	d2["bam"] = make_unique<MyClass>(8, 9, 10);
	d2["boom"] = make_unique<MyClass>(31, 32, 33);
	return 0;
}
