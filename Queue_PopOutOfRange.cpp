#include <iostream>
#include "String.h"
#include "Queue_PopOutOfRange.h"

namespace Action
{
	String Queue_PopOutOfRange::getName() const {return "Action::Queue_PopOutOfRange";}
	String Queue_PopOutOfRange::toString() const {return "Queue is empty and the operation's illegal.";}
}
