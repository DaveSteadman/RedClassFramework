
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {

using namespace Red::Core;

    class RedTestTml
    {
    public:
        static int RunUnitTest(void);

    private:

        static RedResult TestOne(void);
        static RedResult TestTwo(void);
        static RedResult TestIterators(void);
        static RedResult TestTreeEdit(void);

//        static int TestBasicVSILibrary_001(void);
//        static int TestReadBasicVSILibrary_001(void);

    };

} // Test
} // Red

