#include <iostream>
#include <cxxabi.h>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

int main()
{
	auto i = 42;
	auto txt = "coucou\n";

	cout << "i = " << i << endl;
	cout << "type i = " << demangle(typeid(i).name()) << endl;
	cout << "type txt = " << demangle(typeid(txt).name()) << endl;
	cout << "type txt2 = " << typeid(txt).name() << endl;
	return 0;
}
