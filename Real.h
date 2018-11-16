#include <iostream>
#include "Object.h"
#include <cmath>
#include <climits>
#include <cfloat>
#include "DividedByZero.h"
#include "Real_OutOfBound.h"
#include "Real_NotANumber.h"
#include "Boolean.h"

/*
    祝你岁月无波澜
	敬我余生不悲欢
*/

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
            static void set_precision(const Real & new_precision)
            {
                PRECISION = new_precision;
                if(isnan(new_precision.m_value))
                    throw Real_NotANumber(new_precision.m_value);
                else if(isinf(new_precision.m_value) || new_precision < 0)
                    throw Real_OutOfBound(new_precision.m_value);
            }
            Real()
            {
                m_value = 0;
            }
            Real(int value)
            {
                m_value = value;
            }
            Real(const Integer &);
            Real(double value)
            {
                m_value = value;
                if(isnan(m_value))
                    throw Real_NotANumber(m_value);
                else if(isinf(m_value))
                    throw Real_OutOfBound(m_value);
            }
            Real(const Real & another)
            {
                m_value = another.m_value;
            }
            inline Real operator - () const
            {
                double result = -m_value;
                if(isinf(result))
                    throw Real_OutOfBound(result);
                return result;
            }

            inline friend Real operator + (const Real & value_1, const Real & value_2)
            {
                double result = value_1.m_value + value_2.m_value;
                if(isinf(result))
                    throw Real_OutOfBound(result);
                return result;
            }
            inline friend Real operator - (const Real & value_1, const Real & value_2)
            {
                return value_1 + (-value_2);
            }
            inline friend Real operator * (const Real & value_1, const Real & value_2)
            {
                double result = value_1.m_value * value_2.m_value;
                if(isinf(result))
                    throw Real_OutOfBound(result);
                return result;
            }
            inline friend Real operator / (const Real & value_1, const Real & value_2)
            {
                if(fabs(value_2.m_value) < PRECISION.m_value)
                    throw DividedByZero();
                double result = value_1.m_value / value_2.m_value;
                if(isinf(result))
                    throw Real_OutOfBound(result);
                return result;
            }
            inline friend Real operator ^ (const Real & value_1, const Real & value_2)
            {
                double result = pow(value_1.m_value, value_2.m_value);
                if(isnan(result))
                    throw Real_NotANumber(result);
                else if(isinf(result))
                    throw Real_OutOfBound(result);
                return result;
            }
            inline Real & operator += (const Real & value)
            {
                *this = *this + value;
                return *this;
            }
            inline Real & operator -= (const Real & value)
            {
                *this = *this - value;
                return *this;
            }
            inline Real & operator *= (const Real & value)
            {
                *this = *this * value;
                return *this;
            }
            inline Real & operator /= (const Real & value)
            {
                *this = *this / value;
                return *this;
            }
            inline Real & operator ++()
            {
                *this += 1;
                return *this;
            }
            inline Real & operator --()
            {
                *this -= 1;
                return *this;
            }
            inline Real operator ++ (int)
            {
                Real result = *this;
                *this += 1;
                return result;
            }
            inline Real operator -- (int)
            {
                Real result = *this;
                *this += 1;
                return result;
            }
            inline Real & operator = (const Real & value)
            {
                m_value = value.m_value;
                return *this;
            }
            int hash_code() const override
            {
                int count = sizeof(double) / sizeof(int);
                int result = 1;
                for(int i = 0; i < count; ++i)
                {
                    result *= * ((int *)(&m_value) + i);
                    result >>= ((i ^ 23) % sizeof(int));
                }
                if(result < 0)
                    result = -result;
                return ::_hashCode(result);
            }
            Boolean operator == (const Object &) const override;
            inline friend Boolean operator == (const Real value_1, const Real & value_2)
            {
                return Boolean(fabs(value_1.m_value - value_2.m_value) <= PRECISION);
            }
            inline friend Boolean operator != (const Real value_1, const Real & value_2)
            {
                return NOT(value_1 == value_2);
            }
            inline friend Boolean operator > (const Real value_1, const Real & value_2)
            {
                return Boolean(value_1.m_value > value_2.m_value);
            }
            inline friend Boolean operator < (const Real value_1, const Real & value_2)
            {
                return Boolean(value_1.m_value < value_2.m_value);
            }
            inline friend Boolean operator >= (const Real value_1, const Real & value_2)
            {
                return NOT(value_1 < value_2);
            }
            inline friend Boolean operator <= (const Real value_1, const Real & value_2)
            {
                return NOT(value_1 > value_2);
            }
            inline double get_double() const
            {
                return m_value;
            }
            String get_name() const override;
            String to_string() const override;
            Boolean compare_to(const Object &) const override;
        private:
            double m_value;
            static Real PRECISION;
    };
}
#endif	/* Action__Real */
