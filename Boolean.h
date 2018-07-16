#include <iostream>
#include "Byte.h"
#include "Type_NotCorrespond.h"
#ifndef Action__Boolean
#define Action__Boolean 

namespace Action
{
#define AND &&
#define OR ||
#define NOT !
#define XOR ^
	class Boolean:public Byte
	{
	public:
		const static Boolean True;
		const static Boolean False;
		Boolean(){
			setVal(0);
		}
		explicit Boolean(char t){
			if (t) setVal(-1);
			else setVal(0);
		}
		inline friend Boolean operator AND(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.getVal() && b2.getVal());
		}
		friend Boolean operator OR(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.getVal() || b2.getVal());
		}
		friend Boolean operator XOR(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.getVal() ^ b2.getVal());
		} 
		friend Boolean operator NOT(const Boolean & b){
			return Boolean(!b.getVal());
		} 
		Boolean operator ==(const Object & Arg) const override{
			try
			{
				const Boolean & my_bool=dynamic_cast<const Boolean &>(Arg);
				return Boolean((getVal() && my_bool.getVal()) || (!getVal() && !my_bool.getVal()));
			}
			catch (std::bad_cast){
				throw Type_NotCorrespond();
			}
		}
		friend Boolean operator ==(const Boolean & b1,const Boolean & b2){
			return Boolean((b1.getVal() && b2.getVal()) || (!b1.getVal() && !b2.getVal()));
		}
		operator bool() const{
			return getVal()?true:false;
		}
		virtual String getName() const override;
		virtual String toString() const override;
		void print(std::ostream & os=std::cout) const override{
			Byte::print(os);
		}
		~Boolean(){}
	};
}
#endif