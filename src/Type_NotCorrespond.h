#include <iostream>
#include "Exception.h"

#ifndef Action__Type_NotCorrespond
#define Action__Type_NotCorrespond
namespace Action
{
    class Type_NotCorrespond: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__Type_NotCorrespond */
