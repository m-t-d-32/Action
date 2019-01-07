#include <iostream>
#include "AVLTree.h"
#include "Pair.h"
#include "Object.h"
#include "Integer.h"
#include "Boolean.h"
#include "Set_ElementNotExists.h"

/*
    回忆凝结成力量
    随风奔向你
*/

#ifndef Action__TreeMap
#define Action__TreeMap
namespace Action
{
    template <class K, class V, class Tree = AVLTree<Pair<K, V> > >
    class TreeMap: public Object
    {
        public:
            class PairSet: public Tree
            {
                public:
                    virtual Pair<K, V> & get(const Pair<K, V> & another_key) const
                    {
                        typename Tree::Node * element_address = this->find(another_key);
                        if(!element_address)
                        {
                            throw Set_ElementNotExists();
                        }
                        else
                        {
                            return element_address->m_value;
                        }
                    }
            };

            struct Pointer
            {
                private:
                    typename Tree::Pointer m_ptr;
                public:
                    Pointer(typename Tree::Pointer ptr) : m_ptr(ptr) {}
                    Pair<K, V>  & operator *()
                    {
                        return *m_ptr;
                    }
                    Pair<K, V>  * operator ->()
                    {
                        return & (*m_ptr);
                    }
                    Pointer & operator ++()
                    {
                        ++m_ptr;
                        return *this;
                    }
                    Pointer operator ++ (int)
                    {
                        return Pointer(m_ptr++);
                    }
                    Pointer & operator --()
                    {
                        --m_ptr;
                        return *this;
                    }
                    Pointer operator -- (int)
                    {
                        return Pointer(m_ptr--);
                    }
                    Pointer next() const
                    {
                        return Pointer(m_ptr.next());
                    }
                    Pointer last() const
                    {
                        return Pointer(m_ptr.last());
                    }
                    Boolean operator == (const Pointer & another) const
                    {
                        return m_ptr == another.m_ptr;
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
            };

            friend struct Pointer;
        public:
            TreeMap() {}
            TreeMap(const TreeMap &);
            TreeMap & operator = (const TreeMap &);
            virtual void insert(K, V);
            virtual V get(K) const;
            virtual V & operator [](K);
            virtual Boolean contains_key(K);
            virtual Boolean contains_value(V);
            virtual void erase(K);
            virtual void clear()
            {
                m_set.clear();
            }
            virtual Integer size()
            {
                return m_set.size();
            }
            virtual Boolean empty()
            {
                return (m_set.size() == 0);
            }
            virtual ArrayList<Pair<K, V> > to_array()
            {
                return m_set.to_array();
            }

            virtual Pointer begin() const
            {
                return m_set.begin();
            }
            virtual Pointer end() const
            {
                return m_set.end();
            }
            virtual Pointer v_begin() const
            {
                return m_set.v_begin();
            }
            virtual Pointer v_end() const
            {
                return m_set.v_end();
            }
            virtual String get_name() const override
            {
                return "Action::TreeMap";
            }
            virtual String to_string() const override
            {
                return m_set.to_array().to_string();
            }
            virtual ~TreeMap() {}
        private:
            PairSet m_set;
    };
}
#endif /* Action__TreeMap */
