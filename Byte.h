#include <iostream>
#include "Object.h"

#ifndef Action__Byte
#define Action__Byte
namespace Action
{
	class Boolean;
	class Byte :public Object
	{
	private:
		char m_bValue;
	public:
		Byte() {
			m_bValue = 0;
		}
		Byte(char arg) { m_bValue = arg; }
		Byte(const Byte & arg){ m_bValue = arg.m_bValue; }
		virtual Byte & operator =(const Byte & arg){
		    m_bValue=arg.m_bValue;
		    return *this;
		}
		virtual inline char getVal() const { return m_bValue; }
		virtual inline void setVal(char arg) { m_bValue = arg; }
		virtual Boolean operator ==(const Object & Arg) const override;
		virtual String getName() const override;
		virtual String toString() const override;
		virtual int hashCode() const override{
			return ::_hashCode(m_bValue);
		}
	};
}
#endif /* Action__Byte */
