#include <iostream>
#include "Exception.h"

#ifndef Action__Alloc_OutOfMemory
#define Action__Alloc_OutOfMemory
namespace Action
{
    class Alloc_OutOfMemory: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Alloc_OutOfMemory */
