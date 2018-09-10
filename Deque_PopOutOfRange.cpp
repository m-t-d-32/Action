#include <iostream>
#include "String.h"
#include "Deque_PopOutOfRange.h"

namespace Action
{
    String Deque_PopOutOfRange::get_name() const
    {
        return "Action::Deque_PopOutOfRange";
    }
    String Deque_PopOutOfRange::to_string() const
    {
        return "Deque is empty and the operation's illegal.";
    }
}
