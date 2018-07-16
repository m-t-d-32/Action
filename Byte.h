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
		inline char getVal() const { return m_bValue; }
		inline void setVal(char arg) { m_bValue = arg; }
		Boolean operator ==(const Object & Arg) const override;
		String getName() const override;
		String toString() const override;
		int hashCode() const override{
			return ::_hashCode(m_bValue);
		}
		virtual ~Byte() {};
	};
}
#endif