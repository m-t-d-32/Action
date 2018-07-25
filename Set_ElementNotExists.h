#include <iostream>
#include "Exception.h"

#ifndef Action__Set_ElementNotExists
#define Action__Set_ElementNotExists
namespace Action
{
	class Set_ElementNotExists: public Exception
	{
	public:
		String get_name() const override;
		String to_string() const override;
	};
}
#endif  /* Action__Set_ElementNotExists */
