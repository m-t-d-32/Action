#include <iostream>
#include "Integer.h"
#include "ArrayList.h"
#include "BitSet_OutOfRange.h"
#include "Boolean.h"
#include "String.h"
/*

*/

#ifndef Action__BitSet
#define Action__BitSet
namespace Action
{
	class BitSet: public Object
	{
	public:
		BitSet();
		virtual void push_back(Boolean);
		virtual void set(Integer,Boolean);
		virtual Boolean get(Integer);
		virtual ~BitSet();
		virtual Boolean operator ==(const Object & Arg) const override;
		virtual String getName() const override{
			return "Action::BitSet";
		}
		virtual String toString() const override{
			return m_data.toString();
		}
	private:
		const static int BITCOUNT=8*sizeof(char);
		int m_iptrByte,m_iptrBit;
		ArrayList<char> m_data;
	};

	BitSet::BitSet()
	{
		m_iptrByte=m_iptrBit=0;
	}

	void BitSet::push_back(Boolean bArgOfValue)
	{
		if (!m_iptrBit)
			m_data.push_back(0);

		char tmp_Value=m_data[m_iptrByte];
		tmp_Value=bArgOfValue?(tmp_Value | (1 << m_iptrBit)):
				(tmp_Value & (~(1 << m_iptrBit)));
		m_data[m_iptrByte]=tmp_Value;

		++m_iptrBit;
		if (m_iptrBit>BITCOUNT)
		{
			m_iptrBit=0;
			++m_iptrByte;
		}
	}

	void BitSet::set(Integer iArgOfPos, Boolean bArgOfValue)
	{
		int iptrBit=iArgOfPos.get_int() % BITCOUNT;
		int iptrByte=iArgOfPos.get_int() / BITCOUNT;
		if (iptrByte>m_iptrByte ||
			iptrByte==m_iptrByte && iptrBit>=m_iptrBit)
			throw BitSet_OutOfRange();
		char tmp_Value=m_data[iptrByte];
		tmp_Value=bArgOfValue?(tmp_Value | (1 << iptrBit)):
				(tmp_Value & (~(1 << iptrBit)));
		m_data[iptrByte]=tmp_Value;
	}

	Boolean BitSet::get(Integer iArgOfPos)
	{
		int iptrBit=iArgOfPos.get_int() % BITCOUNT;
		int iptrByte=iArgOfPos.get_int() / BITCOUNT;
		if (iptrByte>m_iptrByte ||
			iptrByte==m_iptrByte && iptrBit>=m_iptrBit)
			throw BitSet_OutOfRange();
		char tmp_Value=m_data[iptrByte];
		return Boolean((tmp_Value >> iptrBit) & 1);
	}

	Boolean BitSet::operator ==(const Object & Arg) const 
	{
		try
		{
			const BitSet & my_bits=dynamic_cast<const BitSet &>(Arg);
			return Boolean(m_data==my_bits.m_data);
		}
		catch(std::bad_cast){
			throw Type_NotCorrespond();
		}
	}

	BitSet::~BitSet(){}
}
#endif