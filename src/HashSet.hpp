#include <iostream>
#include "HashSet.h"
#include "String.h"

#ifndef HASHSET__CPP
#define HASHSET__CPP
namespace Action
{
    template <class T>
    const Integer HashSet<T>::BEGIN_SPACE = 10;
    template <class T>
    const Integer HashSet<T>::EVERY_INCREASE = 2;
    template <class T>
    const Real HashSet<T>::INCREASE_CAPACITY = 0.65;

    template <class T>
    HashSet<T>::HashSet()
    {
        m_size = 0;
        m_link_capacity = BEGIN_SPACE.get_int();
        m_links = new LinkedList<T> [m_link_capacity];
    }

    template <class T>
    HashSet<T>::HashSet(const HashSet<T> & another)
    {
        operator = (another);
    }

    template <class T>
    HashSet<T> & HashSet<T>::operator = (const HashSet & another)
    {
        if(this == &another)
            return *this;
        m_size = another.m_size;
        m_link_capacity = another.iCapacity;
        m_links = new LinkedList<T> [m_link_capacity];
        for(int i = 0; i < m_link_capacity; ++i)
            m_links[i] = another.m_links[i];
        return *this;
    }

    template <class T>
    void HashSet<T>::insert(const T & element)
    {
        Object & temp_object = (Object &)(element);
        int element_hash = temp_object.hash_code();
        element_hash %= m_link_capacity;
        for(typename LinkedList<T>::Pointer it = m_links[element_hash].begin(); it != m_links[element_hash].end(); ++it)
        {
            if(*it == temp_object)
                return;
        }
        m_links[element_hash].push_back(element);
        ++m_size;
        if(m_link_capacity * INCREASE_CAPACITY.get_double() < m_size)
            auto_increase();
    }

    template <class T>
    void HashSet<T>::erase(const T & element)
    {
        Object & temp_object = (Object &)(element);
        int my_hash = temp_object.hash_code();
        my_hash = my_hash % m_link_capacity;
        for(typename LinkedList<T>::Pointer it = m_links[my_hash].begin(); it != m_links[my_hash].end(); ++it)
        {
            if(*it == temp_object)
            {
                it.erase();
                --m_size;
                return;
            }
        }
    }

    template <class T>
    Boolean HashSet<T>::contains(const T & element) const
    {
        Object & temp_object = (Object &)(element);
        int my_hash = temp_object.hash_code();
        my_hash = my_hash % m_link_capacity;
        for(typename LinkedList<T>::Pointer it = m_links[my_hash].begin(); it != m_links[my_hash].end(); ++it)
        {
            if(*it == temp_object)
            {
                return Boolean::True;
            }
        }
        return Boolean::False;
    }

    template <class T>
    ArrayList<T> HashSet<T>::to_array() const
    {
        ArrayList<T> result_arraylist;
        for(int i = 0; i < m_link_capacity; ++i)
        {
            for(typename LinkedList<T>::Pointer it = m_links[i].begin(); it != m_links[i].end(); ++it)
            {
                result_arraylist.push_back(*it);
            }
        }
        return result_arraylist;
    }

    template <class T>
    void HashSet<T>::clear()
    {
        for(int i = 0; i < m_link_capacity; ++i)
        {
            m_links[i].clear();
        }
        m_size = 0;
    }

    template <class T>
    typename HashSet<T>::Pointer HashSet<T>::begin() const
    {
        if(m_size == 0)
            return end();
        int i;
        for(i = 0; i < m_link_capacity; ++i)
        {
            if(m_links[i].size() != 0)
                break;
        }
        return Pointer(this, i, m_links[i].begin());
    }

    template <class T>
    typename HashSet<T>::Pointer HashSet<T>::end() const
    {
        return Pointer(this, -1, m_links[0].end());
    }

    template <class T>
    typename HashSet<T>::Pointer HashSet<T>::v_begin() const
    {
        return Pointer(this, -1, m_links[0].v_begin());
    }

    template <class T>
    typename HashSet<T>::Pointer HashSet<T>::v_end() const
    {
        if(m_size == 0)
            return end();
        int i;
        for(i = m_link_capacity - 1; i >= 0; --i)
        {
            if(m_links[i].size() != 0)
                break;
        }
        return Pointer(this, i, m_links[i].v_end());
    }

    template <class T>
    void HashSet<T>::auto_increase()
    {
        int temp_capacity = EVERY_INCREASE.get_int() * m_link_capacity;
        LinkedList<T> *new_links = new LinkedList<T>[temp_capacity];
        for(int i = 0; i < m_link_capacity; ++i)
        {
            for(typename LinkedList<T>::Pointer it = m_links[i].begin(); it != m_links[i].end(); ++it)
            {
                Object & temp_object = (Object &)(*it);
                int temp_object_hash = temp_object.hash_code();
                temp_object_hash = temp_object_hash % temp_capacity;
                new_links[temp_object_hash].push_back(*it);
            }
        }
        delete []m_links;
        m_link_capacity = temp_capacity;
        m_links = new_links;
    }

    template <class T>
    HashSet<T>::~HashSet()
    {
        delete []m_links;
    }
}
#endif /* HASHSET__CPP */
