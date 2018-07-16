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
	
	String::String(const char * chsOfstr)
	{
		while (*chsOfstr)
		{
			m_chars.push_back(*chsOfstr);
			++chsOfstr;
		}
		m_chars.push_back('\0');
	}

	
	String::String(const String & Argstr)
	{
		for (int i=0;i<=Argstr.length();++i)
		{
			m_chars.push_back(Argstr.m_chars.at(i));
		}
	}

	
	void String::append(const char & chArg)
	{
		m_chars.insert(m_chars.size(),chArg);
	}

    
    void String::append(const String & strArg)
    {
        m_chars.insert(length(),strArg.m_chars,0,strArg.length());
    }

    
    String String::operator +(const char & chArg) const
    {
        String tmp_str=*this;
        tmp_str.append(chArg);
        return tmp_str;
    }

    
    String String::operator +(const String & strArg) const
    {
        String tmp_str=*this;
        tmp_str.append(strArg);
        return tmp_str;
    }

	String String::operator+=(const char & chArg)
	{
		*this=*this+chArg;
		return *this;
	}
	
	String String::operator+=(const String & strArg)
	{
		*this=*this+strArg;
		return *this;
	}

	void String::clear()
	{
		m_chars.clear();
		m_chars.push_back('\0');
	}

	
	void String::insert(const Integer & iArgOfPos,const char & chArg)
	{
		m_chars.insert(iArgOfPos,chArg);
	}

	
	void String::insert(const Integer & iArgOfPos,const String & strArg)
	{
        m_chars.insert(iArgOfPos,strArg.m_chars,0,strArg.length());
	}

	
	Integer String::find(const char & chFind) const
	{
		return m_chars.find(chFind);
	}
	
	Integer String::find(const String & strFind) const
	{
		//KMP Algorithm
		return 0;
	}
		
	String & String::operator=(const String & strArg)
	{
		m_chars=strArg.m_chars;
		return *this;
	}

	
	void String::print(std::ostream & os) const
	{
		for (int i=0;i<length();++i)
		{
			os<<m_chars.m_data[i];
		}
	}

	Boolean String::operator ==(const Action::Object & arg) const
	{
		try
		{
			const String & _my_str=dynamic_cast<const String &> (arg);
			return Boolean(strcmp(m_chars.m_data,_my_str.m_chars.m_data)==0);
		}
		catch (std::bad_cast)
		{
			throw Type_NotCorrespond();
		}
	}

	Boolean String::compareTo(const Object & arg) const
	{
		try
		{
			const String & _my_str=dynamic_cast<const String &> (arg);
			return Boolean(strcmp(m_chars.m_data,_my_str.m_chars.m_data)>0);
		}
		catch (std::bad_cast)
		{
			throw Type_NotCorrespond();
		}
	}

	String::~String()
	{
	}
}
