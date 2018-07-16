#include <iostream>
#include "String.h"
#include "Type_NotCorrespond.h"

namespace Action
{
	String Type_NotCorrespond::getName()const {return "Action::Type_NotCorrespond";}
	String Type_NotCorrespond::toString() const {return "The two objects are not comparable.";}
}