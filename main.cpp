#include "Action.h"
#include <stdlib.h>
#include <time.h>
#define MAX 1000000
#define SEQ 0
#define RAND 1

#define INSERT_DEF RAND
#define TREE_DEF BinTree
using namespace Action;

int main(){
    srand(time(NULL));
    ArrayList<Integer> array_ints;

#if INSERT_DEF == SEQ
    //Ë³Ðò
    for (Integer i = 0; i < MAX; ++i){
        array_ints.push_back(i);
    }

#elif INSERT_DEF == RAND
    //Ëæ»ú
    for (Integer i = 0; i < MAX; ++i){
        Integer a = rand() % 1000;
        Integer b = rand() % 1000;
        Integer c = a * 1000 + b;
        array_ints.push_back(c);
    }
#endif
    Integer begin = clock();
	TreeSet<Integer, TREE_DEF<Integer> > my_set;
    for (Integer i = 0; i < MAX; ++i){
        my_set.insert(array_ints[i]);
    }
	//my_set.println();
    for (Integer i = 0; i < MAX; ++i){
       my_set.erase(array_ints[i]);
    }
	my_set.println();
    Integer end = clock();
    (end-begin).println();
    return 0;
}
