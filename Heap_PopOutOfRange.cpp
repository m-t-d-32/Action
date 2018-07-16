#include <iostream>
#include "String.h"
#include "Heap_PopOutOfRange.h"

namespace Action
{
	String Heap_PopOutOfRange::getName()const {return "Action::Heap_PopOutOfRange";}
	String Heap_PopOutOfRange::toString() const {return "Heap is empty and the operation's illegal.";}
}