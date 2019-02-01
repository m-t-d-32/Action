#include "../src/BTree.h"
#include "../src/Action.h"
using namespace Action;

int main(){
	String a = "AmBmCmDmE";
	a.split("mE").println();
	a.split('C').println();
	a.split_long("mBmCmDmE").println();
	a.split_long("AmBmCm").println();
	a.split_long("m").println();
	a.split_long("AmBmCmDmE").println();
	a.println();
	return 0;
}
