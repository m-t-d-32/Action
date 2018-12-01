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

    String String::operator += (const char & char_value)
    {
        append(char_value);
        return *this;
    }

    String String::operator += (const String & string_value)
    {
        append(string_value);
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

    Integer String::find(const char & char_value, const Integer & begin) const
    {
        for (int i = begin.get_int(); i < m_chars.size().get_int(); ++i)
        {
            if (m_chars.at(i) == char_value)
                return i;
        }
        return -1;
    }

    Integer String::find(const String & string_value, const Integer & begin) const
    {
        int this_length = length().get_int(), another_length = string_value.length().get_int();
        if(another_length == 0 || this_length - begin.get_int() < another_length)
            return -1;
        int * nexts = new int[another_length];
        nexts[0] = 0;
        int src_index = 0, dest_index = 0;
        while(dest_index != another_length)
        {
            if(string_value.at(src_index) == string_value.at(dest_index + 1))
            {
                nexts[++dest_index] = ++src_index;
            }
            else if(!src_index)
            {
                nexts[++dest_index] = 0;
            }
            else
            {
                src_index = nexts[src_index - 1];
            }
        }
        for(int i = begin.get_int(); i <= this_length - another_length;)
        {
            bool found = true;
            for(int j = 0; j < another_length; ++j)
            {
                if(at(i + j) != string_value.at(j))
                {
                    i += (j == 0 ? 1 : j - nexts[j - 1]);
                    found = false;
                    break;
                }
            }
            if(found)
            {
                delete []nexts;
                return i;
            }
        }
        delete []nexts;
        return -1;
    }

    String & String::operator= (const String & another_string)
    {
        m_chars = another_string.m_chars;
        return *this;
    }

    void String::print(std::ostream & print_stream) const
    {
        print_stream << m_chars.m_data;
    }

    int String::hash_code() const
    {
        return ::_str_hashCode(m_chars.m_data, length().get_int());
    }

    Boolean String::operator == (const Action::Object & another_one) const
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

    Boolean String::compare_to(const Object & another_one) const
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

    String operator + (const String & str_1, const String & str_2)
    {
        String return_value = str_1;
        return_value.append(str_2);
        return return_value;
    }
    String operator + (const String & str_1, const char * str_2)
    {
        return str_1 + String(str_2);
    }
    String operator + (const char * str_1, const String & str_2)
    {
        return String(str_1) + str_2;
    }
}
