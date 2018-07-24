#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"

namespace Action
{
    String Object::getName() const
    {
        return "Action::Object";
    }
    String Object::toString() const
    {
        return getName();
    }
	Integer Object::getVersion() const
	{
        return __MY__VERSION__98;
    }
    void Object::print(std::ostream & os) const
    {
        toString().print(os);
    }
    void Object::println(std::ostream & os) const
    {
        (toString()+"\n").print(os);
    }
    Boolean Object::compareTo(const Object & os) const
    {
        return Boolean::False;
    }
    int Object::hashCode() const
    {
		return ::_hashCode((int)this);
    }
	Boolean Object::operator ==(const Object & arg) const
	{
		return Boolean(this==(&arg));
	}
	Boolean Object::operator !=(const Object & arg) const
	{
		return NOT operator ==(arg);
	}
    Object::~Object()
    {
    }
}
