#include <iostream>
#include "String.h"
#include "Stack_PopOutOfRange.h"

namespace Action
{
	String Stack_PopOutOfRange::getName() const {return "Action::Stack_PopOutOfRange";}
	String Stack_PopOutOfRange::toString() const {return "Stack is empty and the operation's illegal.";}
}
