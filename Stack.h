#include <iostream>
#include "ArrayList.hpp"
#include "Integer.h"
#include "Type_NotCorrespond.h"
/*
*/

#ifndef Action__Stack
#define Action__Stack
namespace Action
{
	template <class T>
	class Stack:public Object
	{
	private:
		ArrayList<T> m_array;
	public:
		Stack(){}
		Stack(const Stack & stkArgOfCopy):m_array(stkArgOfCopy.m_array){}
		Stack & operator =(const Stack &);

		virtual void push(const T &);
		virtual T pop();
		virtual T top() const ;
		virtual void clear(){m_array.clear();}
		virtual Boolean empty() const {return m_array.empty();}
		virtual Integer size() const {return m_array.size();}
		virtual Boolean operator ==(const Object & oArgOfAno){
			try
			{
				const Stack<T> & stkArgOfAno=dynamic_cast<const Stack<T> &>(oArgOfAno);
				return m_array==stkArgOfAno.m_array;
			}
			catch(std::bad_cast)
			{
				throw Type_NotCorrespond();
			}
		}
		virtual String get_name() const override{
			return "Action::Stack";
		}
		virtual String to_string() const override{
			return m_array.to_string();
		}
		virtual void print(std::ostream & os=std::cout) const override{
			m_array.print(os);
		}
		virtual ~Stack(){}
	};
}
#endif /* Action__Stack */

