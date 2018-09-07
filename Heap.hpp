#include <iostream>
#include "Boolean.h"
#include "Integer.h"
#include "Heap.h"

#ifndef HEAP__CPP
#define HEAP__CPP
namespace Action
{
	template <class T,class Compare>
	Heap<T,Compare>::Heap(){}

	template <class T,class Compare>
	Heap<T,Compare>::Heap(const Heap & HpArgOfData):
		m_data(HpArgOfData.m_data){}

	template <class T,class Compare>
	Heap<T,Compare>::Heap(const ArrayList<T> & arrArgOfData):
		m_data(arrArgOfData)
	{
		int size=m_data.size();
		if (!size) return;
		for (int i=size/2;i>=0;--i)
		{
			int j=i;
			const T tmp_val=m_data[j];
			while (j*2+1<size)
			{
				int next=j*2+1;
				if (next+1<size && compare(m_data[next+1],m_data[next]))
					++next;
				if (compare(tmp_val,m_data[next]))
					break;
				else
				{
					m_data[j]=m_data[next];
					j=next;
				}
			}
			m_data[j]=tmp_val;
		}
	}

	template <class T,class Compare>
	Heap<T,Compare> & Heap<T,Compare>::operator =(const Heap & HpArgOfData)
	{
		if (this==&HpArgOfData)
			return *this;
		m_data=HpArgOfData.m_data;
		return *this;
	}

	template <class T,class Compare>
	Boolean Heap<T,Compare>::operator ==(const Object & oArgOfData) const
	{
		try
		{
			const Heap<T,Compare> & HpArgOfData=dynamic_cast<const Heap<T,Compare> &>(oArgOfData);
			return Boolean(m_data==HpArgOfData.m_data);
		}
		catch(std::bad_cast){
			throw Type_NotCorrespond();
		}
	}

	template <class T,class Compare>
	T Heap<T,Compare>::front() const
	{
		if (m_data.empty())
			throw Heap_PopOutOfRange();
		return m_data.front();
	}

	template <class T,class Compare>
	void Heap<T,Compare>::insert(const T & tArgOfElement)
	{
		int insert_point=m_data.size().get_int();
		m_data.resize(m_data.size()+1);
		while (insert_point)
		{
			if (compare(tArgOfElement,m_data[(insert_point-1)/2]))
			{
				m_data[insert_point]=m_data[(insert_point-1)/2];
				insert_point=(insert_point-1)/2;
			}
			else break;
		}
		m_data[insert_point]=tArgOfElement;
	}

	template <class T,class Compare>
	void Heap<T,Compare>::clear()
	{
		m_data.clear();
	}

	template <class T,class Compare>
	T Heap<T,Compare>::pop()
	{
		if (m_data.empty())
			throw Heap_PopOutOfRange();
		T rtn=m_data.front();
		const T tmp_val=m_data.back();
		m_data.pop_back();
		int size=m_data.size().get_int(),i=0;
		if (!size) return rtn;
		while (i*2+1<size)
		{
			int next=i*2+1;
			if (next+1<size && compare(m_data[next+1],m_data[next]))
				++next;
			if (compare(tmp_val,m_data[next]))
				break;
			m_data[i]=m_data[next];
			i=next;
		}
		m_data[i]=tmp_val;
		return rtn;
	}

	template <class T,class Compare>
	Heap<T,Compare>::~Heap(){}
}
#endif /* HEAP__CPP */