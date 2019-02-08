#include "../src/Action.h"
#include <time.h>
#include <stdlib.h>
using namespace Action;

int main(){
	BTree<Integer> btree;
	ArrayList<Integer> pool;
	srand(time(NULL));
	for (int i = 0; i < 100000; ++i){
		pool.push_back(rand());
	}
	Integer begin = clock();
	for (int i = 0; i < 100000; ++i){
		btree.insert(pool[i]);
	}
	for (int i = 0; i < 100000; ++i){
		btree.erase(pool[i]);
	}
	Integer end = clock();
	btree.println();
	(end - begin).println();
	system("pause");
    return 0;
}
