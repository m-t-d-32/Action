#include <iostream>
#include "Exception.h"

#ifndef Action__AVLTree_IllegalPointer
#define Action__AVLTree_IllegalPointer
namespace Action
{
    class AVLTree_IllegalPointer: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__AVLTree_IllegalPointer */
