#include <iostream>
#include <cxxabi.h>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

const char *demangle(const char *ty)
{
	int status;
	return abi::__cxa_demangle(ty, 0, 0, &status);
}

int main()
{
	vector<int>	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	list<int>	ls {1, 2, 3, 4, 5, 6, 7, 8};
	map<string, int> chaussette {
		{"coucou", 12},
		{"tutu", 2600},
	};
	cout << "type drap = " << demangle(typeid(drap).name()) << endl;

	for (auto it : chaussette)
	{
		cout << "type it = " << demangle(typeid(it).name()) << endl;
		cout << "key = " << it.first << endl;
		cout << "value = " << it.second << endl;
	}

	for (auto &it : ls)
	{
		cout << "type it = " << demangle(typeid(it).name()) << endl;
		cout << "it = " << it << endl;
		it += 1;
	}
	cout << "-------" << endl;
	for (auto it : ls)
	{
		cout << "it = " << it << endl;
	}

	cout << "-------" << endl;
	cout << "type vec1 = " << demangle(typeid(vec).name()) << endl;

	for (auto &it : vec)
	{
		cout << "type it = " << demangle(typeid(it).name()) << endl;
		cout << "it = " << it << endl;
		it += 1;
	}
	cout << "-------" << endl;
	for (auto it : vec)
	{
		cout << "it = " << it << endl;
	}
	//for (auto &it : vec)
	//{
	//	cout << "type it = " << demangle(typeid(it).name()) << endl;
	//	cout << "it = " << it << endl;
	//	it += 1;
	//}
	//for (auto it : vec)
	//{
	//	cout << "it = " << it << endl;
	//}
	return 0;
}
