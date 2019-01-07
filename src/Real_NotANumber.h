#include <iostream>
#include "Exception.h"

#ifndef Action__Real_NotANumber
#define Action__Real_NotANumber
namespace Action
{
    class Real_NotANumber: public Exception
    {
        public:
            Real_NotANumber(double result_value) : m_false_value(result_value) {}
            String get_name() const override;
            String to_string() const override;
            double get_value() const;
        private:
            double m_false_value;
    };
}
#endif  /* Action__Real_NotANumber */
