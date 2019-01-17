#include "../src/BTree.h"
#include "../src/Action.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#define MAX 1000000
#define SEQ 0
#define RAND 1

#define INSERT_DEF RAND
#define TREE_DEF BTree
using namespace Action;

int main(){
	TREE_DEF<Integer, 4, DefaultCompare<Integer>, LinkedList> btree;
	srand(time(NULL));
	Integer begin = clock();
	for (int i = 0; i < 1000000; ++i){
		btree.insert(i);
		//btree.println();
	}
	(clock() - begin).print();
	//btree.to_array().print();
    return 0;
}
