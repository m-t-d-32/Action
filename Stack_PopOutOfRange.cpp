#include <iostream>
#include "String.h"
#include "Stack_PopOutOfRange.h"

namespace Action
{
	String Stack_PopOutOfRange::get_name() const {return "Action::Stack_PopOutOfRange";}
	String Stack_PopOutOfRange::to_string() const {return "Stack is empty and the operation's illegal.";}
}
