#include <iostream>
#include "Object.h"

#ifndef Action__DefaultCompare
#define Action__DefaultCompare
namespace Action
{
    template <class T>
    struct DefaultCompare
    {
        int operator()(const T & element1, const T & element2) const
        {
            try
            {
                const Object & temp_object1 = dynamic_cast
                                              <const Object &>(element1);
                const Object & temp_object2 = dynamic_cast
                                              <const Object &>(element2);
                if(temp_object1 == temp_object2)
                    return 0;
                else if(temp_object1.compare_to(temp_object2) == Boolean::True)
                    return -1;
                else
                    return 1;
            }
            catch(std::bad_cast)
            {
                throw Type_NotCorrespond();
            }
        }
    };
}
#endif /* Action__DefaultCompare */
