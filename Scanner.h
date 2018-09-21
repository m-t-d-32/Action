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

namespace Action
{
    class Scanner
    {
        public:
            Scanner(std::istream & is = std::cin);
            Scanner(const Scanner &);
            Integer next_integer();
            Real next_real();
            String next_line();
            String next();
            void set_separators(const String &);
            void add_separators(const String &);
            void add_separator(char);
            String next_all();
        private:
            bool is_separator(char);
            std::istream & m_istream;
            String m_separators;
    };
}
