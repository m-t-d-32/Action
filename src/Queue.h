#include <iostream>
#include "Object.h"
#include "Boolean.h"
#include "Allocator.hpp"

/*
    我存在
    是生命绵延不断的精彩
*/

#ifndef Action__Queue
#define Action__Queue
namespace Action
{
    template <class T>
    class Deque;

    template <class T>
    class Queue: public Object
    {
            friend class Deque<T>;
        public:
            Queue();
            Queue(Integer);
            Queue(const Queue &);
            Queue & operator = (const Queue &);
            virtual void push(const T &);
            virtual T pop();
            virtual T front() const;
            virtual T back() const;
            virtual Integer size() const
            {
                return m_size;
            }
            virtual Boolean empty() const
            {
                return Boolean(m_size == 0);
            }
            virtual void clear();
            virtual Boolean operator == (const Object &) const override;
            virtual String get_name() const override;
            virtual String to_string() const override;
            virtual ~Queue();
        private:
            T * m_data;
            Allocator<T> m_alloc;
            int m_begin, m_size;
            void auto_increase();
    };
}
#endif /* Action__Queue */
