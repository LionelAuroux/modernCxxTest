#include <iostream>
#include <cxxabi.h>
#include <vector>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

int main()
{
	vector<int>	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (auto it : vec)
	{
		cout << "type it = " << demangle(typeid(it).name()) << endl;
		cout << "it = " << it << endl;
		it += 1;
	}
	for (auto it : vec)
	{
		cout << "it = " << it << endl;
	}
	for (auto &it : vec)
	{
		cout << "type it = " << demangle(typeid(it).name()) << endl;
		cout << "it = " << it << endl;
		it += 1;
	}
	for (auto it : vec)
	{
		cout << "it = " << it << endl;
	}
	return 0;
}
