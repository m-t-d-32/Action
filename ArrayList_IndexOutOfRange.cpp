#include <iostream>
#include "String.h"
#include "ArrayList_IndexOutOfRange.h"

namespace Action
{
	String ArrayList_IndexOutOfRange::getName()const {return "Action::ArrayList_IndexOutOfRange";}
	String ArrayList_IndexOutOfRange::toString() const {return "The index provided for the ArrayList is illegal.";}
}