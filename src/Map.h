#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"
#include "String.h"
#include "ArrayList.hpp"
#include "Pair.h"

#ifndef Action__Map
#define Action__Map
namespace Action
{
    template <class K, class V>
    class Map : public Object
    {
    public:
        virtual void insert(const K &, const V &) = 0;
        virtual V get(const K &) const = 0;
        virtual void erase(const K &) = 0;
        virtual V & operator [](const K &) = 0;
        virtual Boolean contains_key(const K &) const = 0;
        virtual Boolean contains_value(const V &) const = 0;
        virtual void clear() = 0;
        virtual Integer size() const = 0;
        virtual Boolean empty() const = 0;
        virtual ArrayList<Pair<K, V> > to_array() const = 0;
        
        virtual String get_name() const override = 0;
        virtual String to_string() const override = 0;
    };
}
#endif