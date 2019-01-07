#include <iostream>
#include "String.h"
#include "Set_PtrOutOfRange.h"

namespace Action
{
    String Set_PtrOutOfRange::get_name() const
    {
        return "Action::Set_PtrOutOfRange";
    }
    String Set_PtrOutOfRange::to_string() const
    {
        return "The Pointer of the Set is illegal.";
    }
}
