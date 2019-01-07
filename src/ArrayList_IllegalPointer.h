#include <iostream>
#include "Exception.h"

#ifndef Action__ArrayList_IllegalPointer
#define Action__ArrayList_IllegalPointer
namespace Action
{
    class ArrayList_IllegalPointer: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__ArrayList_IllegalPointer */
