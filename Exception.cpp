#include <iostream>
#include "String.h"
#include "Exception.h"

namespace Action
{
	Exception::Exception():m_cause(NULL){}
	Exception * Exception::getCause() const {return m_cause;}
	void Exception::initCause(Exception * cause){m_cause=cause;}
	String Exception::getName() const {	return "Action::Exception";	}
	String Exception::toString() const { return "An Exception was Thrown.";	}
	Exception::~Exception(){}
}