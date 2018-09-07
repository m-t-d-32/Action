#include <iostream>
#include "Exception.h"

#ifndef Action__Heap_PopOutOfRange
#define Action__Heap_PopOutOfRange
namespace Action
{
    class Heap_PopOutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Heap_PopOutOfRange */
