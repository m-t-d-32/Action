#include <iostream>
#include "Byte.h"
#include "String.h"
#include "Boolean.h"
#include "Tools.h"

namespace Action
{
    String Byte::get_name() const
    {
        return "Action::Byte";
    }
    String Byte::to_string() const
    {
        String return_string;
        return_string.append(m_value);
        return return_string;
    }
    Boolean Byte::operator == (const Object & another_one) const
    {
        try
        {
            const Byte & another_byte = dynamic_cast<const Byte &>(another_one);
            return Boolean(get_val() == another_byte.get_val());
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
	int Byte::hash_code() const
	{
		return hash(m_value);
	}
}
