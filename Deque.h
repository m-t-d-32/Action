#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"
#include "Queue.hpp"

#ifndef Action__Deque
#define Action__Deque
namespace Action
{
    template <class T>
    class Deque: public Object
    {
        public:
            Deque();
            Deque (const Integer &);
            Deque (const Deque &);

            virtual void push_back (const T &);
            virtual void push_front (const T &);
            virtual T pop_back();
            virtual T pop_front();
            virtual T back() const;
            virtual T front() const;
            virtual Integer size() const
            {
                return m_data.m_size;
            }
            virtual Boolean empty() const
            {
                return Boolean (m_data.m_size == 0);
            }
            virtual T & operator [] (const Integer &);
            virtual void clear();
            virtual Boolean operator == (const Object &) const override;
            virtual String get_name() const override
            {
                return "Action::Deque";
            }
            virtual String to_string() const override
            {
                return m_data.to_string();
            }
            virtual ~Deque();
        private:
            Queue<T> m_data;
    };
}
#endif /* Action__Deque */
