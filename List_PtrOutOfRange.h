#include <iostream>
#include "Exception.h"

#ifndef Action__List_PtrOutOfRange
#define Action__List_PtrOutOfRange
namespace Action
{
	class List_PtrOutOfRange: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__List_PtrOutOfRange */
