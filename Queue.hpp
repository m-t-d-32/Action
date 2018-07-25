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
        m_iBegin=0;
        m_iSize=0;
        m_data=m_alloc.get_space();
    }

    template <class T>
    Queue<T>::Queue(const Integer & iArg)
    {
        m_iBegin=0;
        m_iSize=0;
        m_alloc.set_capacity(iArg);
        m_data=m_alloc.get_space();
    }

    template <class T>
    Queue<T>::Queue(const Queue & qArgOfAnother)
    {
        m_iBegin=qArgOfAnother.m_iBegin;
        m_iSize=qArgOfAnother.m_iSize;
		int iCapacity=qArgOfAnother.m_alloc.get_capacity().get_int();
		m_alloc.set_capacity(iCapacity);
		m_data=m_alloc.get_space();
        for (int i=0;i<m_iSize;++i)
        {
            m_alloc.construct((i+m_iBegin)%iCapacity,qArgOfAnother.m_data[(i+m_iBegin)%iCapacity]);
        }
    }

    template <class T>
    Queue<T> & Queue<T>::operator =(const Queue & qArgOfAnother)
    {
		if (this==&qArgOfAnother)
			return *this;
        clear();
        m_iBegin=qArgOfAnother.m_iBegin;
        m_iSize=qArgOfAnother.m_iSize;
		int iCapacity=qArgOfAnother.m_alloc.get_capacity().get_int();
        if (iCapacity>m_alloc.get_capacity())
        {
            m_alloc.set_capacity(iCapacity);
            T * tmp_data=m_alloc.get_space();
            free(m_data);
            m_data=tmp_data;
        }
        for (int i=0;i<m_iSize;++i)
        {
            m_alloc.construct((i+m_iBegin)%iCapacity,qArgOfAnother.m_data[(i+m_iBegin)%iCapacity]);
        }
		return *this;
    }

    template <class T>
    void Queue<T>::push(const T & tArg)
    {
		int iCapacity=m_alloc.get_capacity().get_int();
        if (m_iSize>=iCapacity)
        {
            T * tmp_data=m_alloc.get_space();
            memcpy(tmp_data,m_data+m_iBegin,(iCapacity-m_iBegin)*sizeof(T));
            memcpy(tmp_data+iCapacity-m_iBegin,m_data,m_iBegin*sizeof(T));
            m_iBegin=0;
            free(m_data);
            m_data=tmp_data;
        }
        m_alloc.construct((m_iBegin+m_iSize)%m_alloc.get_capacity(),tArg);
        ++m_iSize;
    }

    template <class T>
    T Queue<T>::pop()
    {
        if (m_iSize<=0)
            throw Queue_PopOutOfRange();
        else
        {
            T rtn=m_data[m_iBegin];
            m_alloc.destruct(m_iBegin);
            m_iBegin=(m_iBegin+1)%m_alloc.get_capacity().get_int();
            --m_iSize;
            return rtn;
        }
    }

    template <class T>
    T Queue<T>::front() const
    {
        if (m_iSize<=0)
            throw Queue_PopOutOfRange();
        else
            return m_data[m_iBegin%m_alloc.get_capacity().get_int()];
    }

    template <class T>
    T Queue<T>::back() const
    {
        if (m_iSize<=0)
            throw Queue_PopOutOfRange();
        else
            return m_data[(m_iBegin+m_iSize-1)%m_alloc.get_capacity().get_int()];
    }

    template <class T>
    void Queue<T>::clear()
    {
        for (int i=0;i<m_iSize;++i)
        {
            m_alloc.destruct((m_iBegin+i)%m_alloc.get_capacity().get_int());
        }
        m_iBegin=0;
        m_iSize=0;
    }

    template <class T>
    Boolean Queue<T>::operator ==(const Object & objArg) const
    {
        try
        {
            const Queue & queArg=dynamic_cast<const Queue &>(objArg);
            if (m_iSize!=queArg.m_iSize)
                return Boolean::False;
            for (int i=0;i<m_iSize;++i)
            {
                if (m_data[(m_iBegin+i)%m_alloc.get_capacity().get_int()]!=
                    queArg.m_data[(queArg.m_iBegin+i)%queArg.m_alloc.get_capacity().get_int()])
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
        String rtn="[";
        for (int i=0;i<m_iSize;++i)
        {
            const Object & objTmpRef=(const Object &)m_data[(m_iBegin+i)%m_alloc.get_capacity().get_int()];
            rtn+=objTmpRef.to_string();
            if (i!=m_iSize-1)
                rtn+=",";
        }
        return rtn+"]";
    }

    template <class T>
    Queue<T>::~Queue()
    {
	    clear();
    }
}
