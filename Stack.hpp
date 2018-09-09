#include <iostream>
#include "Integer.h"
#include "Boolean.h"
#include "Stack.h"
#include "Stack_PopOutOfRange.h"

#ifndef STACK__CPP
#define STACK__CPP
namespace Action
{
    template <class T>
    Stack<T> & Stack<T>::operator = (const Stack & another)
    {
        if (this == &another)
            return *this;
        m_array = another.m_array;
        return *this;
    }

    template <class T>
    void Stack<T>::push (const T & element)
    {
        m_array.push_back (element);
    }

    template <class T>
    T Stack<T>::pop()
    {
        try
        {
            T return_value = m_array.back();
            m_array.pop_back();
            return return_value;
        }
        catch (ArrayList_IndexOutOfRange)
        {
            throw Stack_PopOutOfRange();
        }
    }

    template <class T>
    T Stack<T>::top() const
    {
        try
        {
            return m_array.back();
        }
        catch (ArrayList_IndexOutOfRange)
        {
            throw Stack_PopOutOfRange();
        }
    }
}
#endif /* STACK__CPP */
