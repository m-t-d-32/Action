#include <iostream>
#include "Scanner.h"
#include "Object.h"
#include "Integer_OutOfBound.h"

namespace Action
{
    Scanner::Scanner(std::istream & is) : m_istream(is), m_separators(" \n\t\v\r\f") {}

    Scanner::Scanner(const Scanner & another) : m_istream(another.m_istream), m_separators(" \n\t\v\r\f") {}

    bool Scanner::is_separator(char value) const
    {
        return (m_separators.find(value).get_int() != -1);
    }

    void Scanner::clear_separator()
    {
        while(true)
        {
            char read_value = m_istream.peek();
            if(!is_separator(read_value))
                break;
            m_istream.get();
        }
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
        clear_separator();
        String return_value;
        while(true)
        {
            char read_value = m_istream.peek();
            if(is_separator(read_value) || read_value == EOF)
                return return_value;
            m_istream.get();
            return_value += read_value;
        }
    }

    String Scanner::next_all()
    {
        String return_value;
        while(true)
        {
            char read_value = m_istream.peek();
            if(read_value == EOF)
                return return_value;
            m_istream.get();
            return_value += read_value;
        }
    }

    String Scanner::next_line()
    {
        String return_value;
        while(true)
        {
            char read_value = m_istream.peek();
            if(read_value == EOF)
                return return_value;
            else if(read_value == '\n')
            {
                m_istream.get();
                return return_value;
            }
            m_istream.get();
            return_value += read_value;
        }
    }

    Integer Scanner::next_integer()
    {
        clear_separator();
        INT64 return_value = 0;
        bool is_negative = false;
        char read_value = m_istream.peek();
        if(read_value == '-')
            is_negative = true;
        else if(read_value == '+')
            is_negative = false;
        else if(isdigit(read_value))
            return_value += (read_value - '0');
        else
            return return_value;
        m_istream.get();
        while(true)
        {
            read_value = m_istream.peek();
            if(!isdigit(read_value))
            {
                return return_value;
            }
            else
            {
                return_value *= 10;
                if(is_negative)
                {
                    return_value -= (read_value - '0');
                    if(return_value < Integer::MIN_VALUE.get_int())
                        throw Integer_OutOfBound((int)return_value);
                }
                else
                {
                    return_value += (read_value - '0');
                    if(return_value > Integer::MAX_VALUE.get_int())
                        throw Integer_OutOfBound((int)return_value);
                }
            }
            m_istream.get();
        }
    }

    Real Scanner::next_real()
    {
        clear_separator();
        double return_value = 0;
        bool is_negative = false;
        double after_dot = 0;
        char read_value = m_istream.peek();
        if(read_value == '-')
            is_negative = true;
        else if(read_value == '+')
            is_negative = false;
        else if(read_value == '.')
            after_dot = 1;
        else if(isdigit(read_value))
            return_value += (read_value - '0');
        else
            return return_value;
        m_istream.get();
        while(true)
        {
            read_value = m_istream.peek();
            if(isdigit(read_value))
            {
                if(after_dot != 0)
                {
                    after_dot *= 10;
                    return_value += (1 / after_dot) * (read_value - '0');
                }
                else
                {
                    return_value *= 10;
                    return_value += (read_value - '0');
                }
            }
            else if(read_value == '.')
            {
                if(after_dot != 0)
                {
                    return is_negative ? (-return_value) : return_value;
                }
                else
                {
                    after_dot = 1;
                }
            }
            else
            {
                return is_negative ? (-return_value) : return_value;
            }
            m_istream.get();
        }
    }

    void Scanner::ungets(const ArrayList<char> & buffer)
    {
        for(int i = buffer.size().get_int() - 1; i >= 0 ; --i)
        {
            m_istream.putback(buffer.at(i));
        }
    }

    Boolean Scanner::has_next()
    {
        ArrayList<char> buffer;
        while(true)
        {
            char read_value = m_istream.peek();
            if(read_value == EOF)
            {
                ungets(buffer);
                return Boolean::False;
            }
            else if(!is_separator(read_value))
            {
                ungets(buffer);
                return Boolean::True;
            }
            buffer.push_back(read_value);
            m_istream.get();
        }
    }

    Boolean Scanner::has_next_integer()
    {
        ArrayList<char> buffer;
        while(true)
        {
            char read_value = m_istream.peek();
            if(read_value == EOF)
            {
                ungets(buffer);
                return Boolean::False;
            }
            else
            {
                buffer.push_back(read_value);
                m_istream.get();
                if(!is_separator(read_value))
                {
                    if(isdigit(read_value))
                    {
                        ungets(buffer);
                        return Boolean::True;
                    }
                    else if(read_value == '+' || read_value == '-')
                    {
                        read_value = m_istream.peek();
                        if(isdigit(read_value))
                        {
                            ungets(buffer);
                            return Boolean::True;
                        }
                        else
                        {
                            ungets(buffer);
                            return Boolean::False;
                        }
                    }
                    else
                    {
                        ungets(buffer);
                        return Boolean::False;
                    }
                }
            }
        }
    }

    Boolean Scanner::has_next_real()
    {
        ArrayList<char> buffer;
        while(true)
        {
            char read_value = m_istream.peek();
            if(read_value == EOF)
            {
                ungets(buffer);
                return Boolean::False;
            }
            else
            {
                buffer.push_back(read_value);
                m_istream.get();
                if(!is_separator(read_value))
                {
                    if(isdigit(read_value))
                    {
                        ungets(buffer);
                        return Boolean::True;
                    }
                    else if(read_value == '.')
                    {
                        read_value = m_istream.peek();
                        if(isdigit(read_value))
                        {
                            ungets(buffer);
                            return Boolean::True;
                        }
                        else
                        {
                            ungets(buffer);
                            return Boolean::False;
                        }
                    }
                    else if(read_value == '+' || read_value == '-')
                    {
                        read_value = m_istream.peek();
                        if(isdigit(read_value))
                        {
                            ungets(buffer);
                            return Boolean::True;
                        }
                        else if(read_value == '.')
                        {
                            buffer.push_back(read_value);
                            m_istream.get();
                            read_value = m_istream.peek();
                            if(isdigit(read_value))
                            {
                                ungets(buffer);
                                return Boolean::True;
                            }
                            else
                            {
                                ungets(buffer);
                                return Boolean::False;
                            }
                        }
                        else
                        {
                            ungets(buffer);
                            return Boolean::False;
                        }
                    }
                    else
                    {
                        ungets(buffer);
                        return Boolean::False;
                    }
                }
            }
        }
    }
}
