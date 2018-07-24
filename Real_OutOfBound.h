#include <iostream>
#include "Exception.h"

#ifndef Action__Real_OutOfBound
#define Action__Real_OutOfBound
namespace Action
{
	class Real_OutOfBound: public Exception
	{
	public:
		Real_OutOfBound(double fal_value):m_false_value(fal_value){}
		String getName() const override;
		String toString() const override;
		double getValue() const;
	private:
		double m_false_value;
	};
}
#endif  /* Action__Real_OutOfBound */
