#include "../src/Action.h"
#include <iostream>
using namespace Action;

int main(){
    String a = "  123 456  ";
    a.left(3).println();
    a.left(11).println();
    a.right(3).println();
    a.right(11).println();
    a.lstrip().println();
    a.rstrip().length().println();
    a.strip().length().println();
    return 0;
}
