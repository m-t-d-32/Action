#include <iostream>
#include "ArrayList.h"
#include "Object.h"
#include "String.h"
#include "Allocator.hpp"
#include "Type_NotCorrespond.h"

#ifndef ARRAYLIST__CPP
#define ARRAYLIST__CPP
namespace Action
{
    template <class T>
    ArrayList<T>::ArrayList()
    {
        m_data = m_alloc.get_space();
        m_size = 0;
    }

    template <class T>
    ArrayList<T>::ArrayList(Integer capacity)
    {
        if(capacity <= 0)
            throw ArrayList_IndexOutOfRange();
        m_alloc.set_capacity(capacity);
        m_data = m_alloc.get_space();
        m_size = 0;
    }

    template <class T>
    ArrayList<T>::ArrayList(const ArrayList<T> & another)
    {
        m_alloc.set_capacity(another.m_alloc.get_capacity());
        m_data = m_alloc.get_space();
        m_size = another.m_size;
        for(int i = 0; i < m_size; ++i)
        {
            m_alloc.construct(i, another.m_data[i]);
        }
    }

    template <class T>
    T ArrayList<T>::front() const
    {
        if(m_size <= 0)
            throw ArrayList_IndexOutOfRange();
        return m_data[0];
    }

    template <class T>
    T ArrayList<T>::back() const
    {
        if(m_size <= 0)
            throw ArrayList_IndexOutOfRange();
        return m_data[m_size - 1];
    }

    template <class T>
    void ArrayList<T>::clear()
    {
        for(int i = 0; i < m_size; ++i)
        {
            m_alloc.destruct(i);
        }
        m_size = 0;
    }

    template <class T>
    void ArrayList<T>::push_back(const T & element)
    {
        if(m_size >= m_alloc.get_capacity())
        {
            T * new_data = m_alloc.get_space();
            memcpy(new_data, m_data, (m_size) *sizeof(T));
            free(m_data);
            m_data = new_data;
        }
        m_alloc.construct(m_size, element);
        ++m_size;
    }

    template <class T>
    void ArrayList<T>::pop_back()
    {
        if(m_size <= 0)
            throw ArrayList_IndexOutOfRange();
        m_alloc.destruct(--m_size);
    }

    template <class T>
    void ArrayList<T>::insert(Pointer position, const T & element)
    {
        position.insert(element);
    }

    template <class T>
    void ArrayList<T>::insert(Integer position, const T & element)
    {
        if(position > m_size || position < 0)
            throw ArrayList_IndexOutOfRange();
        if(m_size >= m_alloc.get_capacity())
        {
            T * new_data = m_alloc.get_space();
            memcpy(new_data, m_data, (position * sizeof(T)).get_int());
            memcpy(new_data + (position + 1).get_int(), m_data + position.get_int(), ((m_size - position).get_int() *sizeof(T)));
            m_alloc.construct(position, element);
            free(m_data);
            m_data = new_data;
        }
        else
        {
            memmove(m_data + (position + 1).get_int(), m_data + position.get_int(), ((m_size - position).get_int() *sizeof(T)));
            m_alloc.construct(position, element);
        }
        ++m_size;
    }

    template <class T>
    void ArrayList<T>::insert(Integer position, const ArrayList & another, Integer begin,
                              Integer end)
    {
        if(begin < 0 || begin > end || end > another.size())
            throw ArrayList_IndexOutOfRange();
        else if(begin == end)
            return;
        int cpy_size = (end - begin).get_int();
        int tmp_size = m_size;
        resize(size() + cpy_size);
        memmove(m_data + (position + cpy_size).get_int(), m_data + position.get_int(), ((tmp_size - position).get_int() *sizeof(T)));
        for(int i = 0; i < cpy_size; ++i)
            m_data[(position + i).get_int()] = another.at(begin + i);
    }

    template <class T>
    void ArrayList<T>::insert(Integer position, const ArrayList & another)
    {
        insert(position, another, 0, another.size());
    }

