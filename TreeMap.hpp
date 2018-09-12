#include <iostream>
#include "TreeMap.h"
#include "String.h"

#ifndef TREEMAP__CPP
#define TREEMAP__CPP
namespace Action
{
    template<class K, class V, class Tree>
    TreeMap<K, V, Tree>::TreeMap(const TreeMap & another)
    {
        m_set = another.m_set;
    }

    template<class K, class V, class Tree>
    TreeMap<K, V, Tree> & TreeMap<K, V, Tree>::operator = (const TreeMap & another)
    {
        if(this == &another)
            return *this;
        m_set = another.m_set;
        return *this;
    }

    template<class K, class V, class Tree>
    void TreeMap<K, V, Tree>::insert(K key, V value)
    {
        Pair<K, V> put_pair(key, value);
        if(m_set.find(put_pair))
        {
            m_set.get(put_pair).value = value;
        }
        else
        {
            m_set.insert(put_pair);
        }
    }

    template<class K, class V, class Tree>
    V TreeMap<K, V, Tree>::get(K key) const
    {
        return m_set.get(Pair<K, V> (key, V())).value;
    }

    template<class K, class V, class Tree>
    V & TreeMap<K, V, Tree>::operator[](K key)
    {
        Pair<K, V>  put_pair(key, V());
        if(!m_set.find(put_pair))
        {
            m_set.insert(put_pair);
        }
        return m_set.get(put_pair).value;
    }

    template<class K, class V, class Tree>
    Boolean TreeMap<K, V, Tree>::contains_key(K key)
    {
        return Boolean(m_set.find(Pair<K, V> (key, V())) != NULL);
    }

    template<class K, class V, class Tree>
    Boolean TreeMap<K, V, Tree>::contains_value(V value)
    {
        for(typename TreeMap<K, V, Tree>::Pointer it = begin(); it != end(); ++it)
        {
            if(it->value == value)
                return Boolean::True;
        }
        return Boolean::False;
    }

    template<class K, class V, class Tree>
    void TreeMap<K, V, Tree>::erase(K key)
    {
        m_set.erase(Pair<K, V> (key, V()));
    }
}
#endif /* TREEMAP__CPP */
