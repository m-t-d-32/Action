#include <iostream>
#include "Object.h"
#include "AVLTree.h"
#include "Boolean.h"
#include "Integer.h"

namespace Action
{
    template <class T, class Tree = AVLTree<T> >
    class TreeSet: public Object
    {
        public:
            struct Pointer
            {
                private:
                    typename Tree::Pointer m_pointer;
                public:
                    Pointer (typename Tree::Pointer pointer) : m_pointer (pointer) {}
                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean (m_pointer == another.m_pointer);
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
                    T & operator *()
                    {
                        return m_pointer.operator * ();
                    }
                    T * operator ->()
                    {
                        return m_pointer.operator ->();
                    }
                    Pointer next() const
                    {
                        return m_pointer.next();
                    }
                    Pointer last() const
                    {
                        return m_pointer.last();
                    }
                    Pointer operator ++ (int)
                    {
                        return m_pointer++;
                    }
                    Pointer & operator ++()
                    {
                        ++m_pointer;
                        return *this;
                    }
                    Pointer operator -- (int)
                    {
                        return m_pointer--;
                    }
                    Pointer & operator --()
                    {
                        --m_pointer;
                        return *this;
                    }
            };

            TreeSet() {}
            TreeSet (const TreeSet & another) : m_tree (another.m_tree) {}
            TreeSet & operator = (const TreeSet & another)
            {
                m_tree = another.m_tree;
            }
            Boolean operator == (const TreeSet & another)
            {
                return to_array() == another.to_array();
            }
            virtual void insert (const T & element)
            {
                m_tree.insert (element);
            }
            virtual void erase (const T & element)
            {
                m_tree.erase (element);
            }
            virtual Boolean contains (const T & element) const
            {
                return Boolean (m_tree.find (element) != NULL);
            }
            virtual Integer size() const
            {
                return m_tree.size();
            }
            virtual Boolean empty() const
            {
                return Boolean (size() == 0);
            }
            virtual ArrayList<T> to_array() const
            {
                return m_tree.to_array();
            }
            virtual void clear()
            {
                m_tree.clear();
            }
            virtual Pointer begin()
            {
                return Pointer (m_tree.begin() );
            }
            virtual Pointer end()
            {
                return Pointer (m_tree.end() );
            }
            virtual Pointer v_begin()
            {
                return Pointer (m_tree.v_begin() );
            }
            virtual Pointer v_end()
            {
                return Pointer (m_tree.v_end() );
            }
            virtual String get_name() const override
            {
                return "Action::TreeSet";
            }
            virtual String to_string() const override
            {
                return to_array().to_string();
            }
            virtual ~TreeSet() {}
        private:
            Tree m_tree;
    };
}
