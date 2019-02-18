#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include "DefaultCompare.h"
#include "BTree_IllegalPointer.h"
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
        class Container = LinkedList
    >
    class BTree: public Object
    {
        private:
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
            template <class A, class B>
            struct _Pair
            {
                A first;
                B second;
                _Pair(A _first, B _second):first(_first), second(_second){}
            };
        public:
            class Pointer
            {
                private:
                    const BTree * m_tree;
                    Node * m_node;
                    int m_index;
                public:
                    Pointer(const BTree * tree, Node * node, Integer index) :
                        m_tree(tree), m_node(node), m_index(index.get_int()) {}
                    Boolean operator == (const Pointer & another) const
                    {
                        return Boolean(m_tree == another.m_tree && m_node == another.m_node && m_index == another.m_index);
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
                    T operator *()
                    {
                        if(!m_node)
                            throw BTree_IllegalPointer();
                        typename Container<T>::Pointer it = (m_node->m_values).begin();
                        for (int i = 0; i < m_index; ++i){
                            ++it;
                        }
                        return *it;
                    }
                    const T * operator ->()
                    {
                        if(!m_node)
                            throw BTree_IllegalPointer();
                        typename Container<T>::Pointer it = (m_node->m_values).begin();
                        for (int i = 0; i < m_index; ++i){
                            ++it;
                        }
                        return &(*it);
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
                            Node * floating_cursor = m_node;
                            if (m_index < floating_cursor->m_values.size() - 1 && floating_cursor->m_childs.size() == 0){
                                return Pointer(m_tree, floating_cursor, m_index + 1);
                            }
                            else if (m_index < floating_cursor->m_values.size() && floating_cursor->m_childs.size() > 0){
                                typename Container<Node *>::Pointer begin_child = (floating_cursor->m_childs).begin();
                                for (int i = 0; i < m_index; ++i){
                                    ++begin_child;
                                }
                                floating_cursor = *++begin_child;
                                while(floating_cursor->m_childs.size() > 0){
                                    floating_cursor = *floating_cursor->m_childs.begin();
                                }
                                return Pointer(m_tree, floating_cursor, 0);
                            }
                            else {
                                while (floating_cursor == *--(floating_cursor->m_parent->m_childs).end()){
                                    floating_cursor = floating_cursor->m_parent;
                                }
                                typename Container<Node *>::Pointer begin_child = (floating_cursor->m_parent->m_childs).begin();
                                for (int i = 0; i < (floating_cursor->m_parent->m_childs).size(); ++i, ++begin_child){
                                    if (*begin_child == floating_cursor){
                                        return Pointer(m_tree, floating_cursor->m_parent, i);
                                    }
                                }
                            }
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
                            Node * floating_cursor = m_node;
                            if (m_index > 0 && floating_cursor->m_childs.size() == 0){
                                    return Pointer(m_tree, floating_cursor, m_index - 1);
                            }
                            else if (m_index >= 0 && floating_cursor->m_childs.size() > 0){
                                typename Container<Node *>::Pointer begin_child = (floating_cursor->m_childs).begin();
                                for (int i = 0; i < m_index; ++i){
                                    ++begin_child;
                                }
                                floating_cursor = *begin_child;
                                while(floating_cursor->m_childs.size() > 0){
                                    floating_cursor = *--floating_cursor->m_childs.end();
                                }
                                return Pointer(m_tree, floating_cursor, floating_cursor->m_values.size() - 1);
                            }
                            else {
                                while (floating_cursor == *(floating_cursor->m_parent->m_childs).begin()){
                                    floating_cursor = floating_cursor->m_parent;
                                }
                                typename Container<Node *>::Pointer begin_child = (floating_cursor->m_parent->m_childs).begin();
                                for (int i = 0; i < (floating_cursor->m_parent->m_childs).size(); ++i, ++begin_child){
                                    if (*begin_child == floating_cursor){
                                        return Pointer(m_tree, floating_cursor->m_parent, i - 1);
                                    }
                                }
                            }
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
                if (!_node)
                    return;
                for (int i = 0; i < _node->m_childs.size(); ++i){
                    _clear(_node->m_childs[i]);
                }
                delete _node;
            }
            void _to_array(ArrayList<T> * now_array, const Node * root) const
            {
                if (!root)
                    return;
                for (int i = 0; i < root->m_values.size(); ++i){
                    if (!root->m_childs.empty()){
                        _to_array(now_array, root->m_childs.at(i));
                    }
                    now_array->push_back(root->m_values.at(i));
                }
                if (!root->m_childs.empty()){
                    _to_array(now_array, root->m_childs.back());
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
            _Pair<Node *, int> _find(const T & element) const
            {
                if(!m_root)
                    return _Pair<Node *, int>(NULL, 0);
                Node * floating_cursor = m_root;
                while(true)
                {
                    int pos = 0;
                    Container<T> & values = floating_cursor->m_values;
                    Container<Node *> childs = floating_cursor->m_childs;
                    typename Container<T>::Pointer begin_pos = values.begin();
                    typename Container<Node *>::Pointer begin_child = childs.begin();
                    for (; begin_pos != values.end(); ++begin_pos, ++pos){
                        int compare_value = compare(element, *begin_pos);
                        if (compare_value == 0){
                            return _Pair<Node *, int>(floating_cursor, pos);
                        }
                        else if (compare_value < 0){
                            if (floating_cursor->m_childs.empty()){
                                return _Pair<Node *, int>(NULL, 0);
                            }
                            else{
                                floating_cursor = *begin_child;
                                break;
                            }
                        }
                        if (childs.size() > 0){
                            ++begin_child;
                        }
                    }
                    if (begin_pos == values.end()){
                        if (floating_cursor->m_childs.empty()){
                            return _Pair<Node *, int>(NULL, 0);
                        }
                        else{
                            floating_cursor = *begin_child;
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
            void adjust_union(Node * base_cursor){
                Node * floating_cursor = base_cursor;
                while (true){
                    if (floating_cursor->m_values.size() >= (Order - 1) / 2)
                        break;
                    else if (!floating_cursor->m_parent){
                        if (floating_cursor->m_values.size() == 0){
                            if (floating_cursor->m_childs.size() == 0){
                                delete floating_cursor;
                                m_root = NULL;
                            }
                            else {
                                Node * _root = m_root;
                                m_root = *floating_cursor->m_childs.begin();
                                m_root->m_parent = NULL;
                                delete _root;
                            }
                        }
                        break;
                    }
                    else {
                        Node * parent = floating_cursor->m_parent;
                        typename Container<T>::Pointer value_pos = parent->m_values.begin();
                        typename Container<Node *>::Pointer child_pos = parent->m_childs.begin();
                        for (; child_pos != parent->m_childs.end(); ++child_pos, ++value_pos){
                            if (*child_pos == floating_cursor) break;
                        }
                        typename Container<Node *>::Pointer left_brother_pos = child_pos, right_brother_pos = child_pos;
                        --left_brother_pos;
                        ++right_brother_pos;
                        if (bool(right_brother_pos != parent->m_childs.end()) && bool((*right_brother_pos)->m_values.size() > (Order - 1) / 2)){
                            (*child_pos)->m_values.push_back(*value_pos);
                            *value_pos = *(*right_brother_pos)->m_values.begin();
                            (*right_brother_pos)->m_values.erase((*right_brother_pos)->m_values.begin());
                            if (!(*right_brother_pos)->m_childs.empty()){
                                (*child_pos)->m_childs.push_back(*(*right_brother_pos)->m_childs.begin());
                                (*(*right_brother_pos)->m_childs.begin())->m_parent = *child_pos;
                                (*right_brother_pos)->m_childs.erase((*right_brother_pos)->m_childs.begin());
                            }
                            break;
                        }
                        else if (bool(child_pos != parent->m_childs.begin()) && bool((*left_brother_pos)->m_values.size() > (Order - 1) / 2)){
                            --value_pos;
                            (*child_pos)->m_values.insert((*child_pos)->m_values.begin(), *value_pos);
                            *value_pos = (*left_brother_pos)->m_values.back();
                            (*left_brother_pos)->m_values.pop_back();
                            if (!(*left_brother_pos)->m_childs.empty()){
                                (*child_pos)->m_childs.insert((*child_pos)->m_childs.begin(), (*left_brother_pos)->m_childs.back());
                                (*left_brother_pos)->m_childs.back()->m_parent = *child_pos;
                                (*left_brother_pos)->m_childs.pop_back();
                            }
                            break;
                        }
                        else if (right_brother_pos != parent->m_childs.end()){
                            (*child_pos)->m_values.push_back(*value_pos);
                            for (typename Container<T>::Pointer it = (*right_brother_pos)->m_values.begin();
                                it != (*right_brother_pos)->m_values.end(); ++it){
                                    (*child_pos)->m_values.push_back(*it);
                            }
                            for (typename Container<Node *>::Pointer it = (*right_brother_pos)->m_childs.begin();
                                it != (*right_brother_pos)->m_childs.end(); ++it){
                                    (*child_pos)->m_childs.push_back(*it);
                                    (*it)->m_parent = (*child_pos);
                            }
                            parent->m_values.erase(value_pos);
                            delete *right_brother_pos;
                            parent->m_childs.erase(right_brother_pos);
                            floating_cursor = parent;
                        }
                        else {
                            --value_pos;
                            (*left_brother_pos)->m_values.push_back(*value_pos);
                            for (typename Container<T>::Pointer it = (*child_pos)->m_values.begin();
                                it != (*child_pos)->m_values.end(); ++it){
                                    (*left_brother_pos)->m_values.push_back(*it);
                            }
                            for (typename Container<Node *>::Pointer it = (*child_pos)->m_childs.begin();
                                it != (*child_pos)->m_childs.end(); ++it){
                                    (*left_brother_pos)->m_childs.push_back(*it);
                                    (*it)->m_parent = (*left_brother_pos);
                            }
                            parent->m_values.erase(value_pos);
                            delete *child_pos;
                            parent->m_childs.erase(child_pos);
                            floating_cursor = parent;
                        }
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
            Pointer begin() const
            {
                if (!m_root){
                    return end();
                }
                Node * min_node = m_root;
                while(!min_node->m_childs.empty())
                    min_node = *((min_node->m_childs).begin());
                return Pointer(this, min_node, 0);
            }
            Pointer end() const
            {
                return Pointer(this, (Node *) BAD_MEMORY_0, 0);
            }
            Pointer v_begin() const
            {
                return Pointer(this, (Node *) BAD_MEMORY_1, 0);
            }
            Pointer v_end() const
            {
                if (!m_root){
                    return v_begin();
                }
                Node * max_node = m_root;
                while(!max_node->m_childs.empty())
                    max_node = *--((max_node->m_childs).end());
                return Pointer(this, max_node, (max_node->m_values).size().get_int() - 1);
            }          
            void insert(const T & element)
            {
                if(!m_root)
                {
                    m_root = new Node();
                    typename Container<T>::Pointer it = m_root->m_values.begin();
                    m_root->m_values.insert(it, element);
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
                    floating_cursor->m_values.insert(insert_pos, element);
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
                    _Pair<Node *, int> find_value = _find(element);
                    Node *cursor = find_value.first;
                    int item_index = find_value.second;
                    if(!cursor)
                        return;
                    typename Container<T>::Pointer result_pos = cursor->m_values.begin();
                    if (!cursor->m_childs.empty()){
                        typename Container<T>::Pointer begin_value = cursor->m_values.begin();
                        typename Container<Node *>::Pointer begin_child = cursor->m_childs.begin();
                        for (int i = 0; i < item_index; ++i){
                            ++begin_child;
                            ++begin_value;
                        }
                        Node * new_cursor = *begin_child;
                        while (!new_cursor->m_childs.empty()){
                            new_cursor = new_cursor->m_childs.back();
                        }
                        cursor = new_cursor;
                        result_pos = new_cursor->m_values.end();
                        --result_pos;
                        *begin_value = *result_pos;
                    }
                    else {
                        for (int i = 0; i < item_index; ++i){
                            ++result_pos;
                        }
                    }
                    cursor->m_values.erase(result_pos);
                    adjust_union(cursor);
                }
                --m_size;
            }
            Boolean find(const T & element) const{
                return Boolean(_find(element).first != NULL);
            }
            virtual String get_name() const override
            {
                return "Action::BTree";
            }
            virtual ArrayList<T> to_array() const override
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
        protected:
            T * get_self(const T & element) const {
                _Pair<Node *, int> _node = _find(element);
                if (_node.first == NULL){
                    return NULL;
                }                
                typename Container<T>::Pointer it = _node.first->m_values.begin();
                for (; it != _node.first->m_values.end(), --_node.second != 0; ++it);
                return &(*it);
            }
    };
}
#endif /* Action__BTree */
