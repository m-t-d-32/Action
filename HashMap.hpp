#include <iostream>
#include "HashMap.h"
#include "String.h"

#ifndef HASHMAP__CPP
#define HASHMAP__CPP
namespace Action
{
    template<class K, class V>
    HashMap<K, V>::HashMap(const HashMap & hmapArg)
    {
        m_set=hmapArg.m_set;
    }

    template<class K, class V>
    HashMap<K, V> & HashMap<K, V>::operator =(const HashMap & hmapArg)
    {
		if (this==&hmapArg)
			return *this;
        m_set=hmapArg.m_set;
        return *this;
    }

	template<class K, class V>
	void HashMap<K, V>::insert(K key, V value)
	{
		try
		{
			m_set.get(Pair(key, V())).value = value;
		}
		catch (Set_ElementNotExists e)
		{
			Pair put_pair(key, value);
			m_set.insert(put_pair);
		}
	}

	template<class K, class V>
	V HashMap<K, V>::get(K key) const
	{
		return m_set.get(Pair(key, V())).value;
	}

	template<class K, class V>
	V & HashMap<K, V>::operator[](K key)
	{
		try
		{
			return m_set.get(Pair(key, V())).value;
		}
		catch (Set_ElementNotExists e)
		{
			Pair put_pair(key, V());
			m_set.insert(put_pair);
			return m_set.get(Pair(key, V())).value;
		}
	}

	template<class K, class V>
	Boolean HashMap<K, V>::contains_key(K key)
	{
		return m_set.contains(Pair(key, V()));
	}

	template<class K, class V>
	Boolean HashMap<K, V>::contains_value(V value)
	{
	    for (typename HashMap<K, V>::Pointer it=begin();it!=end();++it)
        {
            if (it->value == value)
                return Boolean::True;
        }
		return Boolean::False;
	}

	template<class K, class V>
	void HashMap<K, V>::erase(K key)
	{
		m_set.erase(Pair(key, V()));
	}
}
#endif
