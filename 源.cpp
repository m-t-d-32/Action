#include "HashMap.hpp"
using namespace Action;
#include <cstdlib>
int main()
{
	HashMap<String, Integer> my_map;
	my_map.insert("hello", 1);
	//my_map.insert("bye", 2);
	my_map["bye"] = 3;
	my_map.print();
	system("pause");
	return 0;
}