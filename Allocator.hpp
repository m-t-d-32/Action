#include <iostream>
#include "Allocator.h"
#include "Object.h"
#include "String.h"

#ifndef ALLOCATOR__CPP
#define ALLOCATOR__CPP
namespace Action
{
    template <class T>
    const Integer Allocator<T>::EVERY_INCREASE=2;
    template <class T>
    const Integer Allocator<T>::BEGIN_SPACE=10;

    template <class T>
    Allocator<T>::Allocator()
    {
        m_tSpace=NULL;
        m_iCapacity=0;
        m_iNextCapacity=BEGIN_SPACE.get_int();
    }

    template <class T>
    void Allocator<T>::auto_increase()
    {
        m_iNextCapacity*=EVERY_INCREASE.get_int();
    }

    template <class T>
    void Allocator<T>::construct(const Integer & iArgOfIndex,const T & tArgOfCopy)
    {
        new(m_tSpace+iArgOfIndex.get_int()) T(tArgOfCopy);
    }

    template <class T>
    void Allocator<T>::destruct(const Integer & iArgOfIndex)
    {
        (m_tSpace+iArgOfIndex.get_int())->~T();
    }

    template <class T>
    void Allocator<T>::set_capacity(const Integer & iArgOfSpace)
    {
        m_iNextCapacity=iArgOfSpace.get_int();
    }

    template <class T>
    T * Allocator<T>::get_space()
    {
        if (m_iNextCapacity<=0)
            throw Alloc_OutOfMemory();
        m_tSpace=(T *)malloc(sizeof(T)*m_iNextCapacity);
        if (!m_tSpace)
            throw Alloc_OutOfMemory();
        else
        {
            m_iCapacity=m_iNextCapacity;
            auto_increase();
        }
        return m_tSpace;
    }

    template <class T>
    String Allocator<T>::get_name() const
    {
        return "Action::Allocator";
    }

    template <class T>
    Allocator<T>::~Allocator()
    {
        free(m_tSpace);
    }
}
#endif
