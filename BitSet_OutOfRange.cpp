#include <iostream>
#include "String.h"
#include "BitSet_OutOfRange.h"

namespace Action
{
	String BitSet_OutOfRange::get_name()const {return "Action::BitSet_OutOfRange";}
	String BitSet_OutOfRange::to_string() const {return "The index of BitSet is illegal.";}
}