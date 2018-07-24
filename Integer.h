#include <iostream>
#include <limits.h>
#include "Object.h"
#include "Real.h"
#include "Integer_OutOfBound.h"
#include "DividedByZero.h"

/*
	春水初生，春林初盛
	春风十里，不如你
*/

#ifndef Action__Integer
#define Action__Integer
namespace Action
{
	class Integer: public Object
	{
#ifndef MOD
#define MOD %
#endif
#ifndef DIV
#define DIV ||
#endif
		friend class Real;
	public:
		const static Integer MAX_VALUE;
		const static Integer MIN_VALUE;

		Integer(){m_iValue=0;}
		Integer(int iArg){m_iValue=iArg;}
		Integer(const Integer & iArg){m_iValue=iArg.m_iValue;}
		explicit Integer(const Real & fArg){m_iValue=(int)fArg.get_double();}

		String getName() const override;
		String toString() const override;
		Boolean compareTo(const Object & arg) const override;

		inline int get_int() const {return m_iValue;}

		inline friend Integer operator -(const Integer & Arg)
		{
			if (Arg==MIN_VALUE) throw Integer_OutOfBound(-Arg.m_iValue);
			return -Arg.m_iValue;
		}
		inline friend Integer operator +(const Integer & Arg1,const Integer & Arg2)
		{
			int iResult=Arg1.m_iValue+Arg2.m_iValue;
			if (Arg1.m_iValue>0 && Arg2.m_iValue>0 && iResult<=0)
				throw Integer_OutOfBound(iResult);
			else if (Arg1.m_iValue<0 && Arg2.m_iValue<0 && iResult>=0)
				throw Integer_OutOfBound(iResult);
			return iResult;
		}
		inline friend Integer operator -(const Integer & Arg1,const Integer & Arg2)
		{
			return Arg1+(-Arg2);
		}
		inline friend Integer operator *(const Integer & Arg1,const Integer & Arg2)
		{
			int iResult=Arg1.m_iValue*Arg2.m_iValue;

			if (!Arg2.m_iValue)
				return iResult;
			else
			{
				int chk_back=iResult/Arg2.m_iValue;
				if (chk_back!=Arg1.m_iValue)
					throw Integer_OutOfBound(iResult);
				else if (Arg1==MIN_VALUE && Arg2.m_iValue==-1)
					throw Integer_OutOfBound(iResult);
				return iResult;
			}
		}
		inline friend Real operator / (const Integer & Arg1,const Integer & Arg2)
		{
			Real rArg1=Arg1.m_iValue,rArg2=Arg2.m_iValue;
			return rArg1/rArg2;
		}
		inline friend Integer operator MOD(const Integer & Arg1,const Integer & Arg2)
		{
			if (!Arg2.m_iValue)
				throw DividedByZero();
			else
			{
				int iResult=Arg1.m_iValue%Arg2.m_iValue;
				if (Arg1==MIN_VALUE && Arg2.m_iValue==-1)
					throw Integer_OutOfBound(iResult);
				return iResult;
			}
		}
		inline friend Integer operator DIV(const Integer & Arg1,const Integer & Arg2)
		{
			if (!Arg2.m_iValue)
				throw DividedByZero();
			else
			{
				int iResult=Arg1.m_iValue/Arg2.m_iValue;
				if (Arg1==MIN_VALUE && Arg2.m_iValue==-1)
					throw Integer_OutOfBound(iResult);
				return iResult;
			}
		}
		inline friend Integer operator ^(const Integer & Arg1,const Integer & Arg2)
		{
			int iBase=Arg1.m_iValue,iRadix=Arg2.m_iValue;
			if (iRadix<0)
				return 0;

			int iResult=1;
			while (iRadix)
			{
				if (iRadix & 1)
				{
					iResult*=iBase;
				}
				iRadix>>=1;
				iResult<<=1;
			}
			return iResult;
		}
		inline friend Integer bit_and(const Integer & Arg1,const Integer & Arg2)
		{return Arg1.m_iValue & Arg2.m_iValue;}
		inline friend Integer bit_or(const Integer & Arg1,const Integer & Arg2)
		{return Arg1.m_iValue | Arg2.m_iValue;}
		inline friend Integer bit_xor(const Integer & Arg1,const Integer & Arg2)
		{return Arg1.m_iValue ^ Arg2.m_iValue;}
		inline friend Integer bit_not(const Integer & Arg)
		{return	~Arg.m_iValue;}
		inline friend Integer bit_left(const Integer & Arg,const Integer & iCount)
		{
			if (iCount.m_iValue>=sizeof(int)*8 ||
				iCount.m_iValue<0)
				throw Integer_OutOfBound(((unsigned int)Arg.m_iValue)<<iCount.m_iValue);
			return ((unsigned int)Arg.m_iValue)<<iCount.m_iValue;
		}
		inline friend Integer bit_right(const Integer & Arg,const Integer & iCount)
		{
			if (iCount.m_iValue>=sizeof(int)*8 ||
				iCount.m_iValue<0)
				throw Integer_OutOfBound(((unsigned int)Arg.m_iValue)>>iCount.m_iValue);
			return ((unsigned int)Arg.m_iValue)>>iCount.m_iValue;
		}
		inline friend Integer algorithm_bit_left(const Integer & Arg,const Integer & iCount)
		{
			if (iCount.m_iValue>=sizeof(int)*8 ||
				iCount.m_iValue<0)
				throw Integer_OutOfBound(Arg.m_iValue<<iCount.m_iValue);
			return Arg.m_iValue<<iCount.m_iValue;
		}
		inline friend Integer algorithm_bit_right(const Integer & Arg,const Integer & iCount)
		{
			if (iCount.m_iValue>=sizeof(int)*8 ||
				iCount.m_iValue<0)
				throw Integer_OutOfBound(Arg.m_iValue>>iCount.m_iValue);
			return Arg.m_iValue>>iCount.m_iValue;
		}
		inline Integer & operator +=(const Integer & Arg)
		{
			*this=*this+Arg;
			return *this;
		}
		inline Integer & operator -=(const Integer & Arg)
		{
			*this=*this-Arg;
			return *this;
		}
		inline Integer & operator *=(const Integer & Arg)
		{
			*this=*this*Arg;
			return *this;
		}
		inline Integer & operator ++()
		{
			*this+=1;
			return *this;
		}
		inline Integer & operator --()
		{
			*this-=1;
			return *this;
		}
		inline Integer operator ++(int)
		{
			Integer iResult=*this;
			*this+=1;
			return iResult;
		}
		inline Integer operator --(int)
		{
			Integer iResult=*this;
			*this-=1;
			return iResult;
		}
		inline Integer & operator =(const Integer & iArg)
		{
			m_iValue=iArg.m_iValue;
			return *this;
		}
		Boolean operator ==(const Object &) const override;
		int hashCode() const override{
			return ::_hashCode(m_iValue);
		}
		inline friend Boolean operator ==(const Integer Arg1,const Integer & Arg2)
		{return Boolean(Arg1.m_iValue==Arg2.m_iValue);}
		inline friend Boolean operator !=(const Integer Arg1,const Integer & Arg2)
		{return NOT (Arg1==Arg2);}
		inline friend Boolean operator >(const Integer Arg1,const Integer & Arg2)
		{return Boolean(Arg1.m_iValue>Arg2.m_iValue);}
		inline friend Boolean operator <(const Integer Arg1,const Integer & Arg2)
		{return Boolean(Arg1.m_iValue<Arg2.m_iValue);}
		inline friend Boolean operator >=(const Integer Arg1,const Integer & Arg2)
		{return NOT (Arg1<Arg2);}
		inline friend Boolean operator <=(const Integer Arg1,const Integer & Arg2)
		{return NOT (Arg1>Arg2);}
	private:
		int m_iValue;
	};
}
#endif /* Action__Integer */
