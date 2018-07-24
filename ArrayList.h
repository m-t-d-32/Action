#include <iostream>
#include "Allocator.h"
#include "Integer.h"
#include "Object.h"
#include <cstdlib>
#include "ArrayList_IndexOutOfRange.h"
#include "ArrayList_IllegalPointer.h"
#include "Boolean.h"

/*
	哪里有什么岁月静好
	只不过是有人在为我们负重前行
*/

#ifndef Action__ArrayList
#define Action__ArrayList
namespace Action
{

	template <class T>
	class ArrayList:public Object
	{
	public:
		friend class String;

		struct Pointer
		{
			private:
				ArrayList<T> * m_list;
				Integer m_index;
			public:
				Pointer(ArrayList<T> & now_list,const Integer & index):
					m_list(&now_list),m_index(index){}

				T & operator *(){
					if (m_index>=m_list->size() || m_index<0)
						throw ArrayList_IndexOutOfRange();
					return (*m_list)[m_index];
				}

				T * operator ->(){
					return & (operator *());
				}

				Pointer operator ++(int){
					return Pointer(*m_list,m_index++);
				}

				Pointer & operator ++(){
					++m_index;
					return *this;
				}

				Pointer operator --(int){
					return Pointer(*m_list,m_index--);
				}

				Pointer & operator --(){
					--m_index;
					return *this;
				}

				Pointer operator +(const Integer & iArg) const{
					return Pointer(*m_list,m_index+iArg);
				}

				Pointer operator -(const Integer & iArg) const{
					return Pointer(*m_list,m_index-iArg);
				}

				Pointer operator +=(const Integer & iArg){
					m_index+=iArg;
					return *this;
				}

				Pointer operator -=(const Integer & iArg){
					m_index-=iArg;
					return *this;
				}

				Boolean operator ==(const Pointer & ptrArg) const {
					return Boolean(m_list==ptrArg.m_list && m_index==ptrArg.m_index);
				}

				Boolean operator !=(const Pointer & ptrArg) const {
					return NOT (*this==ptrArg);
				}

				void insert(const T & tArg)
				{
					m_list->insert(m_index,tArg);
				}

				void insert(const Pointer & begin,const Pointer & end)
				{
					if (begin.m_list!=end.m_list)
						throw ArrayList_IllegalPointer();
                    m_list->insert(m_index,*begin.m_list,begin.m_index,end.m_index);
				}

				void erase()
				{
					m_list->erase(m_index);
				}
		};

		ArrayList();
		ArrayList(const Integer &);
		ArrayList(const ArrayList &);

		virtual Pointer begin(){return Pointer(*this,0);}
		virtual Pointer end(){return Pointer(*this,size());}

		virtual void resize(const Integer &,const T & Val=T());
		virtual ArrayList & operator =(const ArrayList &);
		virtual T & operator [](const Integer &);
        virtual T at(const Integer &) const;
		virtual T front() const;
		virtual T back() const;
		virtual void push_back(const T &);
		virtual void pop_back();
		virtual void insert(const Integer &, const T &);
        virtual void insert(const Integer &, const ArrayList<T> &,
            const Integer &,const Integer &);
        virtual void insert(const Integer &, const ArrayList<T> &);
		virtual void erase(const Integer &);
		virtual void erase(const Integer &, const Integer &);
		virtual void clear();

		virtual Boolean operator ==(const Object &) const override;
		virtual inline Integer size() const {return m_iSize;}
		virtual inline Boolean empty() const{return Boolean(size()<=0);}
		virtual Integer find (const T &) const;

		virtual String getName() const override;
		virtual String toString() const override;
		virtual ~ArrayList();
	private:
		int m_iSize;
		Allocator<T> m_alloc;
		T * m_data;
	};
}
#endif /* Action__ArrayList */
