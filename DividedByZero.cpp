#include <iostream>
#include "String.h"
#include "DividedByZero.h"

namespace Action
{
	String DividedByZero::get_name()const {return "Action::DividedByZero";}
	String DividedByZero::to_string() const {return "A number's divided by zero.";}
}