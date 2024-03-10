#include <iostream>
#include <cxxabi.h>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

class	MyClass
{
	int	m_attr2 = 2600;
	protected:
		int	m_attr1 = 42;
	public:
		MyClass() {
		 	cout << "Ctor par defaut " << demangle(typeid(this).name()) << endl;
		}
		MyClass(int a, int b) : m_attr2(b), m_attr1(a) {
			cout << "Ctor - surcharge " << demangle(typeid(this).name()) << endl;
		}
		~MyClass() {
			cout << "Detruit " << demangle(typeid(this).name()) << endl;
		}

		friend ostream &operator<<(ostream &lhs, const MyClass &rhs);
};

ostream &operator<<(ostream &lhs, const MyClass &rhs)
{
	lhs << "MyClass(" << rhs.m_attr1 << ", " << rhs.m_attr2 << ")" << endl;
	return lhs;
}

struct	MyClass2
{
	int	m_attr1;
	int	m_attr2;
};

int main()
{
	// Construit l'objet sur la pile
	MyClass		obj1;
	cout << "type it = " << obj1 << endl;
	MyClass		obj2(15, 12);
	cout << "type it = " << obj2 << endl;
	return 0;
}
