#include <iostream>
#include "Exception.h"

#ifndef Action__Alloc_OutOfMemory
#define Action__Alloc_OutOfMemory
namespace Action
{
	class Alloc_OutOfMemory: public Exception
	{
	public:
		virtual String getName() const override;
		virtual String toString() const override;
	};
}
#endif  /* Action__Alloc_OutOfMemory */
