#include <iostream>
#include "String.h"
#include "BTree_IllegalOrder.h"

namespace Action
{
    String BTree_IllegalOrder::get_name() const
    {
        return "Action::BTree_IllegalOrder";
    }
    String BTree_IllegalOrder::to_string() const
    {
        return "The template argument Order provided for the BTree is illegal(must be above 2).";
    }
}
