#include <iostream>
#include "Boolean.h"
#include "Integer.h"
#include "Heap.h"

#ifndef HEAP__CPP
#define HEAP__CPP
namespace Action
{
    template <class T, class Compare>
    Heap<T, Compare>::Heap() {}

    template <class T, class Compare>
    Heap<T, Compare>::Heap(const Heap & another) :
        m_data(another.m_data) {}

    template <class T, class Compare>
    Heap<T, Compare>::Heap(const ArrayList<T> & values_arraylist) :
        m_data(values_arraylist)
    {
        int size = m_data.size().get_int();
        if(!size)
            return;
        for(int i = size / 2; i >= 0; --i)
        {
            int j = i;
            const T now_value = m_data[j];
            while(j * 2 + 1 < size)
            {
                int next = j * 2 + 1;
                if(next + 1 < size && compare(m_data[next + 1], m_data[next]) < 0)
                    ++next;
                if(compare(now_value, m_data[next]) < 0)
                    break;
                else
                {
                    m_data[j] = m_data[next];
                    j = next;
                }
            }
            m_data[j] = now_value;
        }
    }

    template <class T, class Compare>
    Heap<T, Compare> & Heap<T, Compare>::operator = (const Heap & another)
    {
        if(this == &another)
            return *this;
        m_data = another.m_data;
        return *this;
    }

    template <class T, class Compare>
    Boolean Heap<T, Compare>::operator == (const Object & another_one) const
    {
        try
        {
            const Heap<T, Compare> & another_heap = dynamic_cast<const Heap<T, Compare> &>(another_one);
            return Boolean(m_data == another_heap.m_data);
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    template <class T, class Compare>
    T Heap<T, Compare>::front() const
    {
        if(m_data.empty())
            throw Heap_PopOutOfRange();
        return m_data.front();
    }

    template <class T, class Compare>
    void Heap<T, Compare>::insert(const T & element)
    {
        int insert_point = m_data.size().get_int();
        m_data.resize(m_data.size() + 1);
        while(insert_point)
        {
            if(compare(element, m_data[(insert_point - 1) / 2]) < 0)
            {
                m_data[insert_point] = m_data[(insert_point - 1) / 2];
                insert_point = (insert_point - 1) / 2;
            }
            else
                break;
        }
        m_data[insert_point] = element;
    }

    template <class T, class Compare>
    void Heap<T, Compare>::clear()
    {
        m_data.clear();
    }

    template <class T, class Compare>
    T Heap<T, Compare>::pop()
    {
        if(m_data.empty())
            throw Heap_PopOutOfRange();
        T element_return = m_data.front();
        const T saved_value = m_data.back();
        m_data.pop_back();
        int size = m_data.size().get_int(), i = 0;
        if(!size)
            return element_return;
        while(i * 2 + 1 < size)
        {
            int next = i * 2 + 1;
            if(next + 1 < size && compare(m_data[next + 1], m_data[next]) < 0)
                ++next;
            if(compare(saved_value, m_data[next]) < 0)
                break;
            m_data[i] = m_data[next];
            i = next;
        }
        m_data[i] = saved_value;
        return element_return;
    }

    template <class T, class Compare>
    Heap<T, Compare>::~Heap() {}
}
#endif /* HEAP__CPP */
