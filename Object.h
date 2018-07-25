#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <limits.h>
#define __MY__VERSION__98 0

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

#if _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif

namespace Action
{
	class String;
	class Boolean;
	class Integer;
    class Object
    {
    public:
        virtual void print(std::ostream & os=std::cout) const;
        virtual void println(std::ostream & os=std::cout) const;
        inline Integer get_version() const;
        virtual String get_name() const;
        virtual String to_string() const;
        virtual Boolean compare_to(const Object &) const;
		virtual Boolean operator ==(const Object &) const;
		virtual Boolean operator !=(const Object &) const;
        virtual int hash_code() const;
        virtual ~Object();
    };
}

#endif /* Action__Object */
