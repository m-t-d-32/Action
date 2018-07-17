#include "Stack.h"
#include <vector>
#include "String.h"
using namespace Action;

#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;
int main()
{
	ArrayList<String> act_stk;
	for (int i = 0; i < 100; ++i)
		act_stk.push_back("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	ofstream of("1.txt");
	act_stk.print(of);
	system("pause");
	return 0;
}
