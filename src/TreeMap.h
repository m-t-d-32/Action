#include <iostream>
#include "AVLTree.h"
#include "Pair.h"
#include "Object.h"
#include "Integer.h"
#include "Boolean.h"
#include "Set_ElementNotExists.h"
#include "Map.h"

/*
    回忆凝结成力量
    随风奔向你
*/

#ifndef Action__TreeMap
#define Action__TreeMap
namespace Action
{
    template <class K, class V, class Tree = AVLTree<Pair<K, V> > >
    class TreeMap: public Map<K, V>
    {
        public:
            struct _Tree:public Tree{
                public:
                    Pair<K, V> * get_self(const Pair<K, V> & element) const{
                        return Tree::get_self(element);
                    }
            };

            struct Pointer
            {
                private:
                    typename Tree::Pointer m_ptr;
                public:
                    Pointer(typename Tree::Pointer ptr) : m_ptr(ptr) {}
                    Pair<K, V> operator *()
                    {
                        return *m_ptr;
                    }
                    const Pair<K, V> * operator ->()
                    {
                        return m_ptr.operator ->();
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
            virtual void insert(const K &, const V &);
            virtual V get(const K &) const;
            virtual V & operator [](const K &);
            virtual Boolean contains_key(const K &) const;
            virtual Boolean contains_value(const V &) const;
            virtual void erase(const K &);
            virtual void clear()
            {
                m_tree.clear();
            }
            virtual Integer size() const
            {
                return m_tree.size();
            }
            virtual Boolean empty() const
            {
                return (m_tree.size() == 0);
            }
            virtual ArrayList<Pair<K, V> > to_array() const
            {
                return m_tree.to_array();
            }

            virtual Pointer begin() const
            {
                return m_tree.begin();
            }
            virtual Pointer end() const
            {
                return m_tree.end();
            }
            virtual Pointer v_begin() const
            {
                return m_tree.v_begin();
            }
            virtual Pointer v_end() const
            {
                return m_tree.v_end();
            }
            virtual String get_name() const override
            {
                return "Action::TreeMap";
            }
            virtual String to_string() const override
            {
                return m_tree.to_array().to_string();
            }
            virtual ~TreeMap() {}
        private:
            _Tree m_tree;
    };
}
#endif /* Action__TreeMap */
