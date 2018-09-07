#include <iostream>
#include "Object.h"
#include "LinkedList.hpp"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"
#include "String.h"
#include "ArrayList.hpp"
#include "Set_PtrOutOfRange.h"
#include "Set_ElementNotExists.h"

#ifndef Action__HashSet
#define Action__HashSet
namespace Action
{
    template <class T>
    class HashSet: public Object
    {
        public:
            struct Pointer
            {
                private:
                    const HashSet * m_set;
                    typename LinkedList<T>::Pointer m_ptr;
                public:
                    Pointer(const HashSet * set, typename LinkedList<T>::Pointer ptr):
                        m_set(set),m_ptr(ptr) {}
                    T & operator *()
                    {
                        if (*this==m_set->end())
                            throw Set_PtrOutOfRange();
                        else
                            return *m_ptr;
                    }
                    T * operator ->()
                    {
                        return &(*this);
                    }
                    Pointer & operator ++()
                    {
                        *this=next();
                        return *this;
                    }
                    Pointer & operator --()
                    {
                        *this=last();
                        return *this;
                    }
                    Pointer operator ++(int)
                    {
                        Pointer ptrReturnVal(*this);
                        *this=next();
                        return ptrReturnVal;
                    }
                    Pointer operator --(int)
                    {
                        Pointer ptrReturnVal(*this);
                        *this=last();
                        return ptrReturnVal;
                    }

                    Pointer next() const
                    {
                        if (*this==m_set->end())
                            throw Set_PtrOutOfRange();
                        else if (*this==m_set->v_begin())
                            return m_set->begin();
                        else
                        {
                            if (m_ptr.next()!=(m_ptr.getList())->end())
                                return Pointer(m_set,m_ptr.next());
                            else
                            {
                                LinkedList<T> * rtn_list;
                                for (rtn_list=m_ptr.getList()+1; rtn_list<m_set->m_links+m_set->m_iCapacity; ++rtn_list)
                                    if (rtn_list->size()>0)
                                        break;
                                if (rtn_list>=m_set->m_links+m_set->m_iCapacity)
                                    return m_set->end();
                                else
                                    return Pointer(m_set,rtn_list->begin());
                            }
                        }
                    }
                    Pointer last() const
                    {
                        if (*this==m_set->v_begin())
                            throw Set_PtrOutOfRange();
                        else if (*this==m_set->end())
                            return m_set->v_end();
                        else
                        {
                            if (m_ptr.last()!=(m_ptr.getList())->v_begin())
                                return Pointer(m_set,m_ptr.last());
                            else
                            {
                                LinkedList<T> * rtn_list;
                                for (rtn_list=m_ptr.getList()-1; rtn_list>=m_set->m_links; --rtn_list)
                                    if (rtn_list->size()>0)
                                        break;
                                if (rtn_list<m_set->m_links)
                                    return m_set->v_begin();
                                else
                                    return Pointer(m_set,rtn_list->v_end());
                            }
                        }
                    }
                    Boolean operator == (const Pointer & ptrArgOfAnother) const
                    {
                        return Boolean(m_ptr==ptrArgOfAnother.m_ptr && m_set==ptrArgOfAnother.m_set);
                    }
                    Boolean operator != (const Pointer & ptrArgOfAnother) const
                    {
                        return NOT operator ==(ptrArgOfAnother);
                    }
            };
            friend struct Pointer;
        public:
            HashSet();
            HashSet(const HashSet &);
            HashSet & operator =(const HashSet &);
            virtual void insert(const T &);
            virtual void erase(const T &);
            virtual Boolean contains(const T &) const;
            virtual Integer size() const
            {
                return m_iSize;
            }
            virtual Boolean empty() const
            {
                return Boolean(m_iSize==0);
            }
            virtual ArrayList<T> to_array() const;
            virtual void clear();
            virtual Pointer begin() const;
            virtual Pointer end() const;
            virtual Pointer v_begin() const;
            virtual Pointer v_end() const;
            virtual String get_name() const override
            {
                return "Action::HashSet";
            }
            virtual String to_string() const override
            {
                return to_array().to_string();
            }
            virtual ~HashSet();
            const static Integer BEGIN_SPACE;
            const static Integer EVERY_INCREASE;
            const static Real INCREASE_CAPACITY;
        protected:
            LinkedList<T> * m_links;
            int m_iSize;
            int m_iCapacity;
            void auto_increase();
    };
}

#endif /* Action__HashSet */
