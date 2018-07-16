#include <iostream>
#include "Boolean.h"
#include "String.h"

namespace Action
{
	const Boolean Boolean::True = Boolean(true);
	const Boolean Boolean::False = Boolean(false);
	String Boolean::getName() const{
		return "Action::Boolean";
	}
	String Boolean::toString() const{
		if (getVal()) return "True";
		else return "False";
	}
}