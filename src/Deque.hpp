#include <iostream>
#include "Deque.h"
#include "Deque_IndexOutOfRange.h"
#include "Deque_PopOutOfRange.h"

#ifndef DEQUE__CPP
#define DEQUE__CPP
namespace Action
{
    template <class T>
    Deque<T>::Deque() : m_data() {}

    template <class T>
    Deque<T>::Deque(const Integer & capacity) : m_data(capacity) {}

    template <class T>
    Deque<T>::Deque(const Deque & another) : m_data(another.m_data) {}

    template <class T>
    void Deque<T>::push_back(const T & element)
    {
        m_data.push(element);
    }

    template <class T>
    void Deque<T>::push_front(const T & element)
    {
        int now_capacity = m_data.m_alloc.get_capacity().get_int();
        if(m_data.m_size >= now_capacity)
        {
            m_data.auto_increase();
        }
        now_capacity = m_data.m_alloc.get_capacity().get_int();
        m_data.m_begin = m_data.m_begin - 1 < 0 ? (m_data.m_begin - 1 + now_capacity) : (m_data.m_begin - 1);
        m_data.m_alloc.construct(m_data.m_begin % now_capacity, element);
        ++m_data.m_size;
    }

    template <class T>
    T Deque<T>::pop_back()
    {
        T return_value = back();
        --m_data.m_size;
        return return_value;
    }

    template <class T>
    T Deque<T>::pop_front()
    {
        try
        {
            return m_data.pop();
        }
        catch(Queue_PopOutOfRange)
        {
            throw Deque_PopOutOfRange();
        }
    }

    template <class T>
    T Deque<T>::front() const
    {
        try
        {
            return m_data.front();
        }
        catch(Queue_PopOutOfRange)
        {
            throw Deque_PopOutOfRange();
        }
    }

    template <class T>
    T Deque<T>::back() const
    {
        try
        {
            return m_data.back();
        }
        catch(Queue_PopOutOfRange)
        {
            throw Deque_PopOutOfRange();
        }
    }

    template <class T>
    T & Deque<T>::operator [](const Integer & index)
    {
        if(index < 0 || index >= m_data.m_size)
        {
            throw Deque_IndexOutOfRange();
        }
        return m_data.m_data[(index.get_int() + m_data.m_begin) % m_data.m_alloc.get_capacity().get_int()];
    }

    template <class T>
    void Deque<T>::clear()
    {
        m_data.clear();
    }

    template <class T>
    Boolean Deque<T>::operator == (const Object & another_one) const
    {
        try
        {
            const Deque<T> & another_deque = dynamic_cast<const Deque<T> & >(another_one);
            return m_data == another_deque.m_data;
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    template <class T>
    Deque<T>::~Deque() {}
}
#endif /* DEQUE__CPP */
