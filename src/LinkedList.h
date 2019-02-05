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
    class LinkedList: public Object
    {
            struct Node
            {
                T m_value;
                Node * m_address_last, * m_address_next;
                Node(const T & value) : m_value(value),
                    m_address_last(NULL), m_address_next(NULL) {}
            };

        public:
            struct Pointer
            {
                private:
                    LinkedList<T> * m_list;
                    Node * m_node;
                public:
                    Pointer(LinkedList<T> * list, Node * node) :
                        m_list(list), m_node(node) {}

                    inline LinkedList<T> * get_list() const
                    {
                        return m_list;
                    }
                    inline Node * get_node() const
                    {
                        return m_node;
                    }

                    T & operator *()
                    {
                        if(*this == m_list->end() || *this == m_list->v_begin())
                            throw List_PtrOutOfRange();
                        return m_node->m_value;
                    }

                    T * operator ->()
                    {
                        return & (operator *());
                    }

                    Pointer operator ++ (int)
                    {
                        Pointer return_pointer(*this);
                        *this = next();
                        return return_pointer;
                    }

                    Pointer & operator ++()
                    {
                        *this = next();
                        return *this;
                    }

                    Pointer operator -- (int)
                    {
                        Pointer return_pointer(*this);
                        *this = last();
                        return return_pointer;
                    }

                    Pointer & operator --()
                    {
                        *this = last();
                        return *this;
                    }

                    Pointer next() const
                    {
                        if(*this == m_list->end())
                            throw List_PtrOutOfRange();
                        else if(*this == m_list->v_begin())
                            return m_list->begin();
                        else if(*this == m_list->v_end())
                            return m_list->end();
                        return Pointer(m_list, m_node->m_address_next);
                    }

                    Pointer last() const
                    {
                        if(*this == m_list->v_begin())
                            throw List_PtrOutOfRange();
                        else if(*this == m_list->end())
                            return m_list->v_end();
                        else if(*this == m_list->begin())
                            return m_list->v_begin();
                        return Pointer(m_list, m_node->m_address_last);
                    }

                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean(m_node == another.m_node);
                    }

                    Boolean operator != (const Pointer & another) const
                    {
                        return Boolean(m_node != another.m_node);
                    }

                    void insert(const T & value)
                    {
                        m_list->insert(*this, value);
                    }

                    void erase()
                    {
                        Node * next_node_position = m_node->m_address_next;
                        m_list->erase(*this);
                        m_node = next_node_position;
                    }
            };
            friend struct Pointer;
        public:
            LinkedList();
            LinkedList(const LinkedList &);
            LinkedList & operator = (const LinkedList &);
            virtual void push_back(const T &);
            virtual void insert(Integer, const T &);
            virtual void insert(Integer, Integer, const T &);
            virtual void insert(Pointer, const T &);
            virtual T pop_back();
            virtual void erase(Integer);
            virtual void erase(Integer, Integer);
            virtual void erase(Pointer);
            virtual void erase(Pointer, Pointer);
            virtual void clear();
            virtual T & operator [](Integer);
            virtual T at(Integer) const;
            virtual T front() const;
            virtual T back() const;
            virtual Pointer begin()
            {
                return Pointer(this, m_begin_address);
            }
            virtual Pointer end()
            {
                return Pointer(this, (Node *)BAD_MEMORY_0);
            }
            virtual Pointer v_begin()
            {
                return Pointer(this, (Node *)BAD_MEMORY_1);
            }
            virtual Pointer v_end()
            {
                return Pointer(this, m_end_address);
            }
            virtual Boolean operator == (const Object &) const override;
            virtual Integer size() const
            {
                return m_size;
            }
            virtual Boolean empty() const
            {
                return Boolean(m_size == 0);
            }
            virtual Integer find(const T &) const;

            virtual String get_name() const override;
            virtual String to_string() const override;
            virtual ~LinkedList();
        private:
            Node * m_begin_address, *m_end_address;
            int m_size;
    };
}
#endif /* Action__LinkedList */
