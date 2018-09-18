#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include "DefaultCompare.h"
#include "AVLTree_IllegalPointer.h"
#include "ArrayList.h"

/*
    想去了解你
    了解你光芒以外的地方
*/

#ifndef Action__AVLTree
#define Action__AVLTree
namespace Action
{
    template <class T, class Compare = DefaultCompare<T> >
    class AVLTree: public Object
    {
        public:
            struct Node
            {
                Node *m_left, *m_right, *m_parent;
                int m_height;
                T m_value;
                Node(const T & value) : m_value(value)
                {
                    m_left = m_right = m_parent = NULL;
                    m_height = 0;
                }
            };
            struct Pointer
            {
                private:
                    const AVLTree * m_tree;
                    Node * m_node;
                public:
                    Pointer(const AVLTree * tree, Node * node) :
                        m_tree(tree), m_node(node) {}
                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean(m_tree == another.m_tree && m_node == another.m_node);
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
                    T & operator *()
                    {
                        if(!m_node)
                            throw AVLTree_IllegalPointer();
                        return m_node->m_value;
                    }
                    T * operator ->()
                    {
                        if(!m_node)
                            throw AVLTree_IllegalPointer();
                        return & (m_node->m_value);
                    }
                    Pointer next() const
                    {
                        if(!m_node)
                            throw AVLTree_IllegalPointer();
                        else if(m_node->m_right)
                        {
                            Node * address_cursor = m_node->m_right;
                            while(address_cursor->m_left)
                            {
                                address_cursor = address_cursor->m_left;
                            }
                            return Pointer(m_tree, address_cursor);
                        }
                        else
                        {
                            Node * address_cursor = m_node;
                            while(address_cursor->m_parent)
                            {
                                if(address_cursor == address_cursor->m_parent->m_right)
                                    address_cursor = address_cursor->m_parent;
                                else
                                    return Pointer(m_tree, address_cursor->m_parent);
                            }
                        }
                        return Pointer(m_tree, NULL);
                    }
                    Pointer last() const
                    {
                        if(!m_node)
                            throw AVLTree_IllegalPointer();
                        else if(m_node->m_left)
                        {
                            Node * address_cursor = m_node->m_left;
                            while(address_cursor->m_right)
                            {
                                address_cursor = address_cursor->m_right;
                            }
                            return Pointer(m_tree, address_cursor);
                        }
                        else
                        {
                            Node * address_cursor = m_node;
                            while(address_cursor->m_parent)
                            {
                                if(address_cursor == address_cursor->m_parent->m_left)
                                    address_cursor = address_cursor->m_parent;
                                else
                                    return Pointer(m_tree, address_cursor->m_parent);
                            }
                        }
                        return Pointer(m_tree, NULL);
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
            Node * R_rotate(Node * future_root)
            {
                future_root->m_parent->m_left = future_root->m_right;
                if(future_root->m_right)
                {
                    future_root->m_right->m_parent = future_root->m_parent;
                }
                future_root->m_right = future_root->m_parent;
                future_root->m_parent = future_root->m_right->m_parent;
                if(future_root->m_right->m_parent)
                {
                    if(future_root->m_right->m_parent->m_left == future_root->m_right)
                    {
                        future_root->m_right->m_parent->m_left = future_root;
                    }
                    else
                    {
                        future_root->m_right->m_parent->m_right = future_root;
                    }
                }
                else
                {
                    m_root = future_root;
                }
                future_root->m_right->m_parent = future_root;
                return future_root;
            }
            Node * L_rotate(Node * future_root)
            {
                future_root->m_parent->m_right = future_root->m_left;
                if(future_root->m_left)
                {
                    future_root->m_left->m_parent = future_root->m_parent;
                }
                future_root->m_left = future_root->m_parent;
                future_root->m_parent = future_root->m_left->m_parent;
                if(future_root->m_left->m_parent)
                {
                    if(future_root->m_left->m_parent->m_left == future_root->m_left)
                    {
                        future_root->m_left->m_parent->m_left = future_root;
                    }
                    else
                    {
                        future_root->m_left->m_parent->m_right = future_root;
                    }
                }
                else
                {
                    m_root = future_root;
                }
                future_root->m_left->m_parent = future_root;
                return future_root;
            }
            void adjust(Node * address_cursor)
            {
                while(address_cursor)
                {
                    int left_height = address_cursor->m_left ? address_cursor->m_left->m_height : -1;
                    int right_height = address_cursor->m_right ? address_cursor->m_right->m_height : -1;
                    if(left_height - right_height >= 2)
                    {
                        int left_left_height = address_cursor->m_left->m_left ? address_cursor->m_left->m_left->m_height : -1;
                        int left_right_height = address_cursor->m_left->m_right ? address_cursor->m_left->m_right->m_height : -1;
                        if(left_left_height < left_right_height)
                        {
                            L_rotate(address_cursor->m_left->m_right);
                        }
                        address_cursor = R_rotate(address_cursor->m_left);
                    }
                    else if(left_height - right_height <= -2)
                    {
                        int right_right_height = address_cursor->m_right->m_right ? address_cursor->m_right->m_right->m_height : -1;
                        int right_left_height = address_cursor->m_right->m_left ? address_cursor->m_right->m_left->m_height : -1;
                        if(right_right_height < right_left_height)
                        {
                            R_rotate(address_cursor->m_right->m_left);
                        }
                        address_cursor = L_rotate(address_cursor->m_right);
                    }
                    left_height = address_cursor->m_left ? address_cursor->m_left->m_height : -1;
                    right_height = address_cursor->m_right ? address_cursor->m_right->m_height : -1;
                    address_cursor->m_height = left_height > right_height ? (left_height + 1) : (right_height + 1);
                    address_cursor = address_cursor->m_parent;
                }
            }
            void _to_array(ArrayList<T> * now_array, const Node * _node) const
            {
                if(_node == NULL)
                    return;
                _to_array(now_array, _node->m_left);
                (*now_array).push_back(_node->m_value);
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
        public:
            AVLTree() : m_root(NULL), m_size(0) {}
            AVLTree(const AVLTree & another)
            {
                if(!another.m_root)
                    return;
                m_root = new Node((another.m_root)->m_value);
                _copy(m_root, another.m_root);
            }
            AVLTree & operator = (const AVLTree & another)
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
                Node * max_node = m_root;
                while(max_node->m_right)
                    max_node = max_node->m_right;
                return Pointer(this, max_node);
            }
            Node * find(const T & element) const
            {
                if(!m_root)
                    return NULL;
                Node * address_cursor = m_root;
                while(true)
                {
                    int compare_value = compare(element, address_cursor->m_value);
                    if(compare_value < 0)
                    {
                        if(!address_cursor->m_left)
                        {
                            return NULL;
                        }
                        else
                        {
                            address_cursor = address_cursor->m_left;
                        }
                    }
                    else if(compare_value > 0)
                    {
                        if(!address_cursor->m_right)
                        {
                            return NULL;
                        }
                        else
                        {
                            address_cursor = address_cursor->m_right;
                        }
                    }
                    else
                    {
                        return address_cursor;
                    }
                }
            }
            void insert(const T & element)
            {
                if(!m_root)
                {
                    m_root = new Node(element);
                }
                else
                {
                    Node * address_cursor = m_root;
                    while(true)
                    {
                        int compare_value = compare(element, address_cursor->m_value);
                        if(compare_value == 0)
                        {
                            return;
                        }
                        else if(compare_value > 0)
                        {
                            if(address_cursor->m_right)
                            {
                                address_cursor = address_cursor->m_right;
                            }
                            else
                            {
                                address_cursor->m_right = new Node(element);
                                address_cursor->m_right->m_parent = address_cursor;
                                break;
                            }
                        }
                        else
                        {
                            if(address_cursor->m_left)
                            {
                                address_cursor = address_cursor->m_left;
                            }
                            else
                            {
                                address_cursor->m_left = new Node(element);
                                address_cursor->m_left->m_parent = address_cursor;
                                break;
                            }
                        }
                    }
                    adjust(address_cursor);
                }
                ++m_size;
            }
            void erase(const T & element)
            {
                if(!m_root)
                    return;
                else
                {
                    Node * address_cursor = find(element);
                    if(!address_cursor)
                        return;
                    if(address_cursor->m_left && address_cursor->m_right)
                    {
                        Node * right_min_node = address_cursor->m_right;
                        while(right_min_node->m_left)
                            right_min_node = right_min_node->m_left;
                        address_cursor->m_value = right_min_node->m_value;
                        address_cursor = right_min_node;
                    }
                    if(!address_cursor->m_left)
                    {
                        if(address_cursor->m_parent)
                        {
                            if(address_cursor->m_parent->m_right == address_cursor)
                            {
                                address_cursor->m_parent->m_right = address_cursor->m_right;
                            }
                            else
                            {
                                address_cursor->m_parent->m_left = address_cursor->m_right;
                            }
                            if(address_cursor->m_right)
                            {
                                address_cursor->m_right->m_parent = address_cursor->m_parent;
                            }
                            Node * temp_node_address = address_cursor;
                            address_cursor = address_cursor->m_parent;
                            delete temp_node_address;
                        }
                        else
                        {
                            Node * temp_node_address = address_cursor;
                            m_root = address_cursor = address_cursor->m_right;
                            if(m_root)
                            {
                                m_root->m_parent = NULL;
                            }
                            delete temp_node_address;
                        }
                    }
                    else
                    {
                        if(address_cursor->m_parent)
                        {
                            if(address_cursor->m_parent->m_right == address_cursor)
                            {
                                address_cursor->m_parent->m_right = address_cursor->m_left;
                            }
                            else
                            {
                                address_cursor->m_parent->m_left = address_cursor->m_left;
                            }
                            if(address_cursor->m_left)
                            {
                                address_cursor->m_left->m_parent = address_cursor->m_parent;
                            }
                            Node * temp_node_address = address_cursor;
                            address_cursor = address_cursor->m_parent;
                            delete temp_node_address;
                        }
                        else
                        {
                            Node * temp_node_address = address_cursor;
                            m_root = address_cursor = address_cursor->m_left;
                            if(m_root)
                            {
                                m_root->m_parent = NULL;
                            }
                            delete temp_node_address;
                        }
                    }
                    adjust(address_cursor);
                }
                --m_size;
            }
            virtual String get_name() const override
            {
                return "Action::AVLTree";
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
            ~AVLTree()
            {
                clear();
            }
    };
}
#endif /* Action__AVLTree */
