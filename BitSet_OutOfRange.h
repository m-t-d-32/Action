#include <iostream>
#include "Exception.h"

#ifndef Action__BitSet_OutOfRange
#define Action__BitSet_OutOfRange
namespace Action
{
    class BitSet_OutOfRange: public Exception
    {
        public:
            String get_name() const override;
            String to_string() const override;
    };
}
#endif  /* Action__BitSet_OutOfRange */
