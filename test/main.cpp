#include "../src/BTree.h"
#include "../src/Action.h"
using namespace Action;

int main(){
	String a = "A B C D\t E";
	a.split("E").println();
	a.split().println();
	a.split_long("D\t").println();
	a.split_long().println();
	a.println();
	a.slice(1, -1).println();
	a.slice(1, a.length()).println();
	a.slice(0, a.length()).println();
	
	ArrayList<Integer> b;
	for (int i = 0; i < 100; ++i){
		b.push_back(i);
	}
	b.slice(0, -1).println();
	b.slice(1, -1).println();
	b.slice(1, b.size()).println();
	b.slice(0, b.size()).println();
	return 0;
}
