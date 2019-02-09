#include <iostream>
#include <limits.h>
#include "Real.h"
#include "Integer.h"
#include "String.h"
#include "Type_NotCorrespond.h"
#include "Tools.h"

namespace Action
{
    const Real Real::MAX_VALUE = DBL_MAX;
    const Real Real::MIN_VALUE = DBL_MIN;
    Real Real::PRECISION = MIN_VALUE;
    Real::Real(Integer integer_value)
    {
        m_value = integer_value.m_value;
    }
    String Real::get_name() const
    {
        return "Action::Real";
    }
    String Real::to_string() const
    {
        const int MAX_LENGTH = 100;

        char return_string[MAX_LENGTH] = {0};
        sprintf(return_string, "%f", m_value);
        return return_string;
    }
    Boolean Real::compare_to(const Object & another_one) const
    {
        try
        {
            const Real & another_real = dynamic_cast<const Real &>(another_one);
            return *this < another_real;
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
    Boolean Real::operator == (const Object & another_one) const
    {
        try
        {
            const Real & another_real = dynamic_cast<const Real &>(another_one);
            return Boolean(fabs(m_value - another_real.m_value) <= PRECISION);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
	int Real::hash_code() const
	{
		int count = sizeof(double) / sizeof(int);
		int result = 1;
		for(int i = 0; i < count; ++i)
		{
			result *= * ((int *)(&m_value) + i);
			result >>= ((i ^ 23) % sizeof(int));
		}
		if(result < 0)
			result = -result;
		return hash(result);
	}
}
