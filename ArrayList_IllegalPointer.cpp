#include <iostream>
#include "String.h"
#include "ArrayList_IllegalPointer.h"

namespace Action
{
	String ArrayList_IllegalPointer::getName()const {return "Action::ArrayList_IllegalPointer";}
	String ArrayList_IllegalPointer::toString() const {return "The two pointers aren't pointing to the same ArrayList.";}
}