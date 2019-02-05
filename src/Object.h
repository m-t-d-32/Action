#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <limits.h>
#define __MY__VERSION__98 1

/*
    每一个微不足道的梦想
    都值得 去出发
*/

#ifndef Action__Object
#define Action__Object

#ifdef __cplusplus
extern "C"
{
#endif

int _hashCode(int);
int _str_hashCode(char *, int);

#ifdef __cplusplus
}
#endif

#if __cplusplus < 201103L
#define override
#endif

#ifdef _MSC_VER
#define INT64 __int64
#if _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif
#else
#define INT64 long long
#endif

#define BAD_MEMORY_0 0x00
#define BAD_MEMORY_1 0x01
#define BAD_MEMORY_2 0x02
#define BAD_MEMORY_3 0x03

#define DEFAULT_BUFFER_SIZE 0xff

namespace Action
{
    class String;
    class Boolean;
    class Integer;
    class Object
    {
        public:
            virtual void print(std::ostream & os = std::cout) const;
            virtual void println(std::ostream & os = std::cout) const;
            inline Integer get_version() const;
            virtual String get_name() const;
            virtual String to_string() const;
            virtual Boolean compare_to(const Object &) const;
            virtual Boolean operator == (const Object &) const;
            virtual Boolean operator != (const Object &) const;
            virtual int hash_code() const;
            virtual ~Object();
    };
    String operator + (const Object &, const String &);
    String operator + (const String &, const Object &);
    String operator + (const Object &, const char *);
    String operator + (const char *, const Object &);
}

#endif /* Action__Object */
