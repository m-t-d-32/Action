#include <iostream>
#include "Exception.h"

#ifndef Action__Real_NotANumber
#define Action__Real_NotANumber
namespace Action
{
	class Real_NotANumber: public Exception
	{
	public:
		Real_NotANumber(double fal_value):m_false_value(fal_value){}
		virtual String getName() const override;
		virtual String toString() const override;
		double getValue() const;
	private:
		double m_false_value;
	};
}
#endif  /* Action__Real_NotANumber */
