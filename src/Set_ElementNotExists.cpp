#include <iostream>
#include "String.h"
#include "Set_ElementNotExists.h"

namespace Action
{
    String Set_ElementNotExists::get_name() const
    {
        return "Action::Set_ElementNotExists";
    }
    String Set_ElementNotExists::to_string() const
    {
        return "The Element isn't in current Set.";
    }
}
