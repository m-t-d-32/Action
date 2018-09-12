#include <iostream>
#include "HashMap.h"
#include "String.h"

#ifndef HASHMAP__CPP
#define HASHMAP__CPP
namespace Action
{
    template<class K, class V>
    HashMap<K, V>::HashMap(const HashMap & another)
    {
        m_set = another.m_set;
    }

    template<class K, class V>
    HashMap<K, V> & HashMap<K, V>::operator = (const HashMap & another)
    {
        if(this == &another)
            return *this;
        m_set = another.m_set;
        return *this;
    }

    template<class K, class V>
    void HashMap<K, V>::insert(K key, V value)
    {
        Pair<K, V> put_pair(key, value);
        if(m_set.contains(put_pair))
        {
            m_set.get(put_pair).value = value;
        }
        else
        {
            m_set.insert(put_pair);
        }
    }

    template<class K, class V>
    V HashMap<K, V>::get(K key) const
    {
        return m_set.get(Pair<K, V> (key, V())).value;
    }

    template<class K, class V>
    V & HashMap<K, V>::operator[](K key)
    {
        Pair<K, V>  put_pair(key, V());
        if(!m_set.contains(put_pair))
        {
            m_set.insert(put_pair);
        }
        return m_set.get(put_pair).value;
    }

    template<class K, class V>
    Boolean HashMap<K, V>::contains_key(K key)
    {
        return m_set.contains(Pair<K, V> (key, V()));
    }

    template<class K, class V>
    Boolean HashMap<K, V>::contains_value(V value)
    {
        for(typename HashMap<K, V>::Pointer it = begin(); it != end(); ++it)
        {
            if(it->value == value)
                return Boolean::True;
        }
        return Boolean::False;
    }

    template<class K, class V>
    void HashMap<K, V>::erase(K key)
    {
        m_set.erase(Pair<K, V> (key, V()));
    }
}
#endif /* HASHMAP__CPP */
