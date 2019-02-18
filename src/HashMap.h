#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "HashSet.hpp"
#include "LinkedList.h"
#include "Pair.h"
#include "Map.h"

/*
    命运馈赠的礼物
    背后都有明码标价。
*/

#ifndef Action__HashMap
#define Action__HashMap
namespace Action
{
    template <class K, class V>
    class HashMap : public Map<K, V>
    {
        public:
            class PairSet: public HashSet<Pair<K, V> >
            {
                public:
                    virtual Pair<K, V> & get(const Pair<K, V> & another_key) const
                    {
                        Object & temp_object = (Object &)(another_key);
                        int my_hash = temp_object.hash_code() % this->m_link_capacity;
                        for(typename LinkedList<Pair<K, V> >::Pointer it = this->m_links[my_hash].begin();
                                it != this->m_links[my_hash].end();
                                ++it)
                        {
                            if(*it == temp_object)
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
                    typename HashSet<Pair<K, V> >::Pointer m_ptr;
                public:
                    Pointer(const typename HashSet<Pair<K, V> >::Pointer & ptr) : m_ptr(ptr) {}
                    Pair<K, V> operator *()
                    {
                        return *m_ptr;
                    }
                    const Pair<K, V> * operator ->()
                    {
                        return m_ptr.operator->();
                    }
                    Pointer & operator ++()
                    {
                        ++m_ptr;
                        return *this;
                    }
                    Pointer operator ++ (int)
                    {
                        return Pointer(m_ptr++);
                    }
                    Pointer & operator --()
                    {
                        --m_ptr;
                        return *this;
                    }
                    Pointer operator -- (int)
                    {
                        return Pointer(m_ptr--);
                    }
                    Pointer next() const
                    {
                        return Pointer(m_ptr.next());
                    }
                    Pointer last() const
                    {
                        return Pointer(m_ptr.last());
                    }
                    Boolean operator == (const Pointer & another) const
                    {
                        return m_ptr == another.m_ptr;
                    }
                    Boolean operator != (const Pointer & another) const
                    {
                        return NOT operator == (another);
                    }
            };

            friend struct Pointer;
        public:
            HashMap() {}
            HashMap(const HashMap &);
            HashMap & operator = (const HashMap &);
            virtual void insert(const K &, const V &);
            virtual V get(const K &) const;
            virtual void erase(const K &);
            virtual V & operator [](const K &);
            virtual Boolean contains_key(const K &) const;
            virtual Boolean contains_value(const V &) const;
            virtual void clear()
            {
                m_set.clear();
            }
            virtual Integer size() const
            {
                return m_set.size();
            }
            virtual Boolean empty() const
            {
                return m_set.empty();
            }
            virtual ArrayList<Pair<K, V> > to_array() const
            {
                return m_set.to_array();
            }

            virtual Pointer begin() const
            {
                return m_set.begin();
            }
            virtual Pointer end() const
            {
                return m_set.end();
            }
            virtual Pointer v_begin() const
            {
                return m_set.v_begin();
            }
            virtual Pointer v_end() const
            {
                return m_set.v_end();
            }

            virtual String get_name() const override
            {
                return "Action::HashMap";
            }
            virtual String to_string() const override
            {
                return m_set.to_string();
            }
            virtual ~HashMap() {}
        private:
            PairSet m_set;
    };
}

#endif /* Action__HashMap */
