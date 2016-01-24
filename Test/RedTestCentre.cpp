

#include "RedTestCentre.h"

#include "RedTestCore.h"
#include "RedTestGeometry.h"
#include "RedTestTml.h"
#include "RedTestExp.h"
#include "RedTestVSI.h"

namespace Red {
namespace Test {

int RedTestCentre::RunAllUnitTests(void)
{
    int CorePassed       = RedTestCore::RunUnitTest();
    int TmlPassed        = RedTestTml::RunUnitTest();
    int VSIPassed        = RedTestVSI::RunUnitTest();

    int GeometryPassed   = RedTestGeometry::RunUnitTest();

    int TmlSPPassed      = 1;// RedTestTmlSP::RunUnitTest();

    int OverallPass =
        CorePassed && TmlPassed && VSIPassed &&
        TmlSPPassed && GeometryPassed;

    return OverallPass;
}

}
}