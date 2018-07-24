#include <iostream>
#include "Exception.h"

#ifndef Action__Stack_PopOutOfRange
#define Action__Stack_PopOutOfRange
namespace Action
{
	class Stack_PopOutOfRange: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__Stack_PopOutOfRange */
