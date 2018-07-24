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

        inline Integer length() const {return m_chars.size()-1;}
		inline char & operator [](const Integer & iIndex) {return m_chars[iIndex];}
        inline Boolean empty() const {return Boolean(length()==0);}
        void append(const char &);
        void append(const String &);
        String operator +(const char &) const;
        String operator +(const String &) const;
		String operator +=(const char &);
        String operator +=(const String &);
        void insert(const Integer &, const char &);
		void insert(const Integer &, const String &);
        void clear();
        Integer find(const String &) const;
        Integer find(const char &) const;
		inline const char * c_str() const {return m_chars.m_data;}
		String getName() const override{ return "Action::String";}
		String toString() const override{ return *this;}
		void print(std::ostream & os=std::cout) const override;
		int hashCode() const override;
		Boolean compareTo(const Object &) const override;
		Boolean operator ==(const Object &) const override;
		friend Boolean operator ==(const String & s1,const String & s2){
			return s1.m_chars==s2.m_chars;
		}
    private:
        ArrayList<char> m_chars;
    };
}
#endif /* Action__String */
