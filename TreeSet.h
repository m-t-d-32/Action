#include <iostream>
#include "Object.h"
#include "AVLTree.h"
#include "Boolean.h"
#include "Integer.h"

/*
    我希望
    年年此时都能和你一起看星空
*/

#ifndef Action__TreeSet
#define Action__TreeSet
namespace Action
{
    template <class T, class Tree = AVLTree<T> >
    class TreeSet: public Object
    {
        public:
            struct Pointer
            {
                private:
                    typename Tree::Pointer m_ptr;
                public:
                    Pointer(typename Tree::Pointer pointer) : m_ptr(pointer) {}
                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean(m_ptr == another.m_ptr);
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
                    T & operator *()
                    {
                        return m_ptr.operator * ();
                    }
                    T * operator ->()
                    {
                        return m_ptr.operator ->();
                    }
                    Pointer next() const
                    {
                        return m_ptr.next();
                    }
                    Pointer last() const
                    {
                        return m_ptr.last();
                    }
                    Pointer operator ++ (int)
                    {
                        return m_ptr++;
                    }
                    Pointer & operator ++()
                    {
                        ++m_ptr;
                        return *this;
                    }
                    Pointer operator -- (int)
                    {
                        return m_ptr--;
                    }
                    Pointer & operator --()
                    {
                        --m_ptr;
                        return *this;
                    }
            };

            TreeSet() {}
            TreeSet(const TreeSet & another) : m_tree(another.m_tree) {}
            TreeSet & operator = (const TreeSet & another)
            {
                m_tree = another.m_tree;
				return *this;
            }
            Boolean operator == (const TreeSet & another)
            {
                return to_array() == another.to_array();
            }
            virtual void insert(const T & element)
            {
                m_tree.insert(element);
            }
            virtual void erase(const T & element)
            {
                m_tree.erase(element);
            }
            virtual Boolean contains(const T & element) const
            {
                return Boolean(m_tree.find(element) != NULL);
            }
            virtual Integer size() const
            {
                return m_tree.size();
            }
            virtual Boolean empty() const
            {
                return Boolean(size() == 0);
            }
            virtual ArrayList<T> to_array() const
            {
                return m_tree.to_array();
            }
            virtual void clear()
            {
                m_tree.clear();
            }
            virtual Pointer begin() const
            {
                return Pointer(m_tree.begin());
            }
            virtual Pointer end() const
            {
                return Pointer(m_tree.end());
            }
            virtual Pointer v_begin() const
            {
                return Pointer(m_tree.v_begin());
            }
            virtual Pointer v_end() const
            {
                return Pointer(m_tree.v_end());
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
        protected:
            Tree m_tree;
    };
}
#endif /* Action__TreeSet */
