#include "../src/Action.h"
#include <time.h>
#include <stdlib.h>
using namespace Action;

int main(){
    TreeSet<Integer, BTree<Integer> > btree;
    HashSet<Integer> nums;
    Integer counter = 0;
    srand(time(NULL));
    for (int i = 0; i < 800; ++i){
        nums.insert(rand());
    }
    for (HashSet<Integer>::Pointer it = nums.v_end(); it != nums.v_begin(); --it){
        btree.insert(*it);
    }
    btree.println();
    for (HashSet<Integer>::Pointer it = nums.begin(); it != nums.end(); ++it){
        btree.erase(*it);
    }
    btree.println();
    return 0;
}
