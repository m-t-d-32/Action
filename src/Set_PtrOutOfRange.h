#include <iostream>
#include "Exception.h"

#ifndef Action__Set_PtrOutOfRange
#define Action__Set_PtrOutOfRange
namespace Action
{
    class Set_PtrOutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Set_PtrOutOfRange */
