

#include "RedTestIO.h"

namespace Red {
namespace Test {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestIO::RunUnitTest(void)
{
    int InputPassed        = RedTestIO::TestInputBuffer();
    int OutputPassed       = RedTestIO::TestOutputBuffer();

    int OverallPassed = 0;

    if ((InputPassed  == 1) &&
        (OutputPassed == 1))
    {
        OverallPassed = 1;
    }

    return OverallPassed;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestIO::TestInputBuffer(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestIO::TestOutputBuffer(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




