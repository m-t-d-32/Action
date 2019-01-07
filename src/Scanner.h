#include <iostream>
#include <stdio.h>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include <cctype>

/*
    既然选择了远方
    便只顾风雨兼程
*/

#ifndef Action__Scanner
#define Action__Scanner
namespace Action
{
    class Scanner
    {
        public:
            Scanner(std::istream & is = std::cin);
            Scanner(const Scanner &);
            Boolean has_next();
            Boolean has_next_integer();
            Boolean has_next_real();
            Integer next_integer();
            Real next_real();
            String next_line();
            String next();
            void set_separators(const String &);
            void add_separators(const String &);
            void add_separator(char);
            String next_all();
            void clear_separator();
            char peek() const;
            char get();
        private:
            void ungets(const ArrayList<char> &);
            bool is_separator(char) const;
            std::istream & m_istream;
            String m_separators;
    };
}
#endif /* Action__Scanner */
