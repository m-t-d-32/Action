#include <iostream>
#include "Integer.h"
#include "Object.h"
#include "List_PtrOutOfRange.h"
#include "Boolean.h"

/*
	羁绊早已写好，
	只等与你相遇。
*/

#ifndef Action__LinkedList
#define Action__LinkedList
namespace Action
{
	template <class T>
	class LinkedList:public Object
	{
		struct Node
		{
			T tValue;
			Node * ptrLast, *ptrNext;
			Node(const T & tArgValue):tValue(tArgValue),
				ptrLast(NULL),ptrNext(NULL){}
		};

		public:
			struct Pointer
			{
				private:
					LinkedList<T> * m_List;
					Node * m_Node;
				public:
					Pointer(LinkedList<T> * ptrList,Node * ptrArgNode):
						m_List(ptrList),m_Node(ptrArgNode){}

					inline LinkedList<T> * getList() const {return m_List;}
					inline Node * getPointer() const { return m_Node;}

					T & operator *(){
						if (m_Node==NULL) throw List_PtrOutOfRange();
						return m_Node->tValue;
					}

					T * operator ->(){
						return & (operator *());
					}

					Pointer operator ++(int){
						Pointer ptrReturnVal(*this);
						*this=next();
						return ptrReturnVal;
					}

					Pointer & operator ++(){
						*this=next();
						return *this;
					}

					Pointer operator --(int){
						Pointer ptrReturnVal(*this);
						*this=last();						
						return ptrReturnVal;
					}

					Pointer & operator --(){
						*this=last();
						return *this;
					}

					Pointer next() const {
						if (m_Node==NULL)
							throw List_PtrOutOfRange();
						return Pointer(m_List,m_Node->ptrNext);
					}

					Pointer last() const {
						if (m_Node==NULL)
							throw List_PtrOutOfRange();
						return Pointer(m_List,m_Node->ptrLast);
					}

					Boolean operator == (const Pointer & ptrArgOfAnother) const {
						return Boolean(m_Node==ptrArgOfAnother.m_Node);
					}

					Boolean operator != (const Pointer & ptrArgOfAnother) const {
						return Boolean(m_Node!=ptrArgOfAnother.m_Node);
					}	

					void insert(const T & tArg){
						m_List->insert(*this,tArg);
					}

					void erase(){
						Node * tmp_node=m_Node->ptrNext;
						m_List->erase(*this);
						m_Node=tmp_node;
					}
			};
			friend struct Pointer;
		public:
			LinkedList();
			LinkedList(const LinkedList &);
			LinkedList & operator =(const LinkedList &);

			virtual void push_back(const T &);
			virtual void insert(const Integer &,const T &);
			virtual void insert(const Integer &,const Integer &,const T &);
			virtual void insert(Pointer ,const T &);
			virtual T pop_back();
			virtual void erase(const Integer &);
			virtual void erase(const Integer &,const Integer &);
			virtual void erase(Pointer );
			virtual void erase(Pointer ,Pointer );
			virtual void clear();
			virtual T & operator [](const Integer &);
			virtual T at(const Integer &) const;

			virtual T front() const;
			virtual T back() const;
			virtual Pointer begin() {return Pointer(this,m_ptrBegin);}
			virtual Pointer end() {return Pointer(this,NULL);}
			virtual Pointer v_begin() {return end();}
			virtual Pointer v_end() {return Pointer(this,m_ptrEnd);}

			virtual Boolean operator == (const Object &) const override;
			virtual Integer size() const { return m_iSize;}
			virtual Boolean empty() const { return Boolean(m_iSize==0);}
			virtual Integer find (const T &) const;

			virtual String get_name() const override;
			virtual String to_string() const override;
			virtual ~LinkedList();
		private:
			Node * m_ptrBegin, *m_ptrEnd;
			int m_iSize;
	};
}
#endif /* Action__LinkedList */
