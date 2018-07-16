#include <iostream>
#include "String.h"
#include "Set_ElementNotExists.h"

namespace Action
{
	String Set_ElementNotExists::getName()const {return "Action::Set_ElementNotExists";}
	String Set_ElementNotExists::toString() const {return "The Element isn't in current Set.";}
}