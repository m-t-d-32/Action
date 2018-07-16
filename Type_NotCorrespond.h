#include <iostream>
#include "Exception.h"

#ifndef Action__Type_NotCorrespond
#define Action__Type_NotCorrespond
namespace Action
{
	class Type_NotCorrespond: public Exception
	{
	public:
		virtual String getName() const override;
		virtual String toString() const override;
	};
}
#endif  /* Action__Type_NotCorrespond */