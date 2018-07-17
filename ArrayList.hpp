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
		m_data=m_alloc.GetSpace();
		m_iSize=0;
	}

	template <class T>
	ArrayList<T>::ArrayList(const Integer & iArgOfSpace)
	{
		if (iArgOfSpace<=0)
			throw ArrayList_IndexOutOfRange();
		m_alloc.SetCapacity(iArgOfSpace);
		m_data=m_alloc.GetSpace();
		m_iSize=0;
	}

	template <class T>
	ArrayList<T>::ArrayList(const ArrayList<T> & arrArgOfAnother)
	{
		m_alloc.SetCapacity(arrArgOfAnother.m_alloc.GetCapacity());
		m_data=m_alloc.GetSpace();
		m_iSize=arrArgOfAnother.m_iSize;
		for (int i=0;i<m_iSize;++i)
		{
			m_alloc.Construct(i,arrArgOfAnother.m_data[i]);
		}
	}

	template <class T>
	T ArrayList<T>::front() const
	{
		if (m_iSize<=0)
			throw ArrayList_IndexOutOfRange();
		return m_data[0];
	}

	template <class T>
	T ArrayList<T>::back() const
	{
		if (m_iSize<=0)
			throw ArrayList_IndexOutOfRange();
		return m_data[m_iSize-1];
	}

	template <class T>
	void ArrayList<T>::clear()
	{
		for (int i=0;i<m_iSize;++i)
		{
			m_alloc.Destruct(i);
		}
		m_iSize=0;
	}

	template <class T>
	void ArrayList<T>::push_back(const T & tArgOfElement)
	{
		if (m_iSize>=m_alloc.GetCapacity())
		{
			T * temp_tDataSpace=m_alloc.GetSpace();
			memcpy(temp_tDataSpace,m_data,(m_iSize)*sizeof(T));
			free(m_data);
			m_data=temp_tDataSpace;
		}
		m_alloc.Construct(m_iSize,tArgOfElement);
		++m_iSize;
	}

	template <class T>
	void ArrayList<T>::pop_back()
	{
		if (m_iSize<=0)
			throw ArrayList_IndexOutOfRange();
		m_alloc.Destruct(--m_iSize);
	}

	template <class T>
	void ArrayList<T>::insert(const Integer & iArgOfPos,const T & tArgOfElement)
	{
		if (iArgOfPos>m_iSize || iArgOfPos<0)
			throw ArrayList_IndexOutOfRange();
		if (m_iSize>=m_alloc.GetCapacity())
		{
			T * temp_tDataSpace=m_alloc.GetSpace();
			memcpy(temp_tDataSpace,m_data,(iArgOfPos*sizeof(T)).get_int());
			memcpy(temp_tDataSpace+(iArgOfPos+1).get_int(),m_data+iArgOfPos.get_int(),((m_iSize-iArgOfPos).get_int()*sizeof(T)));
			m_alloc.Construct(iArgOfPos,tArgOfElement);
			free(m_data);
			m_data=temp_tDataSpace;
		}
		else
		{
			memmove(m_data+(iArgOfPos+1).get_int(),m_data+iArgOfPos.get_int(),((m_iSize-iArgOfPos).get_int()*sizeof(T)));
			m_alloc.Construct(iArgOfPos,tArgOfElement);
		}
		++m_iSize;
	}

	template <class T>
	void ArrayList<T>::insert(const Integer & iArgOfPos,const ArrayList & ArrAno,const Integer & iBegin,
			const Integer & iEnd)
	{
		if (iBegin<0 || iBegin>iEnd || iEnd > ArrAno.size())
			throw ArrayList_IndexOutOfRange();
		else if (iBegin == iEnd)
			return;
        int cpy_size=(iEnd-iBegin).get_int();
        int tmp_size=m_iSize;
        resize(size()+cpy_size);
        memmove(m_data+(iArgOfPos+cpy_size).get_int(),m_data+iArgOfPos.get_int(),((tmp_size-iArgOfPos).get_int()*sizeof(T)));
        for (int i=0;i<cpy_size;++i)
            m_data[(iArgOfPos+i).get_int()]=ArrAno.at(iBegin+i);
	}

    template <class T>
    void ArrayList<T>::insert(const Integer & iArgOfPos,const ArrayList & ArrAno)
    {
        insert(iArgOfPos,ArrAno,0,ArrAno.size());
    }

	template <class T>
	void ArrayList<T>::erase(const Integer & iArgOfPos)
	{
		if (iArgOfPos>=m_iSize || iArgOfPos<0)
			throw ArrayList_IndexOutOfRange();
		m_alloc.Destruct(iArgOfPos);
		memmove(m_data+iArgOfPos.get_int(),m_data+(iArgOfPos+1).get_int(),(m_iSize-iArgOfPos-1).get_int()*sizeof(T));
		--m_iSize;
	}

	template <class T>
	void ArrayList<T>::erase(const Integer & iBegin,const Integer & iEnd)
	{
		if (iBegin<0 || iEnd>m_iSize || iEnd<=iBegin)
			throw ArrayList_IndexOutOfRange();
		for (Integer i=iBegin;i<iEnd;++i)
			m_alloc.Destruct(i);
		memmove(m_data+iBegin.get_int(),m_data+iEnd.get_int(),(m_iSize-iEnd).get_int()*sizeof(T));
		m_iSize-=(iEnd-iBegin).get_int();
	}

	template <class T>
	ArrayList<T> & ArrayList<T>::operator =(const ArrayList<T> & arrArgOfAnother)
	{
		resize(arrArgOfAnother.m_iSize);
		for (int i = 0;i<m_iSize;++i)
		{
			m_data[i] = arrArgOfAnother.m_data[i];
		}
		return *this;
	}

	template <class T>
	T & ArrayList<T>::operator[](const Integer & iArgOfIndex)
	{
		if (iArgOfIndex<0 || iArgOfIndex>=m_iSize)
			throw ArrayList_IndexOutOfRange();
		return m_data[iArgOfIndex.get_int()];
	}

    template <class T>
    T ArrayList<T>::at(const Integer & iArgOfIndex) const
    {
        if (iArgOfIndex<0 || iArgOfIndex>=m_iSize)
			throw ArrayList_IndexOutOfRange();
		return m_data[iArgOfIndex.get_int()];
    }

	template <class T>
	void ArrayList<T>::resize(const Integer & iArgOfSpace,const T & Val)
	{
		if (iArgOfSpace<=0)
			throw ArrayList_IndexOutOfRange();
		if (iArgOfSpace<m_iSize)
		{
			for (int i=iArgOfSpace.get_int();i<m_iSize;++i)
			{
				m_alloc.Destruct(i);
			}
		}
		else
		{
			if (iArgOfSpace>=m_alloc.GetCapacity())
			{
				m_alloc.SetCapacity(iArgOfSpace);
				T * temp_tDataSpace=m_alloc.GetSpace();
				memcpy(temp_tDataSpace,m_data,(m_iSize)*sizeof(T));
				free(m_data);
				m_data=temp_tDataSpace;
			}
			for (int i=m_iSize;i<iArgOfSpace;++i)
			{
				m_alloc.Construct(i,Val);
			}
		}
		m_iSize=iArgOfSpace.get_int();
	}

	template <class T>
	Integer ArrayList<T>::find(const T & iArgOfObject) const
	{
		for (int i=0;i<m_iSize;++i)
		{
			if (iArgOfObject==m_data[i])
			{
				return i;
			}
		}
		return -1;
	}

	template <class T>
	Boolean ArrayList<T>::operator ==(const Object & oArgOfAnother) const
	{
		try
		{
			const ArrayList<T> & arrArgOfAnother=dynamic_cast<const ArrayList<T>& >(oArgOfAnother); 
			if (m_iSize!=arrArgOfAnother.m_iSize) return Boolean::False;

			for (int i=0;i<m_iSize;++i)
			{
				if (m_data[i]!=arrArgOfAnother.m_data[i])
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
	String ArrayList<T>::getName() const{
		return "Action::ArrayList";
	}

	template <class T>
	String ArrayList<T>::toString() const{
		String rtn="[";
		for (int i=0;i<m_iSize;++i)
		{
			try
			{
				const Object & my_ref=(const Object &)(m_data[i]);
				rtn+=my_ref.toString();
				if (i!=m_iSize-1)
					rtn+=",";
			}
			catch (std::bad_cast)
			{
				throw Type_NotCorrespond();
			}
		}
		rtn+="]";
		return rtn;
	}

	template <class T>
	ArrayList<T>::~ArrayList()
	{
		for (int i=0;i<m_iSize;++i)
		{
			m_alloc.Destruct(i);
		}
	}
}

#endif