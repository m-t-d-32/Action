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
	//内存分配器，用于申请内存和调用构造，析构函数
	template <class T>
	class Allocator : public Object
	{
	private:
		void Auto_Increase();
	public:
        const static Integer EVERY_INCREASE;	//每次扩容的倍数
        const static Integer BEGIN_SPACE;	//初始空间大小

		//构造函数
		Allocator();

		//设置下次需要的空间（下次申请的空间是参数的两倍，用于提高性能)
		void SetCapacity(const Integer &);

		//获得下次需要申请的空间
		inline Integer GetCapacity() const {return m_iCapacity;}
		
		//在以第一个参数为数组下标的空间上调用拷贝构造函数，拷贝第二个参数
		void Construct(const Integer &,const T &);

		//在以参数为数组下标的空间上调用析构函数
		void Destruct(const Integer &);

		//获得数组指针
		T * GetSpace();

		//获得关于这个类的信息
		String getName() const;

		//析构函数，直接释放数组空间
		~Allocator();
	private:
		T * m_tSpace;
		int m_iCapacity;
		int m_iNextCapacity;
	};
}
#endif /* Action__Allocator */
