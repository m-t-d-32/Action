#include <iostream>
#include "LinkedList.h"
#include "String.h"
#include "Type_NotCorrespond.h"

#ifndef LINKEDLIST__CPP
#define LINKEDLIST__CPP
namespace Action
{

	template <class T>
	LinkedList<T>::LinkedList()
	{
		m_iSize=0;
		m_ptrBegin=m_ptrEnd=NULL;
	}

	template <class T>
	LinkedList<T>::LinkedList(const LinkedList & linkArgOfAnother)
	{
		m_iSize=0;
		m_ptrBegin=m_ptrEnd=NULL;
		operator =(linkArgOfAnother);
	}

	template <class T>
	LinkedList<T> & LinkedList<T>::operator =(const LinkedList & linkArgOfAnother)
	{
		if (this==&linkArgOfAnother)
			return *this;
		Node * ptrArg=linkArgOfAnother.m_ptrBegin;
		Node * ptrTemp;
		if (!ptrArg)
		{
			clear();
			return *this;
		}
		if (!m_ptrBegin)
		{
			m_ptrBegin=new Node(ptrArg->tValue);
			ptrTemp=m_ptrBegin;
		}
		else
		{
			ptrTemp=m_ptrBegin;
			while (ptrArg->ptrNext && ptrTemp->ptrNext)
			{
				ptrTemp->tValue=ptrArg->tValue;
				ptrArg=ptrArg->ptrNext;
				ptrTemp=ptrTemp->ptrNext;
			}
			ptrTemp->tValue=ptrArg->tValue;
		}

		if (!(ptrTemp->ptrNext))
		{
			ptrArg=ptrArg->ptrNext;
			while (ptrArg)
			{
				ptrTemp->ptrNext=new Node(ptrArg->tValue);
				ptrArg=ptrArg->ptrNext;
				ptrTemp=ptrTemp->ptrNext;
			}
			m_ptrEnd=ptrTemp;
		}
		else
		{
			erase(ptrTemp->ptrNext,end());
			m_ptrEnd=ptrTemp;
		}
		m_iSize=linkArgOfAnother.m_iSize;
		return *this;
	}

	template <class T>
	T LinkedList<T>::pop_back()
	{
		if (m_iSize<=0)
			throw List_PtrOutOfRange();
		else
		{
			T rtn=m_ptrEnd->tValue;
			erase(Pointer(this,m_ptrEnd));
			return rtn;
		}
	}

	template <class T>
	void LinkedList<T>::push_back(const T & tArgOfElement)
	{
		Node *ptrNew=new Node(tArgOfElement);
		if (m_ptrBegin==NULL)
			m_ptrEnd=m_ptrBegin=ptrNew;
		else
		{
			ptrNew->ptrLast=m_ptrEnd;
			m_ptrEnd->ptrNext=ptrNew;
			m_ptrEnd=ptrNew;
		}
		++m_iSize;
	}

	template <class T>
	T LinkedList<T>::at(const Integer & iArgOfPos) const
	{
		if (iArgOfPos<0 || iArgOfPos>=m_iSize)
			throw List_PtrOutOfRange();

		const Node *ptrTemp=m_ptrBegin;
		for(int i=0;i<iArgOfPos;++i)
			ptrTemp=ptrTemp->ptrNext;
		return ptrTemp->tValue;
	}

	template <class T>
	T LinkedList<T>::front() const
	{
		if (m_iSize<=0)
			throw List_PtrOutOfRange();
		else
			return m_ptrBegin->tValue;
	}

	template <class T>
	T LinkedList<T>::back() const
	{
		if (m_iSize<=0)
			throw List_PtrOutOfRange();
		else
			return m_ptrEnd->tValue;
	}

	template <class T>
	void LinkedList<T>::insert(Pointer ptrArgOfPos, const T & tArgOfElement)
	{
		Node * ptrNode=ptrArgOfPos.getPointer();
		if (!ptrNode)
			throw List_PtrOutOfRange();

		Node *ptrNew=new Node(tArgOfElement);
		if (ptrNode==m_ptrBegin)
			m_ptrBegin=ptrNew;
		if (ptrNode->ptrLast)
		{
			ptrNode->ptrLast->ptrNext=ptrNew;
			ptrNew->ptrLast=ptrNode->ptrLast;
		}
		ptrNode->ptrLast=ptrNew;
		ptrNew->ptrNext=ptrNode;
		++m_iSize;
	}

	template <class T>
	void LinkedList<T>::insert(const Integer & iArgOfPos, const T & tArgOfElement)
	{
		if (iArgOfPos<0 || iArgOfPos>m_iSize)
			throw List_PtrOutOfRange();
		else if (iArgOfPos==m_iSize)
			push_back(tArgOfElement);
		Pointer ptrTemp=begin();
		for (int i=0;i<iArgOfPos;++i)
			++ptrTemp;
		insert(ptrTemp,tArgOfElement);
	}

