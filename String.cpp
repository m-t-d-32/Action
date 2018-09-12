#include <iostream>
#include "Object.h"
#include "String.h"
#include "ArrayList.hpp"
#include "Type_NotCorrespond.h"
#include <cstring>

namespace Action
{
    String::String()
    {
        m_chars.push_back('\0');
    }

    String::String(const char * chars_value)
    {
        while(*chars_value)
        {
            m_chars.push_back(*chars_value);
            ++chars_value;
        }
        m_chars.push_back('\0');
    }


    String::String(const String & string_value) : m_chars(string_value.m_chars) {}

    void String::append(const char & char_value)
    {
        m_chars.insert(length(), char_value);
    }

    void String::append(const String & string_value)
    {
        m_chars.insert(length(), string_value.m_chars, 0, string_value.length());
    }

    String String::operator + (const char & char_value) const
    {
        String return_string = *this;
        return_string.append(char_value);
        return return_string;
    }

    String String::operator + (const String & string_value) const
    {
        String return_string = *this;
        return_string.append(string_value);
        return return_string;
    }

    String String::operator += (const char & char_value)
    {
        *this = *this + char_value;
        return *this;
    }

    String String::operator += (const String & string_value)
    {
        *this = *this + string_value;
        return *this;
    }

    void String::clear()
    {
        m_chars.clear();
        m_chars.push_back('\0');
    }

    void String::insert(const Integer & position, const char & char_value)
    {
        m_chars.insert(position, char_value);
    }

    void String::insert(const Integer & position, const String & string_value)
    {
        m_chars.insert(position, string_value.m_chars, 0, string_value.length());
    }

    Integer String::find(const char & char_value) const
    {
        return m_chars.find(char_value);
    }

    Integer String::find(const String & string_value) const
    {
        //KMP Algorithm
        return 0;
    }

    String & String::operator= (const String & another_string)
    {
        m_chars = another_string.m_chars;
        return *this;
    }

    void String::print(std::ostream & print_stream) const override
    {
        print_stream << m_chars.m_data;
    }

    int String::hash_code() const override
    {
        return ::_str_hashCode(m_chars.m_data, length().get_int());
    }

    Boolean String::operator == (const Action::Object & another_one) const override
    {
        try
        {
            const String & another_string = dynamic_cast<const String &>(another_one);
            return Boolean(strcmp(m_chars.m_data, another_string.m_chars.m_data) == 0);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    Boolean String::compare_to(const Object & another_one) const override
    {
        try
        {
            const String & another_string = dynamic_cast<const String &>(another_one);
            return Boolean(strcmp(m_chars.m_data, another_string.m_chars.m_data) < 0);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
}
