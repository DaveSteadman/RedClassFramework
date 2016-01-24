
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {

    using namespace Red::Core;

    class RedTestExp
    {
    public:
        static int RunUnitTest(void);

    private:
        static int TestOne(void);
        static int TestTwo(void);
    };

} // Test
} // Red

