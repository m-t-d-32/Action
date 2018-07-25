#include <iostream>
#include "String.h"
#include "ArrayList_IndexOutOfRange.h"

namespace Action
{
	String ArrayList_IndexOutOfRange::get_name()const {return "Action::ArrayList_IndexOutOfRange";}
	String ArrayList_IndexOutOfRange::to_string() const {return "The index provided for the ArrayList is illegal.";}
}