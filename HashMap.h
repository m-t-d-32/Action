#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "HashSet.hpp"
#include "LinkedList.h"

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
			Pair() {}
			Pair(K _key, V _value) :key(_key), value(_value) {}
			int hashCode() const override{
				return ((Object &)(key)).hashCode();
			}
			Boolean operator ==(const Object & obj) const override{
				try
				{
					const Pair my_pair=dynamic_cast<const Pair &> (obj);
					return Boolean(key==my_pair.key);
				}
				catch (std::bad_cast){
					throw Type_NotCorrespond();
				}
			}
			String getName() const override {
				return "Action::HashMap::Pair";
			}
			String toString() const override{
				return ((Object &)key).toString()+":"+((Object &)value).toString();
			}
		};

		class PairSet: public HashSet<Pair>
		{
		public:
			Pair & get(const Pair & arg) const{
				Object & my_obj = (Object &)(arg);
				int my_hash = my_obj.hashCode() % this->m_iCapacity;

				for (typename LinkedList<Pair>::Pointer it = this->m_links[my_hash].begin(); 
					it != this->m_links[my_hash].end(); 
					++it)
				{
					if (*it == my_obj)
					{
						return *it;
					}
				}
				throw Set_ElementNotExists();
			}
		};

		struct Pointer
		{
		private:
			typename HashSet<Pair>::Pointer m_ptr;
		public:
			Pointer(typename HashSet<Pair>::Pointer ptr) :m_ptr(ptr) {}
			Pair operator *() { return *m_ptr; }
			Pair * operator ->() { return &(*this); }
			Pointer & operator ++() { ++m_ptr; return *this; }
			Pointer operator ++(int) { return Pointer(m_ptr++); }
			Pointer & operator --() { --m_ptr; return *this; }
			Pointer operator --(int) { return Pointer(m_ptr--); }
			Pointer next() const { return Pointer(m_ptr.next()); }
			Pointer last() const { return Pointer(m_ptr.last()); }
			Boolean operator ==(const Pointer & ptrArgOfAnother) const { return m_ptr == ptrArgOfAnother.m_ptr; }
			Boolean operator !=(const Pointer & ptrArgOfAnother) const { return NOT operator ==(ptrArgOfAnother);}
		};

		friend struct Pointer;
	public:
		void insert(K ,V );
		V get(K ) const;
		V & operator [](K );
		Boolean containsKey(K );
		Boolean containsValue(V );
		void erase(K );
		void clear(){m_set.clear();}
		Integer size(){return m_set.size();}
		Boolean empty(){return m_set.empty();}
		ArrayList<Pair> toArray() {return m_set.toArray();}

		Pointer begin() const {	return m_set.begin();}
		Pointer end() const { return m_set.end(); }
		Pointer v_begin() const { return m_set.v_begin(); }
		Pointer v_end() const { return m_set.v_end(); }

		String getName() const override{
			return "Action::HashMap";
		}
		String toString() const override{
			return m_set.toString();
		}
	private:
		PairSet m_set;
	};
}
