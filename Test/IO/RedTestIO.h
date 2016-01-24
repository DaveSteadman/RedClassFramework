
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {


    //using namespace Red::Core;

    class RedTestIO
    {
    public:
        static int RunUnitTest(void);

    private:
        static int TestInputBuffer(void);
        static int TestOutputBuffer(void);
    };


}
}