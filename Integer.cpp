#include <iostream>
#include "Integer.h"
#include "Real.h"
#include "String.h"
#include "Type_NotCorrespond.h"
#include "Boolean.h"
namespace Action
{
#ifdef INT_MAX
	const Integer Integer::MAX_VALUE=INT_MAX;
#else
	const Integer Integer::MAX_VALUE=~(1<<(sizeof(int)*8-1));
#endif

#ifdef INT_MIN
	const Integer Integer::MIN_VALUE=INT_MIN;
#else
	const Integer Integer::MIN_VALUE=1<<(sizeof(int)*8-1);
#endif
	Boolean Integer::operator ==(const Object & Arg) const
	{
		try
		{
			const Integer & my_int=dynamic_cast<const Integer &>(Arg);
			return Boolean(m_iValue==my_int.m_iValue);
		}
		catch (std::bad_cast){
			throw Type_NotCorrespond();
		}
	}
	String Integer::getName() const{
		return "Action::Integer";
	}
    String Integer::toString() const{
		const int _MAX_V=20;

		char _str[_MAX_V]={0};
		sprintf(_str,"%d",m_iValue);
		return _str;
	}
    Boolean Integer::compareTo(const Object & arg) const
	{
		try
		{
			const Integer & _my_str=dynamic_cast<const Integer &> (arg);
			return *this<_my_str;
		}
		catch (std::bad_cast)
		{
			throw Type_NotCorrespond();
		}
	}
}