#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include "DefaultCompare.h"
#include "BTree_IllegalPointer.h"
#include "Pair.h"
#include "ArrayList.hpp"
#include "BTree_IllegalOrder.h"

/*
    愿你岁月无波澜
    敬我余生不悲欢
*/

#ifndef Action__BTree
#define Action__BTree

namespace Action
{
    template <class T, unsigned Order = 4, class Compare = DefaultCompare<T>, 
        template <class V> 
        class Container = ArrayList
    >
    class BTree: public Object
    {
        public:
            struct Node
            {
                Node * m_parent; 
                Container<T> m_values;
                Container<Node *> m_childs;
                Node()
                {
                    m_parent = NULL;
                }
            };
            /* Pointer
            {
                private:
                    const BTree * m_tree;
                    Node * m_node;
                public:
                    Pointer(const BTree * tree, Node * node) :
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
                            throw BTree_IllegalPointer();
                        return m_node->m_value;
                    }
                    T * operator ->()
                    {
                        if(!m_node)
                            throw BTree_IllegalPointer();
                        return & (m_node->m_value);
                    }
                    Pointer next() const
                    {
                        if(*this == m_tree->end())
                            throw BTree_IllegalPointer();
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
                            throw BTree_IllegalPointer();
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
            }; */
        private:
            Node * m_root;
            int m_size;
            Compare compare;
            void _clear(Node * _node)
            {
                if (!_node)
                    return;
                for (int i = 0; i < _node->m_childs.size(); ++i){
                    _clear(_node->m_childs[i]);
                }
                delete _node;
            }
            void _to_array(ArrayList<T> * now_array, const Node * _node) const
            {
                for (int i = 0; i < _node->m_values.size(); ++i){
                    if (!_node->m_childs.empty()){
                        _to_array(now_array, _node->m_childs.at(i));
                    }
                    now_array->push_back(_node->m_values.at(i));
                }
                if (!_node->m_childs.empty()){
                    _to_array(now_array, _node->m_childs.back());
                }
            }
            void _copy(Node * dest, Node * src)
            {
                dest->m_values.clear();
                dest->m_childs.clear();
                for (int i = 0; i < src->m_values.size(); ++i){
                    dest->m_values.push_back(src->m_values[i]);
                }
                for (int i = 0; i < src->m_childs.size(); ++i){
                    Node * new_node = new Node();
                    new_node->m_parent = dest;
                    _copy(new_node, src->m_childs[i]);
                    dest->m_childs.push_back(new_node);
                }
            }
            Node * _find(const T & element) const
            {
                if(!m_root)
                    return NULL;
                Node * floating_cursor = m_root;
                while(true)
                {
                    for (int i = 0; i < floating_cursor->m_values.size(); ++i){
                        int compare_value = compare(element, floating_cursor->m_values.at(i));
                        if (compare_value == 0){
                            return floating_cursor;
                        }
                        else if (compare_value < 0){
                            if (floating_cursor.m_childs.empty()){
                                return NULL;
                            }
                            else{
                                floating_cursor = floating_cursor.m_childs[i];
                            }
                        }
                        else if (compare_value > 0){
                            if (floating_cursor.m_childs.empty()){
                                return NULL;
                            }
                            else{
                                floating_cursor = floating_cursor.m_childs[i + 1];
                            }
                        }
                    }
                }
            }
            void adjust_split(Node * base_cursor){
                Node * floating_cursor = base_cursor;
                while (true){
                    if (floating_cursor->m_values.size() < Order) 
                        break;
                    else
                    {
                        Node * new_cursor = new Node();
                        Container<T> & left_part = floating_cursor->m_values;
                        Container<T> & right_part = new_cursor->m_values;
                        Container<Node *> & left_child = floating_cursor->m_childs;
                        Container<Node *> & right_child = new_cursor->m_childs;
                        int element_got = left_part.size().get_int() / 2;
                        int begin_got = 0, end_got = left_part.size().get_int();
                        typename Container<T>::Pointer begin_pos = left_part.begin();
                        typename Container<Node *>::Pointer begin_child = left_child.begin();
                        bool has_child = NOT left_child.empty();

                        for (; begin_got < element_got; ++begin_pos, ++begin_got){
                            if (has_child){
                                ++begin_child;
                            }
                        }                        
                        typename Container<T>::Pointer element_pos = begin_pos;
                        if (has_child){
                            ++begin_child;
                        }
                        for (++begin_pos; begin_pos != floating_cursor->m_values.end(); ++begin_pos){
                            right_part.push_back(*begin_pos);
                            if (has_child){
                                right_child.push_back(*begin_child);
                                (*begin_child)->m_parent = new_cursor;
                                ++begin_child;
                            }
                        }
                        if (has_child){
                            right_child.push_back(*begin_child);
                            (*begin_child)->m_parent = new_cursor;
                        }

                        if (!floating_cursor->m_parent){
                            m_root = new Node();
                            m_root->m_values.push_back(*element_pos);
                            m_root->m_childs.push_back(floating_cursor);
                            m_root->m_childs.push_back(new_cursor);
                            new_cursor->m_parent = floating_cursor->m_parent = m_root;
                        }
                        else{
                            Node * parent = floating_cursor->m_parent;
                            typename Container<T>::Pointer parent_pos = parent->m_values.begin();
                            typename Container<Node *>::Pointer parent_child = parent->m_childs.begin();
                            for (; parent_child != parent->m_childs.end(); ++parent_child, ++parent_pos){
                                if (*parent_child == floating_cursor) break;
                            }
                            ++parent_child;
                            parent->m_values.insert(parent_pos, *element_pos);
                            parent->m_childs.insert(parent_child, new_cursor);
                            new_cursor->m_parent = parent;
                        }

                        begin_got = element_got;
                        for (; begin_got != end_got; ++begin_got){
                            left_part.pop_back();
                            if (has_child){
                                left_child.pop_back();
                            }
                        }
                        floating_cursor = floating_cursor->m_parent;
                    }
                }
            }
        public:
            BTree() : m_root(NULL), m_size(0) {
                if (Order < 3){
                    throw BTree_IllegalOrder();
                }
            }
            BTree(const BTree & another)
            {
                if(!another.m_root)
                    return;
                m_root = new Node();
                _copy(m_root, another.m_root);
            }
            BTree & operator = (const BTree & another)
            {
                if(this == &another)
                    return *this;
                clear();
                if(!another.m_root)
                    return *this;
                m_root = new Node();
                _copy(m_root, another.m_root);
                return *this;
            }
            Integer size() const
            {
                return m_size;
            }
            /*Pointer begin() const
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
            }*/
            
