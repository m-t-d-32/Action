#include "../src/Action.h"
#include <time.h>
#include <stdlib.h>
using namespace Action;

int main(){
    TreeSet<Integer> a;
	Set<Integer> & b = a;
	b.insert(12);
	b.insert(23);
	b.println();
	b.erase(12);
	b.println();
	b.size().println();
	b.empty().println();
	b.contains(12).println();
	b.contains(23).println();
	b.to_array().println();
	b.clear();
	b.println();
    return 0;
}
