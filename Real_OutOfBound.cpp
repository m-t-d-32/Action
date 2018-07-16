#include <iostream>
#include "String.h"
#include "Real_OutOfBound.h"

namespace Action
{
	double Real_OutOfBound::getValue() const{return m_false_value;}
	String Real_OutOfBound::getName()const {return "Action::Real_OutOfBound";}
	String Real_OutOfBound::toString() const {return "The float number overflowed.";}
}