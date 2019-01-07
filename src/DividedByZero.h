#include <iostream>
#include "Exception.h"

#ifndef Action__DividedByZero
#define Action__DividedByZero
namespace Action
{
    class DividedByZero: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__DividedByZero */
