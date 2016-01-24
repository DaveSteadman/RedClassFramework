

#include "RedTestUnits.h"
#include "RedUnitsNamespace.h"

namespace Red {
namespace Test {

using namespace Red::Core;
using namespace Red::Units;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::RunUnitTest(void)
{
    int AnglePassed        = RedTestUnits::TestAngle();
    int AreaPassed         = RedTestUnits::TestArea();
    int DistancePassed     = RedTestUnits::TestDistance();
    int TemperaturePassed  = RedTestUnits::TestTemperature();
    int VolumePassed       = RedTestUnits::TestVolume();

    int OverallPassed = 0;

    if ((AnglePassed       == 1) &&
        (AreaPassed        == 1) &&
        (DistancePassed    == 1) &&
        (TemperaturePassed == 1) &&
        (VolumePassed      == 1))
    {
        OverallPassed = 1;
    }

    return OverallPassed;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::TestAngle(void)
{
    {
        RedAngle x;
        x.SetDegrees(360);
        RedNumber y = x.Radians();
        if (!y.IsEqualToWithinTollerance(two_pi, 0.00001))
            return 0;
    }
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::TestArea(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::TestDistance(void)
{
    {
        RedDistance x;
        x.SetInches(1.0);
        RedNumber y = x.Centimetres();
        if (!y.IsEqualToWithinTollerance(2.54, 0.001))
            return 0;
    }

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::TestTemperature(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestUnits::TestVolume(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




