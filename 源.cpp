#include "HashSet.hpp"
#include <time.h>
#include <stdlib.h>
using namespace Action;
#include <iostream>
#include <set>
using namespace std;
int main()
{
	Integer my_time=clock();

	HashSet<Integer> h;
	for (int i=0;i<100000;++i)
		h.insert(i);
	HashSet<Integer>::Pointer it=h.end();
	for (it--;it!=h.v_begin();--it);


	(clock()-my_time).print();
	system("pause");
	return 0;
}