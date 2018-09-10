#include <iostream>
#include "Exception.h"

#ifndef Action__Deque_IndexOutOfRange
#define Action__Deque_IndexOutOfRange
namespace Action
{
    class Deque_IndexOutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Deque_IndexOutOfRange */
