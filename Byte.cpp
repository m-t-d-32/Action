#include <iostream>
#include "Byte.h"
#include "String.h"
#include "Boolean.h"
namespace Action
{
	String Byte::getName() const{
		return "Action::Byte";
	}
	String Byte::toString() const{
		String rtn;
		rtn.append(m_bValue);
		return rtn;
	}
	Boolean Byte::operator ==(const Object & Arg) const{
		try{
			const Byte & my_byte=dynamic_cast<const Byte &>(Arg);
			return Boolean(getVal()==my_byte.getVal());
		}
		catch (std::bad_cast){
			throw Type_NotCorrespond();
		}
	}
}