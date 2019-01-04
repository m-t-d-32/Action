#include <iostream>
#include "String.h"
#include "BinTree_IllegalPointer.h"

namespace Action
{
	String BinTree_IllegalPointer::get_name() const
	{
		return "Action::BinTree_IllegalPointer";
	}
	String BinTree_IllegalPointer::to_string() const
	{
		return "The pointer provided for the BinTree is illegal.";
	}
}
