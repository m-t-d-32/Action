#include <iostream>
#include "String.h"
#include "Integer_OutOfBound.h"
#include "Integer.h"
namespace Action
{
    Integer Integer_OutOfBound::getValue() const{return m_false_value;}
	String Integer_OutOfBound::getName()const {return "Action::Integer_OutOfBound";}
	String Integer_OutOfBound::toString() const {return "The Integer overflowed.";}
}