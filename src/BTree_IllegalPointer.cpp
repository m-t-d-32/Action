#include <iostream>
#include "String.h"
#include "BTree_IllegalPointer.h"

namespace Action
{
    String BTree_IllegalPointer::get_name() const
    {
        return "Action::BTree_IllegalPointer";
    }
    String BTree_IllegalPointer::to_string() const
    {
        return "The pointer provided for the BTree is illegal.";
    }
}
