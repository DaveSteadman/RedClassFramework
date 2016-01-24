// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

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




