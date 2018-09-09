#include <iostream>
#include "Queue.h"
#include "String.h"
#include <cstdlib>
#include "Queue_PopOutOfRange.h"

namespace Action
{
    template <class T>
    Queue<T>::Queue()
    {
        m_begin = 0;
        m_size = 0;
        m_data = m_alloc.get_space();
    }

    template <class T>
    Queue<T>::Queue (const Integer & capacity)
    {
        m_begin = 0;
        m_size = 0;
        m_alloc.set_capacity (capacity);
        m_data = m_alloc.get_space();
    }

    template <class T>
    Queue<T>::Queue (const Queue<T> & another)
    {
        operator = (another);
    }

    template <class T>
    Queue<T> & Queue<T>::operator = (const Queue & another)
    {
        if (this == &another)
            return *this;
        int another_capacity = another.m_alloc.get_capacity().get_int();
        if (m_size >= another.m_size)
        {
            for (int i = 0; i < another.m_size; ++i)
            {
                m_data[ (m_begin + i) % m_alloc.get_capacity().get_int()] = another.m_data[ (another.m_begin + i) % another_capacity];
            }
            for (int i = another.m_size; i < m_size; ++i)
            {
                m_alloc.destruct ( (m_begin + i) % m_alloc.get_capacity().get_int() );
            }
            m_size = another.m_size;
        }
        else
        {
            if (another_capacity > m_alloc.get_capacity() )
            {
                clear();
                m_alloc.set_capacity (another_capacity);
                m_data = m_alloc.get_space();
            }
            for (int i = 0; i < m_size; ++i)
            {
                m_data[ (m_begin + i) % m_alloc.get_capacity().get_int()] = another.m_data[ (another.m_begin + i) % another_capacity];
            }
            for (int i = m_size; i < another.m_size; ++i)
            {
                m_alloc.construct ( (m_begin + m_size) % m_alloc.get_capacity().get_int(), another.m_data[ (another.m_begin + i) % another_capacity]);
            }
            m_size = another.m_size;
        }
        return *this;
    }

    template <class T>
    void Queue<T>::push (const T & value)
    {
        int now_capacity = m_alloc.get_capacity().get_int();
        if (m_size >= now_capacity)
        {
            T * new_data = m_alloc.get_space();
            memcpy (new_data, m_data + m_begin, (now_capacity - m_begin) *sizeof (T) );
            memcpy (new_data + now_capacity - m_begin, m_data, m_begin * sizeof (T) );
            m_begin = 0;
            free (m_data);
            m_data = new_data;
        }
        m_alloc.construct ( (m_begin + m_size) % m_alloc.get_capacity(), value);
        ++m_size;
    }

    template <class T>
    T Queue<T>::pop()
    {
        if (m_size <= 0)
            throw Queue_PopOutOfRange();
        else
        {
            T return_value = m_data[m_begin];
            m_alloc.destruct (m_begin);
            m_begin = (m_begin + 1) % m_alloc.get_capacity().get_int();
            --m_size;
            return return_value;
        }
    }

    template <class T>
    T Queue<T>::front() const
    {
        if (m_size <= 0)
            throw Queue_PopOutOfRange();
        else
            return m_data[m_begin % m_alloc.get_capacity().get_int()];
    }

    template <class T>
    T Queue<T>::back() const
    {
        if (m_size <= 0)
            throw Queue_PopOutOfRange();
        else
            return m_data[ (m_begin + m_size - 1) % m_alloc.get_capacity().get_int()];
    }

    template <class T>
    void Queue<T>::clear()
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_alloc.destruct ( (m_begin + i) % m_alloc.get_capacity().get_int() );
        }
        m_begin = 0;
        m_size = 0;
    }

    template <class T>
    Boolean Queue<T>::operator == (const Object & another_one) const
    {
        try
        {
            const Queue & another_queue = dynamic_cast<const Queue &> (another_one);
            if (m_size != another_queue.m_size)
                return Boolean::False;
            for (int i = 0; i < m_size; ++i)
            {
                if (m_data[ (m_begin + i) % m_alloc.get_capacity().get_int()] !=
                        another_queue.m_data[ (another_queue.m_begin + i) % another_queue.m_alloc.get_capacity().get_int()])
                    return Boolean::False;
            }
            return Boolean::True;
        }
        catch (std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    template <class T>
    String Queue<T>::get_name() const
    {
        return "Action::Queue";
    }

    template <class T>
    String Queue<T>::to_string() const
    {
        String rtn = "[";
        for (int i = 0; i < m_size; ++i)
        {
            const Object & temp_reference = (const Object &) m_data[ (m_begin + i) % m_alloc.get_capacity().get_int()];
            rtn += temp_reference.to_string();
            if (i != m_size - 1)
                rtn += ",";
        }
        return rtn + "]";
    }

    template <class T>
    Queue<T>::~Queue()
    {
        clear();
    }
}
