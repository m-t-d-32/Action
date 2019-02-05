#include <iostream>
#include "Allocator.h"
#include "Object.h"
#include "String.h"

#ifndef ALLOCATOR__CPP
#define ALLOCATOR__CPP
namespace Action
{
    template <class T>
    const Integer Allocator<T>::EVERY_INCREASE = 2;
    template <class T>
    const Integer Allocator<T>::BEGIN_SPACE = 10;

    template <class T>
    Allocator<T>::Allocator()
    {
        m_space = NULL;
        m_capacity = 0;
        m_next_capacity = BEGIN_SPACE.get_int();
    }

    template <class T>
    void Allocator<T>::auto_increase()
    {
        m_next_capacity *= EVERY_INCREASE.get_int();
    }

    template <class T>
    void Allocator<T>::construct(Integer index, const T & cpy_constructor_arg)
    {
        new(m_space + index.get_int()) T(cpy_constructor_arg);
    }

    template <class T>
    void Allocator<T>::destruct(Integer index)
    {
        (m_space + index.get_int())->~T();
    }

    template <class T>
    void Allocator<T>::set_capacity(Integer new_capacity)
    {
        m_next_capacity = new_capacity.get_int();
    }

    template <class T>
    T * Allocator<T>::get_space()
    {
        if(m_next_capacity <= 0)
            throw Alloc_OutOfMemory();
        m_space = (T *) malloc(sizeof(T) * m_next_capacity);
        if(!m_space)
            throw Alloc_OutOfMemory();
        else
        {
            m_capacity = m_next_capacity;
            auto_increase();
        }
        return m_space;
    }

    template <class T>
    String Allocator<T>::get_name() const
    {
        return "Action::Allocator";
    }

    template <class T>
    Allocator<T>::~Allocator()
    {
        free(m_space);
    }
}
#endif /* ALLOCATOR__CPP */
