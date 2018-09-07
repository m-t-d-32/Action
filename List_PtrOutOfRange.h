#include <iostream>
#include "Exception.h"

#ifndef Action__List_PtrOutOfRange
#define Action__List_PtrOutOfRange
namespace Action
{
    class List_PtrOutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__List_PtrOutOfRange */
