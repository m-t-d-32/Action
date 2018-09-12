#include <iostream>
#include "Object.h"

#ifndef Action__Pair
#define Action__Pair
namespace Action
{
    template <class K, class V>
    struct Pair: public Object
    {
            K key;
            V value;
        public:
            Pair() {}
            Pair(K _key, V _value) : key(_key), value(_value) {}
            virtual int hash_code() const override
            {
                return ((Object &)(key)).hash_code();
            }
            virtual Boolean operator == (const Object & another_one) const override
            {
                try
                {
                    const Pair & another_pair = dynamic_cast<const Pair &>(another_one);
                    return Boolean(key == another_pair.key);
                }
                catch(std::bad_cast)
                {
                    throw Type_NotCorrespond();
                }
            }
            virtual Boolean compare_to(const Object & another_one) const override
            {
                try
                {
                    const Pair & another_pair = dynamic_cast<const Pair &>(another_one);
                    return Boolean(key.compare_to(another_pair.key));
                }
                catch(std::bad_cast)
                {
                    throw Type_NotCorrespond();
                }
            }
            virtual String get_name() const override
            {
                return "Action::Pair";
            }
            virtual String to_string() const override
            {
                return ((Object &) key).to_string() + ":" + ((Object &) value).to_string();
            }
    };
}
#endif /* Action__Pair */
