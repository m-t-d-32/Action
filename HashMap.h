#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "HashSet.hpp"

namespace Action
{
	template <class K,class V>
	class HashMap:public Object
	{
	public:
		struct Pair: public Object
		{
			K key;
			V value;
		public:
			int hashCode() const override{
				return ((Object &)(key)).hashCode();
			}
			Boolean operator ==(const Object & obj) const override{
				try{
					my_pair=dynamic_cast<Pair &> (obj);
					return Boolean(key==my_pair.key);
				}
				catch (std::bad_cast){
					throw Type_NotCorrespond();
				}
			}
			String getName(){
				return "Action::HashMap::Pair";
			}
			String toString(){
				return ((Object &)key).toString()+":"+((Object &)value).toString();
			}
		};

		typedef HashSet<Pair<K,V> >::Pointer HashMap<K,V>::Pointer;

	public:
		HashMap();
		void insert(K key,V value);
		V get(K key) const;
		V & operator [](K key);
		Boolean containsKey(K Key);
		Boolean containsValue(V value);
		void erase(K key);
		void clear(){m_set.clear();}
		Integer size(){return m_set.size();}
		Boolean empty(){return m_set.empty();}
		ArrayList toArray() {return m_set.toArray();}

		Pointer begin() const;
		Pointer end() const;
		Pointer v_begin() const;
		Pointer v_end() const;

		String getName() const override{
			return "Action::HashMap";
		}
		String toString() const override{
			return m_set.toString();
		}
		~HashMap();
	private:
		HashSet<Pair<K,V> > m_set;
	};
}
