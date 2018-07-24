#include <iostream>
#include "Exception.h"

#ifndef Action__Queue_PopOutOfRange
#define Action__Queue_PopOutOfRange
namespace Action
{
	class Queue_PopOutOfRange: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__Queue_PopOutOfRange */
