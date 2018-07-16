#include <iostream>
#include "String.h"
#include "List_PtrOutOfRange.h"

namespace Action
{
	String List_PtrOutOfRange::getName()const {return "Action::List_PtrOutOfRange";}
	String List_PtrOutOfRange::toString() const {return "The Pointer or index of the LinkedList is illegal.";}
}