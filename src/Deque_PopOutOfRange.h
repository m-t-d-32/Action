#include <iostream>
#include "Exception.h"

#ifndef Action__Deque_PopOutOfRange
#define Action__Deque_PopOutOfRange
namespace Action
{
    class Deque_PopOutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Deque_PopOutOfRange */
