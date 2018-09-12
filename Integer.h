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

            Integer()
            {
                m_value = 0;
            }
            Integer(int value)
            {
                m_value = value;
            }
            Integer(const Integer & value)
            {
                m_value = value.m_value;
            }
            explicit Integer(const Real & value)
            {
                m_value = (int) value.get_double();
            }

            String get_name() const override;
            String to_string() const override;
            Boolean compare_to(const Object &) const override;

            inline int get_int() const
            {
                return m_value;
            }

            inline friend Integer operator - (const Integer & value)
            {
                if(value == MIN_VALUE)
                    throw Integer_OutOfBound(-value.m_value);
                return -value.m_value;
            }
            inline friend Integer operator + (const Integer & value_1, const Integer & value_2)
            {
                int result = value_1.m_value + value_2.m_value;
                if(value_1.m_value > 0 && value_2.m_value > 0 && result <= 0)
                    throw Integer_OutOfBound(result);
                else if(value_1.m_value < 0 && value_2.m_value < 0 && result >= 0)
                    throw Integer_OutOfBound(result);
                return result;
            }
            inline friend Integer operator - (const Integer & value_1, const Integer & value_2)
            {
                return value_1 + (-value_2);
            }
            inline friend Integer operator * (const Integer & value_1, const Integer & value_2)
            {
                int result = value_1.m_value * value_2.m_value;

                if(!value_2.m_value)
                    return result;
                else
                {
                    int chk_back = result / value_2.m_value;
                    if(chk_back != value_1.m_value)
                        throw Integer_OutOfBound(result);
                    else if(value_1 == MIN_VALUE && value_2.m_value == -1)
                        throw Integer_OutOfBound(result);
                    return result;
                }
            }
            inline friend Real operator / (const Integer & value_1, const Integer & value_2)
            {
                Real value_real_1 = value_1.m_value, value_real_2 = value_2.m_value;
                return value_real_1 / value_real_2;
            }
            inline friend Integer operator MOD(const Integer & value_1, const Integer & value_2)
            {
                if(!value_2.m_value)
                    throw DividedByZero();
                else
                {
                    int result = value_1.m_value % value_2.m_value;
                    if(value_1 == MIN_VALUE && value_2.m_value == -1)
                        throw Integer_OutOfBound(result);
                    return result;
                }
            }
            inline friend Integer operator DIV(const Integer & value_1, const Integer & value_2)
            {
                if(!value_2.m_value)
                    throw DividedByZero();
                else
                {
                    int result = value_1.m_value / value_2.m_value;
                    if(value_1 == MIN_VALUE && value_2.m_value == -1)
                        throw Integer_OutOfBound(result);
                    return result;
                }
            }
            inline friend Integer operator ^ (const Integer & value_1, const Integer & value_2)
            {
                int base = value_1.m_value, radix = value_2.m_value;
                if(radix < 0)
                    return 0;

                int result = 1;
                while(radix)
                {
                    if(radix & 1)
                    {
                        result *= base;
                    }
                    radix >>= 1;
                    result <<= 1;
                }
                return result;
            }
            inline friend Integer bit_and(const Integer & value_1, const Integer & value_2)
            {
                return value_1.m_value & value_2.m_value;
            }
            inline friend Integer bit_or(const Integer & value_1, const Integer & value_2)
            {
                return value_1.m_value | value_2.m_value;
            }
            inline friend Integer bit_xor(const Integer & value_1, const Integer & value_2)
            {
                return value_1.m_value ^ value_2.m_value;
            }
            inline friend Integer bit_not(const Integer & value)
            {
                return	~value.m_value;
            }
            inline friend Integer bit_left(const Integer & value, const Integer & count)
            {
                if(count.m_value >= sizeof(int) * 8 ||
                        count.m_value < 0)
                    throw Integer_OutOfBound(((unsigned int) value.m_value) << count.m_value);
                return ((unsigned int) value.m_value) << count.m_value;
            }
            inline friend Integer bit_right(const Integer & value, const Integer & count)
            {
                if(count.m_value >= sizeof(int) * 8 ||
                        count.m_value < 0)
                    throw Integer_OutOfBound(((unsigned int) value.m_value) >> count.m_value);
                return ((unsigned int) value.m_value) >> count.m_value;
            }
            inline friend Integer algorithm_bit_left(const Integer & value, const Integer & count)
            {
                if(count.m_value >= sizeof(int) * 8 ||
                        count.m_value < 0)
                    throw Integer_OutOfBound(value.m_value << count.m_value);
                return value.m_value << count.m_value;
            }
            inline friend Integer algorithm_bit_right(const Integer & value, const Integer & count)
            {
                if(count.m_value >= sizeof(int) * 8 ||
                        count.m_value < 0)
                    throw Integer_OutOfBound(value.m_value >> count.m_value);
                return value.m_value >> count.m_value;
            }
            inline Integer & operator += (const Integer & value)
            {
                *this = *this + value;
                return *this;
            }
            inline Integer & operator -= (const Integer & value)
            {
                *this = *this - value;
                return *this;
            }
            inline Integer & operator *= (const Integer & value)
            {
                *this = *this * value;
                return *this;
            }
            inline Integer & operator ++()
            {
                *this += 1;
                return *this;
            }
            inline Integer & operator --()
            {
                *this -= 1;
                return *this;
            }
            inline Integer operator ++ (int)
            {
                Integer result = *this;
                *this += 1;
                return result;
            }
            inline Integer operator -- (int)
            {
                Integer result = *this;
                *this -= 1;
                return result;
            }
            inline Integer & operator = (const Integer & value)
            {
                m_value = value.m_value;
                return *this;
            }
            Boolean operator == (const Object &) const override;
            int hash_code() const override
            {
                return ::_hashCode(m_value);
            }
            inline friend Boolean operator == (const Integer value_1, const Integer & value_2)
            {
                return Boolean(value_1.m_value == value_2.m_value);
            }
            inline friend Boolean operator != (const Integer value_1, const Integer & value_2)
            {
                return NOT(value_1 == value_2);
            }
            inline friend Boolean operator > (const Integer value_1, const Integer & value_2)
            {
                return Boolean(value_1.m_value > value_2.m_value);
            }
            inline friend Boolean operator < (const Integer value_1, const Integer & value_2)
            {
                return Boolean(value_1.m_value < value_2.m_value);
            }
            inline friend Boolean operator >= (const Integer value_1, const Integer & value_2)
            {
                return NOT(value_1 < value_2);
            }
            inline friend Boolean operator <= (const Integer value_1, const Integer & value_2)
            {
                return NOT(value_1 > value_2);
            }
        private:
            int m_value;
    };
}
#endif /* Action__Integer */
