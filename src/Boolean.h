#include <iostream>
#include "Byte.h"
#include "Type_NotCorrespond.h"

/*
    我颠覆了整个世界
    只为摆正你的倒影
*/

#ifndef Action__Boolean
#define Action__Boolean
namespace Action
{
#define AND &&
#define OR ||
#define NOT !
#define XOR ^
    class Boolean: public Byte
    {
        public:
            const static Boolean True;
            const static Boolean False;
            Boolean() {}
            Boolean(const Boolean & another) : Byte(another) {}
            Boolean & operator = (const Boolean & another)
            {
                another.get_val() ? (set_val(-1)) : (set_val(0));
                return *this;
            }
            explicit Boolean(char value)
            {
                if(value)
                    set_val(-1);
                else
                    set_val(0);
            }
            inline friend Boolean operator AND(const Boolean & value_1, const Boolean & value_2)
            {
                if (!value_1.get_val())
                    return False;
                return Boolean(value_2.get_val());
            }
            inline friend Boolean operator OR(const Boolean & value_1, const Boolean & value_2)
            {
                if (value_1.get_val())
                    return True;
                return Boolean(value_2.get_val());
            }
            inline friend Boolean operator XOR(const Boolean & value_1, const Boolean & value_2)
            {
                return Boolean(value_1.get_val() ^ value_2.get_val());
            }
            inline friend Boolean operator NOT(const Boolean & value)
            {
                return Boolean(!value.get_val());
            }
            Boolean operator == (const Object & another_one) const override
            {
                try
                {
                    const Boolean & another_boolean = dynamic_cast<const Boolean &>(another_one);
                    return Boolean((get_val() && another_boolean.get_val()) || (!get_val() && !another_boolean.get_val()));
                }
                catch(std::bad_cast)
                {
                    throw Type_NotCorrespond();
                }
            }
            inline friend Boolean operator == (const Boolean & value_1, const Boolean & value_2)
            {
                return Boolean((value_1.get_val() && value_2.get_val()) || (!value_1.get_val() && !value_2.get_val()));
            }
            operator bool() const
            {
                return get_val() ? true : false;
            }
			int hash_code() const override;
            String get_name() const override;
            String to_string() const override;
    };
}
#endif /* Action__Boolean */
