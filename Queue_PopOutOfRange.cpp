#include <iostream>
#include "String.h"
#include "Queue_PopOutOfRange.h"

namespace Action
{
    String Queue_PopOutOfRange::get_name() const
    {
        return "Action::Queue_PopOutOfRange";
    }
    String Queue_PopOutOfRange::to_string() const
    {
        return "Queue is empty and the operation's illegal.";
    }
}
