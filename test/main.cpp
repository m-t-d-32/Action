#include "../src/Action.h"
#include <time.h>
#include <stdlib.h>
using namespace Action;

int main(){
    srand(time(NULL));
    TreeMap<String, Integer, BTree<Pair<String, Integer> > > a;
    Map<String, Integer> & b = a;
    for (int i = 0; i < 10; ++i){
        String v; 
        for (int j = 0; j < 3; ++j){
            v += char(rand() % 26 + 'a');
        }
        b.insert(v, i);
    }
    for (TreeMap<String, Integer, BTree<Pair<String, Integer> > >::Pointer it = a.begin(); it != a.end(); ++it){
        it->println();
    }
    String("\n").println();
    for (TreeMap<String, Integer, BTree<Pair<String, Integer> > >::Pointer it = --a.end(); it != --a.begin(); --it){
        it->println();
    }
    b.println();
    return 0;
}
