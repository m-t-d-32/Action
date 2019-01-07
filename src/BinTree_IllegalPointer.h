#include <iostream>
#include "Exception.h"

#ifndef Action__BinTree_IllegalPointer
#define Action__BinTree_IllegalPointer
namespace Action
{
	class BinTree_IllegalPointer : public Exception
	{
	public:
		String get_name() const override;
		String to_string() const override;
	};
}
#endif  /* Action__BinTree_IllegalPointer */
