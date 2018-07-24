#include <iostream>
#include "Exception.h"

#ifndef Action__BitSet_OutOfRange
#define Action__BitSet_OutOfRange
namespace Action
{
	class BitSet_OutOfRange: public Exception
	{
	public:
		String getName() const override;
		String toString() const override;
	};
}
#endif  /* Action__BitSet_OutOfRange */
