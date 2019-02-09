#include "../src/Action.h"
#include <time.h>
#include <stdlib.h>
using namespace Action;

int main(){
    String a, b;
	a = "hello";
	a.println();
	b = a;
	b.println();
	a.find("ll").println();
	a = " strip ";
	a.lstrip().size().println();
	a.rstrip().length().println();
	a.strip().println();
	a.left(3).println();
	b.right(2).println();
	b.slice(2, -1).println();
	b = "";
	b.empty().println();
	for (String::Pointer it = a.begin(); it != a.end(); ++it){
		std::cout << *it;
	}
	std::cout << Integer(-1).hash_code() << std::endl;
	std::cout << Boolean::False.hash_code() << std::endl;
	
	Integer x = 3;
	(++x).println();
	if ((++x) == 5 AND (++x) == 6){
		x.println();
	}
	x.println();
    return 0;
}
