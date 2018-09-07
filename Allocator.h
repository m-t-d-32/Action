#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include "Integer.h"
#include "Object.h"
#include "Alloc_OutOfMemory.h"

/*
	月亮在白莲花般的云朵里穿行,
	晚风吹来一阵阵欢乐的歌声
*/

#ifndef Action__Allocator
#define Action__Allocator
namespace Action
{
    template <class T>
    class Allocator : public Object
    {
        private:
            void auto_increase();
        public:
            const static Integer EVERY_INCREASE;
            const static Integer BEGIN_SPACE;

            Allocator();
            virtual void set_capacity(const Integer &);
            virtual inline Integer get_capacity() const
            {
                return m_iCapacity;
            }
            virtual void construct(const Integer &,const T &);
            virtual void destruct(const Integer &);
            virtual T * get_space();
            virtual String get_name() const;
            virtual ~Allocator();

#if __cplusplus < 201103L
        private:
            Allocator & operator =(const Allocator &);
            Allocator(const Allocator &);
#else
            void operator =(const Allocator &)=delete;
            Allocator(const Allocator &)=delete;
#endif

        private:
            T * m_tSpace;
            int m_iCapacity;
            int m_iNextCapacity;
    };
}
#endif /* Action__Allocator */
