#include <iostream>
#include "Exception.h"

#ifndef Action__DividedByZero
#define Action__DividedByZero
namespace Action
{
	class DividedByZero: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__DividedByZero */