	template <class T>
	void LinkedList<T>::insert(const Integer & iArgOfPos,const Integer & iArgCount,const T & tArgOfElement)
	{
		if (iArgOfPos<0 || iArgOfPos>=m_iSize)
			throw List_PtrOutOfRange();

		Pointer ptrTemp=begin();
		int i;
		for (i=0;i<iArgOfPos;++i)
			++ptrTemp;
		for (i=0;i<iArgCount;++i)
			insert(ptrTemp,tArgOfElement);
	}

	template <class T>
	void LinkedList<T>::erase(Pointer ptrArgOfPos)
	{
		Node * ptrNode=ptrArgOfPos.getPointer();
		if (!ptrNode)
			throw List_PtrOutOfRange();

		if (ptrNode==m_ptrBegin)
			m_ptrBegin=ptrNode->ptrNext;
		if (ptrNode==m_ptrEnd)
			m_ptrEnd=ptrNode->ptrLast;
		if (ptrNode->ptrNext)
			ptrNode->ptrNext->ptrLast=ptrNode->ptrLast;
		if (ptrNode->ptrLast)
			ptrNode->ptrLast->ptrNext=ptrNode->ptrNext;
		delete ptrNode;
		--m_iSize;
	}

	template <class T>
	void LinkedList<T>::erase(Pointer ptrArgPosBegin,Pointer ptrArgPosEnd)
	{
		if (!(ptrArgPosBegin.getPointer()))
			throw List_PtrOutOfRange();

		Pointer ptrTemp=ptrArgPosBegin;
		while (ptrTemp!=ptrArgPosEnd)
		{
			Pointer ptrcTemp=Pointer(this,(ptrTemp.getPointer())->ptrNext);
			erase(ptrTemp);
			ptrTemp=ptrcTemp;
		}
	}

	template <class T>
	void LinkedList<T>::erase(const Integer & iArgOfPos)
	{
		if (iArgOfPos<0 || iArgOfPos>=m_iSize)
			throw List_PtrOutOfRange();

		Pointer ptrTemp=begin();
		for (int i=0;i<iArgOfPos;++i)
			++ptrTemp;
		erase(ptrTemp);
	}

	template <class T>
	void LinkedList<T>::erase(const Integer & iArgPosBegin,const Integer & iArgCount)
	{
		if (iArgPosBegin<0 || iArgPosBegin+iArgCount>=m_iSize
			|| iArgCount<0)
			throw List_PtrOutOfRange();

		Pointer ptrTemp=begin();
		int i;
		for (i=0;i<iArgPosBegin;++i)
			++ptrTemp;
		for (i=0;i<iArgCount;++i)
		{
			Pointer ptrcTemp=ptrTemp.next();
			erase(ptrTemp);
			ptrTemp=ptrcTemp;
		}
	}

	template <class T>
	T & LinkedList<T>::operator [](const Integer & iArgOfPos)
	{
		if (iArgOfPos<0 || iArgOfPos>=m_iSize)
			throw List_PtrOutOfRange();

		Pointer ptrTemp=begin();
		for(int i=0;i<iArgOfPos;++i)
			++ptrTemp;
		return *ptrTemp;
	}

	template <class T>
	Boolean LinkedList<T>::operator ==(const Object & oArgOfAnother) const
	{
		try
		{
			const LinkedList<T> & linkArgOfAnother=dynamic_cast<const LinkedList<T> &>(oArgOfAnother);
			Node *ptr1=m_ptrBegin,*ptr2=linkArgOfAnother.m_ptrBegin;
			while (ptr1 && ptr2)
			{
				if (ptr1->tValue!=ptr2->tValue)
					return Boolean::False;
				ptr1=ptr1->ptrNext;
				ptr2=ptr2->ptrNext;
			}
			if (ptr1==NULL && ptr2 || ptr1 && ptr2==NULL)
				return Boolean::False;
			return Boolean::True;
		}
		catch (std::bad_cast){
			throw Type_NotCorrespond();
		}
	}

	template <class T>
	void LinkedList<T>::clear()
	{
		if (m_ptrBegin)
			erase(begin(),end());
	}

	template <class T>
	Integer LinkedList<T>::find(const T & iArgOfObject) const
	{
		if (!m_ptrBegin) return -1;

		int index=0;
		for (const Node * ptr=m_ptrBegin;ptr!=NULL;ptr=ptr->ptrNext)
		{
			if (ptr->tValue==iArgOfObject)
				return index;
			++index;
		}
		return -1;
	}

	template <class T>
	String LinkedList<T>::getName() const
	{
		return "Action::LinkedList";
	}

	template <class T>
	String LinkedList<T>::toString() const
	{
		String rtn="[";
		for (const Node * ptr=m_ptrBegin;ptr!=NULL;ptr=ptr->ptrNext)
		{
			rtn+=((Object &)(ptr->tValue)).toString();
			if (ptr!=m_ptrEnd)
			{
				rtn+=",";
			}
		}
		rtn+="]";
		return rtn;
	}
	template <class T>
	LinkedList<T>::~LinkedList()
	{
		clear();
	}
}
#endif
