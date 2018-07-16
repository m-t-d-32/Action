#include <iostream>
#include <typeinfo>
#include "ArrayList.hpp"
#include "Integer.h"
#include "Boolean.h"
#include "Object.h"
#include "String.h"
#include "Type_NotCorrespond.h"
#include "Heap_PopOutOfRange.h"

/*
	愿你走出半生
	归来仍是少年
*/

#ifndef Action__Heap
#define Action__Heap
namespace Action
{
	template <class T>
	struct DefaultCompare
	{
		Boolean operator()(const T & tArg1,const T & tArg2)
		{
			try
			{
				const Object & obj_arg1=dynamic_cast
					<const Object &>(tArg1);
				const Object & obj_arg2=dynamic_cast
					<const Object &>(tArg2);
				return tArg1.compareTo(tArg2);
			}
			catch(std::bad_cast)
			{
				throw Type_NotCorrespond();
			}
		}
	};
	
	template <class T,class Compare=DefaultCompare<T> >
	class Heap: public Object
	{
	public:
		Heap();
		Heap(const Heap &);
		Heap(const ArrayList<T> &);
		Heap & operator =(const Heap &);
		
		virtual Integer size() const{return m_data.size();}
		virtual T front() const;
		virtual Boolean empty() const{return Boolean(m_data.size()<=0);}
		virtual void insert(const T &);
		virtual void clear();
		virtual T pop();
		virtual Boolean operator ==(const Object & Arg) const override;
		virtual String getName() const override{
			return "Action::Heap";
		}
		virtual String toString() const override{
			return m_data.toString();
		}
		virtual ~Heap();
	private:
		ArrayList<T> m_data;
		Compare compare;
	};
	
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
		m_data=HpArgOfData.m_data;
		return *this;
	}
	
	template <class T,class Compare>
	Boolean Heap<T,Compare>::operator ==(const Object & oArgOfData) const
	{
		try{
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
#endif	/* Action__Heap */