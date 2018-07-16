#include <iostream>
#include "Exception.h"

#ifndef Action__Heap_PopOutOfRange
#define Action__Heap_PopOutOfRange
namespace Action
{
	class Heap_PopOutOfRange: public Exception
	{
	public:
		virtual String getName() const override;
		virtual String toString() const override;
	};
}
#endif  /* Action__Heap_PopOutOfRange */
