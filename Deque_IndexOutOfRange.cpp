#include <iostream>
#include "String.h"
#include "Deque_IndexOutOfRange.h"

namespace Action
{
    String Deque_IndexOutOfRange::get_name() const
    {
        return "Action::ArrayList_IndexOutOfRange";
    }
    String Deque_IndexOutOfRange::to_string() const
    {
        return "The index provided for the Deque is illegal.";
    }
}
