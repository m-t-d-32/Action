#include <iostream>
#include "Integer.h"
#include "ArrayList.h"
#include <cstring>
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
        String & operator =(const String &);

        virtual inline Integer length() const {return m_chars.size()-1;}
		virtual inline char & operator [](const Integer & iIndex) {return m_chars[iIndex];}
        virtual inline Boolean empty() const {return Boolean(length()==0);}
        virtual void append(const char &);
        virtual void append(const String &);
        virtual String operator +(const char &) const;
        virtual String operator +(const String &) const;
		virtual String operator +=(const char &);
        virtual String operator +=(const String &);
        virtual void insert(const Integer &, const char &);
		virtual void insert(const Integer &, const String &);
        virtual void clear();
        virtual Integer find(const String &) const;
        virtual Integer find(const char &) const;
		virtual inline const char * c_str() const {return m_chars.m_data;}
		virtual String getName() const override{ return "Action::String";}
		virtual String toString() const override{ return *this;}
		virtual void print(std::ostream & os=std::cout) const override;
		virtual int hashCode() const override;
		virtual Boolean compareTo(const Object &) const override;
		virtual Boolean operator ==(const Object &) const override;
		friend Boolean operator ==(const String & s1,const String & s2){
			return s1.m_chars==s2.m_chars;
		}
    private:
        ArrayList<char> m_chars;
    };
}

#endif /* Action__String */