            void insert(const T & element)
            {
                if(!m_root)
                {
                    m_root = new Node();
                    typename Container<T>::Pointer it = m_root->m_values.begin();
                    it.insert(element);
                }
                else
                {
                    Node * floating_cursor = m_root;
                    typename Container<T>::Pointer insert_pos = floating_cursor->m_values.begin();
                    typename Container<Node *>::Pointer child_pos = floating_cursor->m_childs.begin();                    
                    while (!floating_cursor->m_childs.empty()){
                        for (insert_pos = floating_cursor->m_values.begin(),
                            child_pos = floating_cursor->m_childs.begin();
                            insert_pos != floating_cursor->m_values.end(); 
                            ++insert_pos, ++child_pos){
                            int compare_value = compare(element, *insert_pos);
                            if (compare_value == 0)
                                return;
                            else if (compare_value < 0)
                                break;
                        }
                        floating_cursor = *child_pos;
                    }
                    for (insert_pos = floating_cursor->m_values.begin(); 
                        insert_pos != floating_cursor->m_values.end(); 
                        ++insert_pos){
                        int compare_value = compare(element, *insert_pos);
                        if (compare_value == 0)
                            return;
                        else if (compare_value < 0)
                            break;
                    }
                    insert_pos.insert(element);
                    adjust_split(floating_cursor);
                }
                ++m_size;
            }

            void erase(const T & element)
            {
                if(!m_root)
                    return;
                else
                {
                    Pair<Node *, int> find_value = _find(element);
                    Node cursor = find_value.key;
                    int item_index = find_value.value;

                    if(!cursor)
                        return;
                    if (!cursor->m_childs.empty()){
                        Node * new_cursor = cursor->m_childs[item_index];
                        while (!new_cursor->m_childs.empty()){
                            new_cursor = new_cursor->m_childs.back();
                        }
                        cursor->m_values[item_index] = new_cursor->m_value.back();
                        cursor = new_cursor;
                        item_index = new_cursor->m_value.size() - 1;
                    }

                }
                --m_size;
            }

            void _check(Node * root){
                if (root->m_childs.empty())
                    return;
                else if (root->m_values.size() + 1 == root->m_childs.size()){
                    for (typename ArrayList<Node *>::Pointer p = root->m_childs.begin(); p != root->m_childs.end(); ++p){
                        _check(*p);
                    }
                }
                else
                    throw 9;
            }
            void check(){
                _check(m_root);
            }
            String _to_string(const Node * root) const{
                String result = root->m_values.to_string();
                for (int i = 0; i < root->m_childs.size(); ++i){
                    result += _to_string(root->m_childs.at(i));
                }
                return result;
            }
            String to_string() const override{
                return _to_string(m_root);
            }
            virtual String get_name() const override
            {
                return "Action::BTree";
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
            ~BTree()
            {
                _clear(m_root);
            }
    };
}
#endif /* Action__BTree */
