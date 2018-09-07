#include <iostream>
#include "String.h"
#include "ArrayList_IllegalPointer.h"

namespace Action
{
    String ArrayList_IllegalPointer::get_name() const
    {
        return "Action::ArrayList_IllegalPointer";
    }
    String ArrayList_IllegalPointer::to_string() const
    {
        return "The two pointers aren't pointing to the same ArrayList.";
    }
}
