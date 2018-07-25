#include <iostream>
#include "String.h"
#include "Exception.h"

namespace Action
{
	Exception::Exception():m_cause(NULL){}
	Exception * Exception::get_cause() const {return m_cause;}
	void Exception::init_cause(Exception * cause){m_cause=cause;}
	String Exception::get_name() const {	return "Action::Exception";	}
	String Exception::to_string() const { return "An Exception was Thrown.";	}
	Exception::~Exception(){}
}