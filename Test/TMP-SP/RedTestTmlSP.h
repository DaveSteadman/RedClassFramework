
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {

    using namespace Red::Core;

    class RedTestTmlSP
    {
    public:
        static int RunUnitTest(void);

    private:
        static int TestOne(void);
    };

} // Test
} // Red

