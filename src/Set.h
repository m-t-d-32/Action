#include <iostream>
#include "Object.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"
#include "String.h"
#include "ArrayList.hpp"

#ifndef Action__Set
#define Action__Set
namespace Action
{
    template <class T>
    class Set: public Object
	{
		public:
			virtual void insert(const T &) = 0;
			virtual void erase(const T &) = 0;
			virtual Boolean contains(const T &) const = 0;
			virtual Integer size() const = 0;
			virtual Boolean empty() const = 0;
			virtual ArrayList<T> to_array() const = 0;
			virtual void clear() = 0;
			virtual String get_name() const override = 0;
			virtual String to_string() const override = 0;
	};
}
#endif