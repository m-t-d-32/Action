#include <iostream>
#include "Exception.h"

#ifndef Action__Set_ElementNotExists
#define Action__Set_ElementNotExists
namespace Action
{
	class Set_ElementNotExists: public Exception
	{
	public:
		virtual String getName() const override;
		virtual String toString() const override;
	};
}
#endif  /* Action__Set_ElementNotExists */