#include <iostream>
#include <limits.h>
#include "Real.h"
#include "Integer.h"
#include "String.h"
#include "Type_NotCorrespond.h"
namespace Action
{
	const Real Real::MAX_VALUE=DBL_MAX;
	const Real Real::MIN_VALUE=DBL_MIN;
	Real Real::PRECISION=MIN_VALUE;
	Real::Real(const Integer & iArg) {m_fValue=iArg.m_iValue;}
	String Real::getName() const{
		return "Action::Real";
	}
	String Real::toString() const
	{
		const int _MAX_V=100;

		char _str[_MAX_V]={0};
		sprintf(_str,"%lf",m_fValue);
		return _str;
	}
    Boolean Real::compareTo(const Object & arg) const
	{
		try
		{
			const Real & _my_str=dynamic_cast<const Real &> (arg);
			return *this<_my_str;
		}
		catch (std::bad_cast)
		{
			throw Type_NotCorrespond();
		}
	}
	Boolean Real::operator ==(const Object & Arg) const
	{
		try{
			const Real & my_real=dynamic_cast<const Real &>(Arg);
			return Boolean(fabs(m_fValue-my_real.m_fValue)<=PRECISION);
		}
		catch (std::bad_cast){
			throw Type_NotCorrespond();
		}
	}
}