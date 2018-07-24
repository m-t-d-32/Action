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
		void autoIncrease();
	public:
        const static Integer EVERY_INCREASE;
        const static Integer BEGIN_SPACE;

		Allocator();
		virtual void setCapacity(const Integer &);
		virtual inline Integer getCapacity() const {return m_iCapacity;}
		virtual void construct(const Integer &,const T &);
		virtual void destruct(const Integer &);
		virtual T * getSpace();
		virtual String getName() const;
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
