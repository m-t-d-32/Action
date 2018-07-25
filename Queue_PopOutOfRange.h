#include <iostream>
#include "Exception.h"

#ifndef Action__Queue_PopOutOfRange
#define Action__Queue_PopOutOfRange
namespace Action
{
	class Queue_PopOutOfRange: public Exception
	{
	public:
		String get_name() const override;
		String to_string() const override;
	};
}
#endif  /* Action__Queue_PopOutOfRange */
