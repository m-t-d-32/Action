#include <iostream>
#include "Exception.h"

#ifndef Action__ArrayList_IndexOutOfRange
#define Action__ArrayList_IndexOutOfRange
namespace Action
{
	class ArrayList_IndexOutOfRange: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__ArrayList_IndexOutOfRange */
