#include <iostream>
#include "String.h"
#include "Type_NotCorrespond.h"

namespace Action
{
	String Type_NotCorrespond::get_name()const {return "Action::Type_NotCorrespond";}
	String Type_NotCorrespond::to_string() const {return "The two objects are not comparable.";}
}