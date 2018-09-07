#include <iostream>
#include "Object.h"
#include "Boolean.h"
#include "Allocator.hpp"

#ifndef Action__Queue
#define Action__Queue
namespace Action
{
    template <class T>
    class Queue: public Object
    {
        public:
            Queue();
            Queue(const Integer &);
            Queue(const Queue &);
            Queue & operator =(const Queue &);

            virtual void push(const T &);
            virtual T pop();
            virtual T front() const;
            virtual T back() const;
            virtual Integer size() const
            {
                return m_iSize;
            }
            virtual Boolean empty() const
            {
                return Boolean(m_iSize==0);
            }
            virtual void clear();

            virtual Boolean operator ==(const Object &) const override;
            virtual String get_name() const override;
            virtual String to_string() const override;

            virtual ~Queue();
        private:
            T * m_data;
            Allocator<T> m_alloc;
            int m_iBegin,m_iSize;
    };
}
#endif /* Action__Queue */
