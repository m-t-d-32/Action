#include <iostream>
#include "Scanner.h"
#include "Object.h"
#include "Integer_OutOfBound.h"

namespace Action
{
    Scanner::Scanner(std::istream & is) : m_istream(is), m_separators(" \n\t\v\r\f"){}

    Scanner::Scanner(const Scanner & another) : m_istream(another.m_istream), m_separators(" \n\t\v\r\f"){}

    bool Scanner::is_separator(char value)
    {
        return (m_separators.find(value).get_int() != -1);
    }

    void Scanner::set_separators(const String & new_separators)
    {
        m_separators = new_separators;
    }

    void Scanner::add_separators(const String & separators)
    {
        m_separators += separators;
    }

    void Scanner::add_separator(char separator)
    {
        m_separators += separator;
    }

    String Scanner::next()
    {
        String return_value;
        while (true)
        {
            char read_value = m_istream.get();
            if (is_separator(read_value))
                return return_value;
            return_value += read_value;
        }
    }

    String Scanner::next_all()
    {
        String return_value;
        while (true)
        {
            char read_value = m_istream.get();
            if (read_value == EOF || read_value == '\0')
                return return_value;
            return_value += read_value;
        }
    }

    String Scanner::next_line()
    {
        String return_value;
        while (true)
        {
            char read_value = m_istream.get();
            if (read_value == EOF || read_value == '\n' || read_value == '\0')
                return return_value;
            return_value += read_value;
        }
    }

    Integer Scanner::next_integer()
    {
        INT64 return_value = 0;
        bool is_negative = false;
        char read_value;
        while (true)
        {
            read_value = m_istream.get();
            if (!is_separator(read_value))
                break;
        }
        if (read_value == '-')
            is_negative = true;
        else if (read_value == '+')
            is_negative = false;
        else if (isdigit(read_value))
            return_value += (read_value - '0');
        else
            return return_value;
        while (true)
        {
            read_value = m_istream.get();
            if (!isdigit(read_value))
            {
                return return_value;
            }
            else
            {
                return_value *= 10;
                if (is_negative)
                {
                    return_value -= (read_value - '0');
                    if (return_value < Integer::MIN_VALUE.get_int())
                        throw Integer_OutOfBound((int)return_value);
                }
                else
                {
                    return_value += (read_value - '0');
                    if (return_value > Integer::MAX_VALUE.get_int())
                        throw Integer_OutOfBound((int)return_value);
                }
            }
        }
    }
}
