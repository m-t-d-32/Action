#include <iostream>
#include "Object.h"
#include <cmath>
#include <climits>
#include <cfloat>
#include "DividedByZero.h"
#include "Real_OutOfBound.h"
#include "Real_NotANumber.h"
#include "Boolean.h"

#ifndef Action__Real
#define Action__Real
namespace Action
{
#ifndef isnan
#define isnan(x) (x)!=(x)
#endif

#ifndef isinf
#define isinf(x) ((x)>DBL_MAX || (x)<-DBL_MAX)
#endif

    class Integer;
    class Real : public Object
    {
        public:
            const static Real MAX_VALUE;
            const static Real MIN_VALUE;
            static void set_precision(const Real & Precision)
            {
                PRECISION=Precision;
                if (isnan(Precision.m_fValue))
                    throw Real_NotANumber(Precision.m_fValue);
                else if (isinf(Precision.m_fValue) || Precision<0)
                    throw Real_OutOfBound(Precision.m_fValue);
            }

            Real()
            {
                m_fValue=0;
            }
            Real(int iArg)
            {
                m_fValue=iArg;
            }
            Real(const Integer &);
            Real(double fArg)
            {
                m_fValue=fArg;
                if (isnan(m_fValue))
                    throw Real_NotANumber(m_fValue);
                else if (isinf(m_fValue))
                    throw Real_OutOfBound(m_fValue);
            }
            Real(const Real & fArg)
            {
                m_fValue=fArg.m_fValue;
            }

            inline Real operator - () const
            {
                double fValue=-m_fValue;
                if (isinf(fValue))
                    throw Real_OutOfBound(fValue);
                return fValue;
            }

            inline friend Real operator + (const Real & fArg1,const Real & fArg2)
            {
                double fValue=fArg1.m_fValue+fArg2.m_fValue;
                if (isinf(fValue))
                    throw Real_OutOfBound(fValue);
                return fValue;
            }
            inline friend Real operator - (const Real & fArg1,const Real & fArg2)
            {
                return fArg1+(-fArg2);
            }
            inline friend Real operator * (const Real & fArg1,const Real & fArg2)
            {
                double fValue=fArg1.m_fValue*fArg2.m_fValue;
                if (isinf(fValue))
                    throw Real_OutOfBound(fValue);
                return fValue;
            }
            inline friend Real operator / (const Real & fArg1,const Real & fArg2)
            {
                if (fabs(fArg1.m_fValue)<PRECISION.m_fValue)
                    throw DividedByZero();
                double fValue=fArg1.m_fValue/fArg2.m_fValue;
                if (isinf(fValue))
                    throw Real_OutOfBound(fValue);
                return fValue;
            }
            inline friend Real operator ^ (const Real & fArg1,const Real & fArg2)
            {
                double fValue=pow(fArg1.m_fValue,fArg2.m_fValue);
                if (isnan(fValue))
                    throw Real_NotANumber(fValue);
                else if (isinf(fValue))
                    throw Real_OutOfBound(fValue);
                return fValue;
            }
            inline Real & operator +=(const Real & fArg)
            {
                *this=*this+fArg;
                return *this;
            }
            inline Real & operator -=(const Real & fArg)
            {
                *this=*this-fArg;
                return *this;
            }
            inline Real & operator *=(const Real & fArg)
            {
                *this=*this*fArg;
                return *this;
            }
            inline Real & operator /=(const Real & fArg)
            {
                *this=*this/fArg;
                return *this;
            }
            inline Real & operator ++()
            {
                *this+=1;
                return *this;
            }
            inline Real & operator --()
            {
                *this-=1;
                return *this;
            }
            inline Real operator ++(int)
            {
                Real fResult=*this;
                *this+=1;
                return *this;
            }
            inline Real operator --(int)
            {
                Real fResult=*this;
                *this+=1;
                return *this;
            }
            inline Real & operator =(const Real & fArg)
            {
                m_fValue=fArg.m_fValue;
                return *this;
            }
            int hash_code() const override
            {
                int times=sizeof(double)/sizeof(int);
                int result=1;
                for (int i=0; i<times; ++i)
                {
                    result*=*((int *)(&m_fValue)+i);
                    result >>= ((i ^ 23) % sizeof(int));
                }
                if (result<0)
                    result=-result;
                return ::_hashCode(result);
            }
            Boolean operator ==(const Object &) const override;
            inline friend Boolean operator ==(const Real Arg1,const Real & Arg2)
            {
                return Boolean(fabs(Arg1.m_fValue-Arg2.m_fValue)<=PRECISION);
            }
            inline friend Boolean operator !=(const Real Arg1,const Real & Arg2)
            {
                return NOT (Arg1==Arg2);
            }
            inline friend Boolean operator >(const Real Arg1,const Real & Arg2)
            {
                return Boolean(Arg1.m_fValue>Arg2.m_fValue);
            }
            inline friend Boolean operator <(const Real Arg1,const Real & Arg2)
            {
                return Boolean(Arg1.m_fValue<Arg2.m_fValue);
            }
            inline friend Boolean operator >=(const Real Arg1,const Real & Arg2)
            {
                return NOT (Arg1<Arg2);
            }
            inline friend Boolean operator <=(const Real Arg1,const Real & Arg2)
            {
                return NOT (Arg1>Arg2);
            }
            inline double get_double() const
            {
                return m_fValue;
            }
            String get_name() const override;
            String to_string() const override;
            Boolean compare_to(const Object &) const override;
        private:
            double m_fValue;
            static Real PRECISION;
    };
}
#endif	/* Action__Real */