    template <class T>
    void ArrayList<T>::erase(Integer position)
    {
        if(position >= m_size || position < 0)
            throw ArrayList_IndexOutOfRange();
        m_alloc.destruct(position);
        memmove(m_data + position.get_int(), m_data + (position + 1).get_int(), (m_size - position - 1).get_int() *sizeof(T));
        --m_size;
    }

    template <class T>
    void ArrayList<T>::erase(Integer begin, Integer end)
    {
        if(begin < 0 || end > m_size || end <= begin)
            throw ArrayList_IndexOutOfRange();
        for(Integer i = begin; i < end; ++i)
            m_alloc.destruct(i);
        memmove(m_data + begin.get_int(), m_data + end.get_int(), (m_size - end).get_int() *sizeof(T));
        m_size -= (end - begin).get_int();
    }

    template <class T>
    ArrayList<T> & ArrayList<T>::operator = (const ArrayList<T> & another)
    {
        if(this == &another)
            return *this;
        resize(another.m_size);
        for(int i = 0; i < m_size; ++i)
        {
            m_data[i] = another.m_data[i];
        }
        return *this;
    }

    template <class T>
    T & ArrayList<T>::operator[](Integer index)
    {
        if(index < 0 || index >= m_size)
            throw ArrayList_IndexOutOfRange();
        return m_data[index.get_int()];
    }

    template <class T>
    T ArrayList<T>::at(Integer index) const
    {
        if(index < 0 || index >= m_size)
            throw ArrayList_IndexOutOfRange();
        return m_data[index.get_int()];
    }

    template <class T>
    void ArrayList<T>::resize(Integer new_size, const T & cpy_constructor_arg)
    {
        if(new_size <= 0)
            throw ArrayList_IndexOutOfRange();
        if(new_size < m_size)
        {
            for(int i = new_size.get_int(); i < m_size; ++i)
            {
                m_alloc.destruct(i);
            }
        }
        else
        {
            if(new_size >= m_alloc.get_capacity())
            {
                m_alloc.set_capacity(new_size);
                T * new_data = m_alloc.get_space();
                memcpy(new_data, m_data, (m_size) *sizeof(T));
                free(m_data);
                m_data = new_data;
            }
            for(int i = m_size; i < new_size; ++i)
            {
                m_alloc.construct(i, cpy_constructor_arg);
            }
        }
        m_size = new_size.get_int();
    }

    template <class T>
    Integer ArrayList<T>::find(const T & element) const
    {
        for(int i = 0; i < m_size; ++i)
        {
            if(element == m_data[i])
            {
                return i;
            }
        }
        return -1;
    }

    template <class T>
    Boolean ArrayList<T>::operator == (const Object & another_one) const
    {
        try
        {
            const ArrayList<T> & another_arraylist = dynamic_cast<const ArrayList<T>& >(another_one);
            if(m_size != another_arraylist.m_size)
                return Boolean::False;

            for(int i = 0; i < m_size; ++i)
            {
                if(m_data[i] != another_arraylist.m_data[i])
                    return Boolean::False;
            }
            return Boolean::True;
        }
        catch(std::bad_cast)
        {
            throw Type_NotCorrespond();
        }
    }

    template <class T>
    String ArrayList<T>::get_name() const
    {
        return "Action::ArrayList";
    }

    template <class T>
    String ArrayList<T>::to_string() const
    {
        String return_value = "[";
        for(int i = 0; i < m_size; ++i)
        {
            try
            {
                const Object & temp_reference = (const Object &)(m_data[i]);
                return_value += temp_reference.to_string();
                if(i != m_size - 1)
                    return_value += ",";
            }
            catch(std::bad_cast)
            {
                throw Type_NotCorrespond();
            }
        }
        return_value += "]";
        return return_value;
    }

	template <class T>
	ArrayList<T> ArrayList<T>::slice(Integer begin ,Integer end) const{
		ArrayList<T> result;
		if (begin < 0) begin += size();
		if (end < 0) end += size();
		for (Integer i = begin; i < end; ++i){
			result.push_back(at(i));
		}
		return result;
	}

    template <class T>
    ArrayList<T>::~ArrayList()
    {
        clear();
    }
}
#endif /* ARRAYLIST__CPP */
