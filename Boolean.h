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
			set_val(0);
		}
		Boolean(const Boolean & arg):Byte(arg){}
		Boolean & operator =(const Boolean & arg){
		    if (arg.get_val()) *this=True;
		    else *this=False;
		    return *this;
        }
		explicit Boolean(char t){
			if (t) set_val(-1);
			else set_val(0);
		}
		inline friend Boolean operator AND(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.get_val() && b2.get_val());
		}
		inline friend Boolean operator OR(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.get_val() || b2.get_val());
		}
		inline friend Boolean operator XOR(const Boolean & b1,const Boolean & b2){
			return Boolean(b1.get_val() ^ b2.get_val());
		}
		inline friend Boolean operator NOT(const Boolean & b){
			return Boolean(!b.get_val());
		}
		Boolean operator ==(const Object & Arg) const override{
			try
			{
				const Boolean & my_bool=dynamic_cast<const Boolean &>(Arg);
				return Boolean((get_val() && my_bool.get_val()) || (!get_val() && !my_bool.get_val()));
			}
			catch (std::bad_cast){
				throw Type_NotCorrespond();
			}
		}
		inline friend Boolean operator ==(const Boolean & b1,const Boolean & b2){
			return Boolean((b1.get_val() && b2.get_val()) || (!b1.get_val() && !b2.get_val()));
		}
		operator bool() const{
			return get_val()?true:false;
		}
		String get_name() const override;
		String to_string() const override;
	};
}
#endif /* Action__Boolean */
