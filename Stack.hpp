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
    Stack<T> & Stack<T>::operator =(const Stack & stkArg)
    {
        if (this==&stkArg)
            return *this;
        m_array=stkArg.m_array;
        return *this;
    }

    template <class T>
    void Stack<T>::push(const T & tArgOfElement)
    {
        m_array.push_back(tArgOfElement);
    }

    template <class T>
    T Stack<T>::pop()
    {
        try
        {
            T rtn=m_array.back();
            m_array.pop_back();
            return rtn;
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
