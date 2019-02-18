#include <iostream>
#include "TreeMap.h"
#include "String.h"
#include "Set_ElementNotExists.h"

#ifndef TREEMAP__CPP
#define TREEMAP__CPP
namespace Action
{
    template<class K, class V, class Tree>
    TreeMap<K, V, Tree>::TreeMap(const TreeMap & another):
        m_tree(another.m_tree){}

    template<class K, class V, class Tree>
    TreeMap<K, V, Tree> & TreeMap<K, V, Tree>::operator = (const TreeMap & another)
    {
        if(this == &another)
            return *this;
        m_tree = another.m_tree;
        return *this;
    }

    template<class K, class V, class Tree>
    void TreeMap<K, V, Tree>::insert(const K & key, const V & value)
    {
        Pair<K, V> put_pair(key, value);
        Pair<K, V> * get_pair = m_tree.get_self(put_pair);
        if (get_pair)
        {
            get_pair->value = value;
        }
        else
        {
            m_tree.insert(put_pair);
        }
    }

    template<class K, class V, class Tree>
    V TreeMap<K, V, Tree>::get(const K & key) const
    {
        Pair<K, V> put_pair(key, V());
        Pair<K, V> * get_pair = m_tree.get_self(put_pair);
        if (get_pair)
        {
            return get_pair->value;
        }
        else
        {
            throw Set_ElementNotExists();
        }
    }

    template<class K, class V, class Tree>
    V & TreeMap<K, V, Tree>::operator[](const K & key)
    {
        Pair<K, V> put_pair(key, V());
        if(!m_tree.find(put_pair))
        {
            m_tree.insert(put_pair);
        }
        return m_tree.get_self(put_pair)->value;
    }

    template<class K, class V, class Tree>
    Boolean TreeMap<K, V, Tree>::contains_key(const K & key) const
    {
        return m_tree.find(Pair<K, V> (key, V()));
    }

    template<class K, class V, class Tree>
    Boolean TreeMap<K, V, Tree>::contains_value(const V & value) const
    {
        for(typename TreeMap<K, V, Tree>::Pointer it = begin(); it != end(); ++it)
        {
            if(it->value == value)
                return Boolean::True;
        }
        return Boolean::False;
    }

    template<class K, class V, class Tree>
    void TreeMap<K, V, Tree>::erase(const K & key)
    {
        m_tree.erase(Pair<K, V> (key, V()));
    }
}
#endif /* TREEMAP__CPP */
