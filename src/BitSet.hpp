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
        m_ptr_byte = m_ptr_bit = 0;
    }

    BitSet::BitSet(const BitSet & another)
    {
        m_ptr_byte = another.m_iptrByte;
        m_ptr_bit = another.m_iptrBit;
        m_data = another.m_data;
    }

    BitSet & BitSet::operator = (const BitSet & another)
    {
        if(this == &another)
            return *this;
        m_ptr_byte = another.m_ptr_byte;
        m_ptr_bit = another.m_ptr_bit;
        m_data = another.m_data;
        return *this;
    }

    void BitSet::push_back(Boolean value)
    {
        if(!m_ptr_bit)
            m_data.push_back(0);

        char tmp_Value = m_data[m_ptr_byte];
        tmp_Value = value ? (tmp_Value | (1 << m_ptr_bit)) :
                    (tmp_Value & (~(1 << m_ptr_bit)));
        m_data[m_ptr_byte] = tmp_Value;

        ++m_ptr_bit;
        if(m_ptr_bit > BITCOUNT)
        {
            m_ptr_bit = 0;
            ++m_ptr_byte;
        }
    }

    void BitSet::set(Integer position, Boolean value)
    {
        int bit_position = position.get_int() % BITCOUNT;
        int byte_position = position.get_int() / BITCOUNT;
        if(byte_position > m_ptr_byte ||
                byte_position == m_ptr_byte && bit_position >= m_ptr_bit)
            throw BitSet_OutOfRange();
        char tmp_Value = m_data[byte_position];
        tmp_Value = value ? (tmp_Value | (1 << bit_position)) :
                    (tmp_Value & (~(1 << bit_position)));
        m_data[byte_position] = tmp_Value;
    }

    Boolean BitSet::get(Integer position)
    {
        int bit_position = position.get_int() % BITCOUNT;
        int byte_position = position.get_int() / BITCOUNT;
        if(byte_position > m_ptr_byte ||
                byte_position == m_ptr_byte && bit_position >= m_ptr_bit)
            throw BitSet_OutOfRange();
        char tmp_Value = m_data[byte_position];
        return Boolean((tmp_Value >> bit_position) & 1);
    }

    Boolean BitSet::operator == (const Object & another_one) const
    {
        try
        {
            const BitSet & another_bitset = dynamic_cast<const BitSet &>(another_one);
            return Boolean(m_data == another_bitset.m_data);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }
}
#endif /* BITSET__CPP */
