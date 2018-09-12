#include <iostream>
#include <typeinfo>
#include "ArrayList.hpp"
#include "Integer.h"
#include "Boolean.h"
#include "Object.h"
#include "String.h"
#include "Type_NotCorrespond.h"
#include "Heap_PopOutOfRange.h"
#include "DefaultCompare.h"

/*
	愿你走出半生
	归来仍是少年
*/

#ifndef Action__Heap
#define Action__Heap
namespace Action
{
    template <class T, class Compare = DefaultCompare<T> >
    class Heap: public Object
    {
        public:
            Heap();
            Heap (const Heap &);
            Heap (const ArrayList<T> &);
            Heap & operator = (const Heap &);

            virtual Integer size() const
            {
                return m_data.size();
            }
            virtual T front() const;
            virtual Boolean empty() const
            {
                return Boolean (m_data.size() <= 0);
            }
            virtual void insert (const T &);
            virtual void clear();
            virtual T pop();
            virtual Boolean operator == (const Object &) const override;
            virtual String get_name() const override
            {
                return "Action::Heap";
            }
            virtual String to_string() const override
            {
                return m_data.to_string();
            }
            virtual ~Heap();
        private:
            ArrayList<T> m_data;
            Compare compare;
    };
}
#endif	/* Action__Heap */
