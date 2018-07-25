#include <iostream>
#include "String.h"
#include "Real_NotANumber.h"

namespace Action
{
	double Real_NotANumber::get_value() const{return m_false_value;}
	String Real_NotANumber::get_name()const {return "Action::Real_NotANumber";}
	String Real_NotANumber::to_string() const {return "The float number is invalid (such as a result of 0/0) .";}
}