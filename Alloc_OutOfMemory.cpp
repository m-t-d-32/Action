#include <iostream>
#include "String.h"
#include "Alloc_OutOfMemory.h"

namespace Action
{
	String Alloc_OutOfMemory::getName()const {return "Action::Alloc_OutOfMemory";}
	String Alloc_OutOfMemory::toString() const {return "The device doesn't have enough memory space.";}
}