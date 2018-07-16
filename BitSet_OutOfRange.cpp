#include <iostream>
#include "String.h"
#include "BitSet_OutOfRange.h"

namespace Action
{
	String BitSet_OutOfRange::getName()const {return "Action::BitSet_OutOfRange";}
	String BitSet_OutOfRange::toString() const {return "The index of BitSet is illegal.";}
}