#include <iostream>
#include "HashMap.h"
#include "String.h"

namespace Action
{
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
	Boolean HashMap<K, V>::containsKey(K key)
	{
		return m_set.contains(Pair(key, V()));
	}

	template<class K, class V>
	Boolean HashMap<K, V>::containsValue(V value)
	{
		for (int i = 0; i < m_set.m_iCapacity; ++i)
		{
			for (LinkedList<Pair<T, V> >::Pointer it = m_set.m_links[i].begin();
				it != m_set.m_links[i].end();
				++it)
			{
				if (it->value == value)
					return Boolean::True;
			}
		}
		return Boolean::False;
	}

	template<class K, class V>
	void HashMap<K, V>::erase(K key)
	{
		m_set.erase(Pair(key, V()));
	}
}