#include <iostream>
#include "Boolean.h"
#include "String.h"

namespace Action
{
	const Boolean Boolean::True=Boolean::True;
	const Boolean Boolean::False=Boolean::False;
	String Boolean::getName() const{
		return "Action::Boolean";
	}
	String Boolean::toString() const{
		if (getVal()) return "True";
		else return "False";
	}
}