#include <iostream>
#include "Exception.h"

#ifndef Action__Real_OutOfBound
#define Action__Real_OutOfBound
namespace Action
{
    class Real_OutOfBound: public Exception
    {
        public:
            Real_OutOfBound(double fal_value):m_false_value(fal_value) {}
            String get_name() const override;
            String to_string() const override;
            double get_value() const;
        private:
            double m_false_value;
    };
}
#endif  /* Action__Real_OutOfBound */
