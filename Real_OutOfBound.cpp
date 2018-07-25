#include <iostream>
#include "String.h"
#include "Real_OutOfBound.h"

namespace Action
{
	double Real_OutOfBound::get_value() const{return m_false_value;}
	String Real_OutOfBound::get_name()const {return "Action::Real_OutOfBound";}
	String Real_OutOfBound::to_string() const {return "The float number overflowed.";}
}