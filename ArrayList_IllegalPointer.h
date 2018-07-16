#include <iostream>
#include "Exception.h"

#ifndef Action__ArrayList_IllegalPointer
#define Action__ArrayList_IllegalPointer
namespace Action
{
	class ArrayList_IllegalPointer: public Exception
	{
	public:
		virtual String getName() const override;
		virtual String toString() const override;
	};
}
#endif  /* Action__ArrayList_IllegalPointer */