#include <iostream>
#include "String.h"
#include "Alloc_OutOfMemory.h"

namespace Action
{
    String Alloc_OutOfMemory::get_name()const
    {
        return "Action::Alloc_OutOfMemory";
    }
    String Alloc_OutOfMemory::to_string() const
    {
        return "The device doesn't have enough memory space.";
    }
}
