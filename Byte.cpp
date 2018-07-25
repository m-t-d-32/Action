#include <iostream>
#include "Byte.h"
#include "String.h"
#include "Boolean.h"
namespace Action
{
	String Byte::get_name() const{
		return "Action::Byte";
	}
	String Byte::to_string() const{
		String rtn;
		rtn.append(m_bValue);
		return rtn;
	}
	Boolean Byte::operator ==(const Object & Arg) const{
		try
		{
			const Byte & my_byte=dynamic_cast<const Byte &>(Arg);
			return Boolean(get_val()==my_byte.get_val());
		}
		catch (std::bad_cast){
			throw Type_NotCorrespond();
		}
	}
}