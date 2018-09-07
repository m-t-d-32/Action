#include <iostream>
#include "Object.h"
#ifndef Action__Exception
#define Action__Exception
namespace Action
{
    class Exception: public Object
    {
        public:
            Exception();
            virtual Exception * get_cause() const;
            virtual void init_cause(Exception *);
            virtual String get_name() const override;
            virtual String to_string() const override;
            virtual ~Exception();
        private:
            Exception * m_cause;
    };
}
#endif /* Action__Exception */
