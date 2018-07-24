#include <iostream>
#include "Object.h"
#ifndef Action__Exception
#define Action__Exception
namespace Action
{
	class Exception: public Object
	{
	public:
		Exception();
		virtual Exception * getCause() const;
		virtual void initCause(Exception *);
		virtual String getName() const override;
		virtual String toString() const override;
		virtual ~Exception();
	private:
		Exception * m_cause;
	};
}
#endif /* Action__Exception */
