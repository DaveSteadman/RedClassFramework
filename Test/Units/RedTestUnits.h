
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {

    class RedTestUnits
    {
    public:
        static int RunUnitTest(void);

    private:
        static int TestAngle(void);
        static int TestArea(void);
        static int TestDistance(void);
        static int TestTemperature(void);
        static int TestVolume(void);
    };

}
}