#include <iostream>
#include "String.h"
#include "DividedByZero.h"

namespace Action
{
	String DividedByZero::getName()const {return "Action::DividedByZero";}
	String DividedByZero::toString() const {return "A number's divided by zero.";}
}