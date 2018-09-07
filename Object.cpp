#include <iostream>
#include "Object.h"
#include "String.h"
#include "Integer.h"
#include "Boolean.h"

namespace Action
{
    String Object::get_name() const
    {
        return "Action::Object";
    }
    String Object::to_string() const
    {
        return get_name();
    }
    Integer Object::get_version() const
    {
        return __MY__VERSION__98;
    }
    void Object::print(std::ostream & os) const
    {
        to_string().print(os);
    }
    void Object::println(std::ostream & os) const
    {
        (to_string()+"\n").print(os);
    }
    Boolean Object::compare_to(const Object & os) const
    {
        return Boolean::False;
    }
    int Object::hash_code() const
    {
        return ::_hashCode((INT64)this);
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
