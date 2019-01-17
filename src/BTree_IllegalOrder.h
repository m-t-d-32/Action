#include <iostream>
#include "Exception.h"

#ifndef Action__BTree_IllegalOrder
#define Action__BTree_IllegalOrder
namespace Action
{
    class BTree_IllegalOrder: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__BTree_IllegalOrder */
