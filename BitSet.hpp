#include <iostream>
#include "Boolean.h"
#include "Integer.h"
#include "BitSet.h"

#ifndef BITSET__CPP
#define BITSET__CPP
namespace Action
{
	BitSet::BitSet()
	{
		m_iptrByte=m_iptrBit=0;
	}

	BitSet::BitSet(const BitSet & bsetArgOfAnother)
	{
	    m_iptrByte=bsetArgOfAnother.m_iptrByte;
	    m_iptrBit=bsetArgOfAnother.m_iptrBit;
	    m_data=bsetArgOfAnother.m_data;
	}

	BitSet & BitSet::operator =(const BitSet & bsetArgOfAnother)
	{
		if (this==&bsetArgOfAnother)
			return *this;
        m_iptrByte=bsetArgOfAnother.m_iptrByte;
	    m_iptrBit=bsetArgOfAnother.m_iptrBit;
	    m_data=bsetArgOfAnother.m_data;
	    return *this;
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
}
#endif /* BITSET__CPP */
