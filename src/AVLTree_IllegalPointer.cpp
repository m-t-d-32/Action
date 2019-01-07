#include <iostream>
#include "String.h"
#include "AVLTree_IllegalPointer.h"

namespace Action
{
    String AVLTree_IllegalPointer::get_name() const
    {
        return "Action::AVLTree_IllegalPointer";
    }
    String AVLTree_IllegalPointer::to_string() const
    {
        return "The pointer provided for the AVLTree is illegal.";
    }
}
