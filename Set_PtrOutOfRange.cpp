#include <iostream>
#include "String.h"
#include "Set_PtrOutOfRange.h"

namespace Action
{
	String Set_PtrOutOfRange::getName()const {return "Action::Set_PtrOutOfRange";}
	String Set_PtrOutOfRange::toString() const {return "The Pointer of the Set is illegal.";}
}