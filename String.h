#include <iostream>
#include "Integer.h"
#include "ArrayList.h"
#include <cstring>

/*
    人的一切痛苦
    本质上都是对自己的无能的愤怒
*/

#ifndef Action__String
#define Action__String
namespace Action
{
    template <class T>
    class ArrayList;

    class String : public Object
    {
        public:
            String();
            String(const char *);
            String(const String &);
            String & operator = (const String &);

            inline Integer length() const
            {
                return m_chars.size() - 1;
            }
            inline char & operator [](const Integer & index)
            {
                return m_chars[index];
            }
            inline Boolean empty() const
            {
                return Boolean(length() == 0);
            }
            void append(const char &);
            void append(const String &);
            String operator + (const char &) const;
            String operator + (const String &) const;
            String operator += (const char &);
            String operator += (const String &);
            void insert(const Integer &, const char &);
            void insert(const Integer &, const String &);
            void clear();
            Integer find(const String &) const;
            Integer find(const char &) const;
            inline const char * c_str() const
            {
                return m_chars.m_data;
            }
            String get_name() const override
            {
                return "Action::String";
            }
            String to_string() const override
            {
                return *this;
            }
            void print(std::ostream & os = std::cout) const override;
            int hash_code() const override;
            Boolean compare_to(const Object &) const override;
            Boolean operator == (const Object &) const override;
            friend Boolean operator == (const String & value_1, const String & value_2)
            {
                return value_1.m_chars == value_2.m_chars;
            }
        private:
            ArrayList<char> m_chars;
    };
}
#endif /* Action__String */
