#include <iostream>
#include "Object.h"

#ifndef Action__Byte
#define Action__Byte
namespace Action
{
    class Boolean;
    class Byte :public Object
    {
        private:
            char m_bValue;
        public:
            Byte()
            {
                m_bValue = 0;
            }
            Byte(char arg)
            {
                m_bValue = arg;
            }
            Byte(const Byte & arg)
            {
                m_bValue = arg.m_bValue;
            }
            Byte & operator =(const Byte & arg)
            {
                m_bValue=arg.m_bValue;
                return *this;
            }
            virtual inline char get_val() const
            {
                return m_bValue;
            }
            virtual inline void set_val(char arg)
            {
                m_bValue = arg;
            }
            virtual Boolean operator ==(const Object & arg) const override;
            virtual String get_name() const override;
            virtual String to_string() const override;
            virtual int hash_code() const override
            {
                return ::_hashCode(m_bValue);
            }
    };
}
#endif /* Action__Byte */
