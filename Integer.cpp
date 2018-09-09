#include <iostream>
#include "Integer.h"
#include "Real.h"
#include "String.h"
#include "Type_NotCorrespond.h"
#include "Boolean.h"
namespace Action
{
#ifdef INT_MAX
    const Integer Integer::MAX_VALUE = INT_MAX;
#else
    const Integer Integer::MAX_VALUE = ~ (1 << (sizeof (int) * 8 - 1) );
#endif

#ifdef INT_MIN
    const Integer Integer::MIN_VALUE = INT_MIN;
#else
    const Integer Integer::MIN_VALUE = 1 << (sizeof (int) * 8 - 1);
#endif
    Boolean Integer::operator == (const Object & another_one) const
    {
        try
        {
            const Integer & another_integer = dynamic_cast<const Integer &> (another_one);
            return Boolean (m_value == another_integer.m_value);
        }
        catch (std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
    String Integer::get_name() const
    {
        return "Action::Integer";
    }
    String Integer::to_string() const
    {
        const int MAX_LENGTH = 20;

        char return_string[MAX_LENGTH] = {0};
        sprintf (return_string, "%d", m_value);
        return return_string;
    }
    Boolean Integer::compare_to (const Object & another_one) const
    {
        try
        {
            const Integer & another_integer = dynamic_cast<const Integer &> (another_one);
            return *this < another_integer;
        }
        catch (std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
}
