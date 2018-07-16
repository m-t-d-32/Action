#include <iostream>
#include "String.h"
#include "Real_NotANumber.h"

namespace Action
{
	double Real_NotANumber::getValue() const{return m_false_value;}
	String Real_NotANumber::getName()const {return "Action::Real_NotANumber";}
	String Real_NotANumber::toString() const {return "The float number is invalid (such as a result of 0/0) .";}
}