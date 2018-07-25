#include <iostream>
#include "String.h"
#include "Heap_PopOutOfRange.h"

namespace Action
{
	String Heap_PopOutOfRange::get_name()const {return "Action::Heap_PopOutOfRange";}
	String Heap_PopOutOfRange::to_string() const {return "Heap is empty and the operation's illegal.";}
}