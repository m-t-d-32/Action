#include <iostream>
#include "Exception.h"

#ifndef Action__BTree_IllegalPointer
#define Action__BTree_IllegalPointer
namespace Action
{
    class BTree_IllegalPointer: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__BTree_IllegalPointer */
