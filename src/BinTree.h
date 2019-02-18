#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include "DefaultCompare.h"
#include "BinTree_IllegalPointer.h"
#include "ArrayList.h"

/*
    我们的征途是星辰大海
*/

#ifndef Action__BinTree
#define Action__BinTree
namespace Action
{
    template <class T, class Compare = DefaultCompare<T> >
    class BinTree: public Object
    {
        public:
            struct Node
            {
                Node * m_left, * m_right, * m_parent;
                T m_value;
                Node(const T & value) : m_value(value)
                {
                    m_left = m_right = m_parent = NULL;
                }
            };
            struct Pointer
            {
                private:
                    const BinTree * m_tree;
                    Node * m_node;
                public:
                    Pointer(const BinTree * tree, Node * node) :
                        m_tree(tree), m_node(node) {}
                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean(m_tree == another.m_tree && m_node == another.m_node);
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
                    T operator *()
                    {
                        if(!m_node)
                            throw BinTree_IllegalPointer();
                        return m_node->m_value;
                    }
                    const T * operator ->()
                    {
                        if(!m_node)
                            throw BinTree_IllegalPointer();
                        return & (m_node->m_value);
                    }
                    Pointer next() const
                    {
                        if(*this == m_tree->end())
                            throw BinTree_IllegalPointer();
                        else if(*this == m_tree->v_end())
                            return m_tree->end();
                        else if(*this == m_tree->v_begin())
                            return m_tree->begin();
                        else
                        {
                            if(m_node->m_right)
                            {
                                Node * floating_cursor = m_node->m_right;
                                while(floating_cursor->m_left)
                                {
                                    floating_cursor = floating_cursor->m_left;
                                }
                                return Pointer(m_tree, floating_cursor);
                            }
                            else
                            {
                                Node * floating_cursor = m_node;
                                while(floating_cursor->m_parent)
                                {
                                    if(floating_cursor == floating_cursor->m_parent->m_right)
                                        floating_cursor = floating_cursor->m_parent;
                                    else
                                        return Pointer(m_tree, floating_cursor->m_parent);
                                }
                            }
                            return Pointer(m_tree, NULL);
                        }
                    }
                    Pointer last() const
                    {
                        if(*this == m_tree->v_begin())
                            throw BinTree_IllegalPointer();
                        else if(*this == m_tree->begin())
                            return m_tree->v_begin();
                        else if(*this == m_tree->end())
                            return m_tree->v_end();
                        else
                        {
                            if(m_node->m_left)
                            {
                                Node * floating_cursor = m_node->m_left;
                                while(floating_cursor->m_right)
                                {
                                    floating_cursor = floating_cursor->m_right;
                                }
                                return Pointer(m_tree, floating_cursor);
                            }
                            else
                            {
                                Node * floating_cursor = m_node;
                                while(floating_cursor->m_parent)
                                {
                                    if(floating_cursor == floating_cursor->m_parent->m_left)
                                        floating_cursor = floating_cursor->m_parent;
                                    else
                                        return Pointer(m_tree, floating_cursor->m_parent);
                                }
                            }
                            return Pointer(m_tree, NULL);
                        }
                    }
                    Pointer & operator ++()
                    {
                        *this = next();
                        return *this;
                    }
                    Pointer operator ++ (int)
                    {
                        Pointer return_value = *this;
                        *this = next();
                        return return_value;
                    }
                    Pointer & operator --()
                    {
                        *this = last();
                        return *this;
                    }
                    Pointer operator -- (int)
                    {
                        Pointer return_value = *this;
                        *this = last();
                        return return_value;
                    }
            };
        private:
            Node * m_root;
            int m_size;
            Compare compare;
            void _clear(Node * _node)
            {
                if(!_node)
                    return;
                _clear(_node->m_left);
                _clear(_node->m_right);
                delete _node;
            }
            void _to_array(ArrayList<T> * now_array, const Node * _node) const
            {
                if(!_node)
                    return;
                _to_array(now_array, _node->m_left);
                now_array->push_back(_node->m_value);
                _to_array(now_array, _node->m_right);
            }
            void _copy(Node * dest, Node * src)
            {
                if(src->m_left)
                {
                    dest->m_left = new Node(src->m_left->m_value);
                    dest->m_left->m_parent = dest;
                    _copy(dest->m_left, src->m_left);
                }
                if(src->m_right)
                {
                    dest->m_right = new Node(src->m_right->m_value);
                    dest->m_right->m_parent = dest;
                    _copy(dest->m_right, src->m_right);
                }
            }
            Node * _find(const T & element) const
            {
                if(!m_root)
                    return NULL;
                Node * floating_cursor = m_root;
                while(true)
                {
                    int compare_value = compare(element, floating_cursor->m_value);
                    if(compare_value < 0)
                    {
                        if(!floating_cursor->m_left)
                        {
                            return NULL;
                        }
                        else
                        {
                            floating_cursor = floating_cursor->m_left;
                        }
                    }
                    else if(compare_value > 0)
                    {
                        if(!floating_cursor->m_right)
                        {
                            return NULL;
                        }
                        else
                        {
                            floating_cursor = floating_cursor->m_right;
                        }
                    }
                    else
                    {
                        return floating_cursor;
                    }
                }
            }
        public:
            BinTree() : m_root(NULL), m_size(0) {}
            BinTree(const BinTree & another)
            {
                if(!another.m_root)
                    return;
                m_root = new Node((another.m_root)->m_value);
                _copy(m_root, another.m_root);
            }
            BinTree & operator = (const BinTree & another)
            {
                if(this == &another)
                    return *this;
                clear();
                if(!another.m_root)
                    return *this;
                m_root = new Node((another.m_root)->m_value);
                _copy(m_root, another.m_root);
                return *this;
            }
            Integer size() const
            {
                return m_size;
            }
            Pointer begin() const
            {
                if (!m_root){
                    return end();
                }
                Node * min_node = m_root;
                while(min_node->m_left)
                    min_node = min_node->m_left;
                return Pointer(this, min_node);
            }
            Pointer end() const
            {
                return Pointer(this, (Node *) BAD_MEMORY_0);
            }
            Pointer v_begin() const
            {
                return Pointer(this, (Node *) BAD_MEMORY_1);
            }
            Pointer v_end() const
            {
                if (!m_root){
                    return v_begin();
                }
                Node * max_node = m_root;
                while(max_node->m_right)
                    max_node = max_node->m_right;
                return Pointer(this, max_node);
            }
            Boolean find(const T & element) const
            {
                return Boolean(_find(element) != NULL);
            }
            void insert(const T & element)
            {
                if(!m_root)
                {
                    m_root = new Node(element);
                }
                else
                {
                    Node * floating_cursor = m_root;
                    while(true)
                    {
                        int compare_value = compare(element, floating_cursor->m_value);
                        if(compare_value == 0)
                        {
                            return;
                        }
                        else if(compare_value > 0)
                        {
                            if(floating_cursor->m_right)
                            {
                                floating_cursor = floating_cursor->m_right;
                            }
                            else
                            {
                                floating_cursor->m_right = new Node(element);
                                floating_cursor->m_right->m_parent = floating_cursor;
                                break;
                            }
                        }
                        else
                        {
                            if(floating_cursor->m_left)
                            {
                                floating_cursor = floating_cursor->m_left;
                            }
                            else
                            {
                                floating_cursor->m_left = new Node(element);
                                floating_cursor->m_left->m_parent = floating_cursor;
                                break;
                            }
                        }
                    }
                }
                ++m_size;
            }
            void erase(const T & element)
            {
                if(!m_root)
                    return;
                else
                {
                    Node * cursor = _find(element);
                    if(!cursor)
                        return;
                    if(cursor->m_left && cursor->m_right)
                    {
                        Node * right_min_node = cursor->m_right;
                        while(right_min_node->m_left)
                            right_min_node = right_min_node->m_left;
                        cursor->m_value = right_min_node->m_value;
                        cursor = right_min_node;
                    }
                    if(!cursor->m_left)
                    {
                        if(cursor->m_parent)
                        {
                            if(cursor->m_parent->m_right == cursor)
                            {
                                cursor->m_parent->m_right = cursor->m_right;
                            }
                            else
                            {
                                cursor->m_parent->m_left = cursor->m_right;
                            }
                            if(cursor->m_right)
                            {
                                cursor->m_right->m_parent = cursor->m_parent;
                            }
                            Node * temp_node_address = cursor;
                            cursor = cursor->m_parent;
                            delete temp_node_address;
                        }
                        else
                        {
                            Node * temp_node_address = cursor;
                            m_root = cursor = cursor->m_right;
                            if(m_root)
                            {
                                m_root->m_parent = NULL;
                            }
                            delete temp_node_address;
                        }
                    }
                    else
                    {
                        if(cursor->m_parent)
                        {
                            if(cursor->m_parent->m_right == cursor)
                            {
                                cursor->m_parent->m_right = cursor->m_left;
                            }
                            else
                            {
                                cursor->m_parent->m_left = cursor->m_left;
                            }
                            if(cursor->m_left)
                            {
                                cursor->m_left->m_parent = cursor->m_parent;
                            }
                            Node * temp_node_address = cursor;
                            cursor = cursor->m_parent;
                            delete temp_node_address;
                        }
                        else
                        {
                            Node * temp_node_address = cursor;
                            m_root = cursor = cursor->m_left;
                            if(m_root)
                            {
                                m_root->m_parent = NULL;
                            }
                            delete temp_node_address;
                        }
                    }
                }
                --m_size;
            }
            virtual String get_name() const override
            {
                return "Action::BinTree";
            }
            virtual ArrayList<T> to_array() const
            {
                ArrayList<T> return_value;
                _to_array(&return_value, m_root);
                return return_value;
            }
            void clear()
            {
                _clear(m_root);
                m_root = NULL;
            }
            ~BinTree()
            {
                _clear(m_root);
            }
        protected:
            T * get_self(const T & element) const {
                Node * result = _find(element);
                return result ? &result->m_value : NULL;
            }
    };
}
#endif /* Action__BinTree */
