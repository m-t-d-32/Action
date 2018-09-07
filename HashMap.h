#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "HashSet.hpp"
#include "LinkedList.h"

#ifndef Action__HashMap
#define Action__HashMap
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
                    virtual int hash_code() const override
                    {
                        return ((Object &)(key)).hash_code();
                    }
                    virtual Boolean operator ==(const Object & obj) const override
                    {
                        try
                        {
                            const Pair my_pair=dynamic_cast<const Pair &> (obj);
                            return Boolean(key==my_pair.key);
                        }
                        catch (std::bad_cast)
                        {
                            throw Type_NotCorrespond();
                        }
                    }
                    virtual String get_name() const override
                    {
                        return "Action::HashMap::Pair";
                    }
                    virtual String to_string() const override
                    {
                        return ((Object &)key).to_string()+":"+((Object &)value).to_string();
                    }
            };

            class PairSet: public HashSet<Pair>
            {
                public:
                    virtual Pair & get(const Pair & arg) const
                    {
                        Object & my_obj = (Object &)(arg);
                        int my_hash = my_obj.hash_code() % this->m_iCapacity;

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
                    Pair & operator *()
                    {
                        return *m_ptr;
                    }
                    Pair * operator ->()
                    {
                        return &(*m_ptr);
                    }
                    Pointer & operator ++()
                    {
                        ++m_ptr;
                        return *this;
                    }
                    Pointer operator ++(int)
                    {
                        return Pointer(m_ptr++);
                    }
                    Pointer & operator --()
                    {
                        --m_ptr;
                        return *this;
                    }
                    Pointer operator --(int)
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
                    Boolean operator ==(const Pointer & ptrArgOfAnother) const
                    {
                        return m_ptr == ptrArgOfAnother.m_ptr;
                    }
                    Boolean operator !=(const Pointer & ptrArgOfAnother) const
                    {
                        return NOT operator ==(ptrArgOfAnother);
                    }
            };

            friend struct Pointer;
        public:
            HashMap() {}
            HashMap(const HashMap &);
            HashMap & operator =(const HashMap &);
            virtual void insert(K,V );
            virtual V get(K ) const;
            virtual V & operator [](K );
            virtual Boolean contains_key(K );
            virtual Boolean contains_value(V );
            virtual void erase(K );
            virtual void clear()
            {
                m_set.clear();
            }
            virtual Integer size()
            {
                return m_set.size();
            }
            virtual Boolean empty()
            {
                return m_set.empty();
            }
            virtual ArrayList<Pair> to_array()
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
