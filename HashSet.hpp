#include <iostream>
#include "HashSet.h"
#include "String.h"

#ifndef HASHSET__CPP
#define HASHSET__CPP
namespace Action
{
	template <class T>
	const Integer HashSet<T>::BEGIN_SPACE=10;
	template <class T>
	const Integer HashSet<T>::EVERY_INCREASE=2;
	template <class T>
	const Real HashSet<T>::INCREASE_CAPACITY=0.65;

    template <class T>
    HashSet<T>::HashSet()
    {
        m_iSize=0;
		m_iCapacity=BEGIN_SPACE.get_int();
        m_links=new LinkedList<T> [m_iCapacity];
    }

    template <class T>
    HashSet<T>::HashSet(const HashSet<T> & hsetArg)
    {
        operator =(hsetArg);
    }

    template <class T>
    HashSet<T> & HashSet<T>::operator =(const HashSet & hsetArg)
    {
		if (this==&hsetArg)
			return *this;
        m_iSize=hsetArg.m_iSize;
        m_iCapacity=hsetArg.iCapacity;
        m_links=new LinkedList<T> [m_iCapacity];
        for (int i=0;i<m_iCapacity;++i)
            m_links[i]=hsetArg.m_links[i];
        return *this;
    }

    template <class T>
    void HashSet<T>::insert(const T & arg)
	{
		Object & my_obj=(Object &)(arg);
		int my_hash=my_obj.hashCode();
		my_hash = my_hash % m_iCapacity;

		for (typename LinkedList<T>::Pointer it=m_links[my_hash].begin();it!=m_links[my_hash].end();++it)
		{
			if (*it==my_obj)
				return;
		}

		m_links[my_hash].push_back(arg);
		++m_iSize;

		if (m_iCapacity*INCREASE_CAPACITY.get_double()<m_iSize)
			increase();
	}

	template <class T>
	void HashSet<T>::erase(const T & arg)
	{
		Object & my_obj=(Object &)(arg);
		int my_hash=my_obj.hashCode();
		my_hash = my_hash % m_iCapacity;
		for (typename LinkedList<T>::Pointer it=m_links[my_hash].begin();it!=m_links[my_hash].end();++it)
		{
			Object & tmp_obj=(Object &)(*it);
			if (tmp_obj==my_obj)
			{
				it.erase();
				--m_iSize;
				return;
			}
		}
	}

	template <class T>
	Boolean HashSet<T>::contains(const T & arg) const
	{
		Object & my_obj=(Object &)(arg);
		int my_hash=my_obj.hashCode();
		my_hash = my_hash % m_iCapacity;
		for (typename LinkedList<T>::Pointer it=m_links[my_hash].begin();it!=m_links[my_hash].end();++it)
		{
			if (*it==my_obj)
			{
				return Boolean::True;
			}
		}
		return Boolean::False;
	}

	template <class T>
	ArrayList<T> HashSet<T>::toArray() const
	{
		ArrayList<T> rtn;
		for (int i=0;i<m_iCapacity;++i)
		{
			for (typename LinkedList<T>::Pointer it=m_links[i].begin();it!=m_links[i].end();++it)
			{
				rtn.push_back(*it);
			}
		}
		return rtn;
	}

	template <class T>
	void HashSet<T>::clear()
	{
		for (int i=0;i<m_iCapacity;++i)
		{
			m_links[i].clear();
		}
		m_iSize=0;
	}

	template <class T>
	typename HashSet<T>::Pointer HashSet<T>::begin() const
	{
		if (m_iSize==0)
			return end();
		int i;
		for (i=0;i<m_iCapacity;++i)
		{
			if (m_links[i].size()!=0)
				break;
		}
		return Pointer(this,m_links[i].begin());
	}

	template <class T>
	typename HashSet<T>::Pointer HashSet<T>::end() const
	{
		return Pointer(this,m_links[0].end());
	}

	template <class T>
	typename HashSet<T>::Pointer HashSet<T>::v_begin() const
	{
		return Pointer(NULL,m_links[1].end());
	}

	template <class T>
	typename HashSet<T>::Pointer HashSet<T>::v_end() const
	{
		if (m_iSize==0)
			return end();
		int i;
		for (i=m_iCapacity-1;i>=0;--i)
		{
			if (m_links[i].size()!=0)
				break;
		}
		return Pointer(this,m_links[i].v_end());
	}

	template <class T>
	void HashSet<T>::increase()
	{
		int tmp_Capacity=EVERY_INCREASE.get_int()*m_iCapacity;
		LinkedList<T> *tmp_links=new LinkedList<T>[tmp_Capacity];
		for (int i=0;i<m_iCapacity;++i)
		{
			for (typename LinkedList<T>::Pointer it=m_links[i].begin();it!=m_links[i].end();++it)
			{
				Object & my_obj=(Object &)(*it);
				int my_hash=my_obj.hashCode();
				my_hash = my_hash % tmp_Capacity;
				tmp_links[my_hash].push_back(*it);
			}
		}
		delete []m_links;
		m_iCapacity=tmp_Capacity;
		m_links=tmp_links;
	}

	template <class T>
	HashSet<T>::~HashSet()
	{
		delete []m_links;
	}
}
#endif
