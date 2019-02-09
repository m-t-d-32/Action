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
    class String : public ArrayList<char>
    {
        public:
            String();
            String(const char *);
            String & operator = (const String &);

            inline Integer length() const
            {
                return size() - 1;
            }
            inline Boolean empty() const override
            {
                return Boolean(length() == 0);
            }
            void append(char);
            void append(const String &);
            String operator += (char);
            String operator += (const String &);
            void insert(Integer, char);
            void insert(Integer, const String &);
            void clear() override;
            Integer find(const String &, Integer begin = 0) const;
            Integer find(char, Integer begin = 0) const;
            inline const char * c_str() const
            {
                return m_data;
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
            String slice(Integer, Integer) const;
            ArrayList<String> split(const String & delim = "\t\f\n ") const;
            ArrayList<String> split(char) const;
            ArrayList<String> split_long(const String & delim = " ") const;
            Boolean compare_to(const Object &) const override;
            Boolean operator == (const Object &) const override;
            
            String lstrip(char delim) const;
            String rstrip(char delim) const;
            String strip(char delim) const;
            String lstrip(const String & delims = "\t\f\n ") const;
            String rstrip(const String & delims = "\t\f\n ") const;
            String strip(const String & delims = "\t\f\n ") const;            
            String left(Integer length) const;
            String right(Integer length) const;
    };

    String operator + (const String &, const String &);
    String operator + (const String &, const char *);
    String operator + (const char *, const String &);
}
#endif /* Action__String */
