#include <iostream>
#include "String.h"
#include "Integer_OutOfBound.h"
#include "Integer.h"

namespace Action
{
    Integer Integer_OutOfBound::get_value() const
    {
        return m_false_value;
    }
    String Integer_OutOfBound::get_name() const
    {
        return "Action::Integer_OutOfBound";
    }
    String Integer_OutOfBound::to_string() const
    {
        return "The Integer overflowed.";
    }
}
