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

#include "RedCoreNamespace.h"
#include "RedGeometryNamespace.h"

#include "RedTestGeometry.h"

namespace Red {
namespace Test {

using namespace Red::Core;
using namespace Red::Geometry;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTestGeometry::RunUnitTest(RedLog& log)
{
    // 2D
    if (RedTestGeometry::TestCircle().IsFail())      { log.AddErrorEvent("Geometry Unit Test: TestCircle Failed");      return; }
    if (RedTestGeometry::TestLine2D().IsFail())      { log.AddErrorEvent("Geometry Unit Test: TestLine2D Failed");      return; }
    if (RedTestGeometry::TestPoint2D().IsFail())     { log.AddErrorEvent("Geometry Unit Test: TestPoint2D Failed");     return; }
    if (RedTestGeometry::TestRect().IsFail())        { log.AddErrorEvent("Geometry Unit Test: TestRect Failed");        return; }
    if (RedTestGeometry::TestRectSize().IsFail())    { log.AddErrorEvent("Geometry Unit Test: TestRectSize Failed");    return; }
    if (RedTestGeometry::TestVector2D().IsFail())    { log.AddErrorEvent("Geometry Unit Test: TestVector2D Failed");    return; }

    // 3D
    if (RedTestGeometry::TestSphere().IsFail())      { log.AddErrorEvent("Geometry Unit Test: TestSphere Failed");      return; }
    if (RedTestGeometry::TestLine3D().IsFail())      { log.AddErrorEvent("Geometry Unit Test: TestLine3D Failed");      return; }
    if (RedTestGeometry::TestLatLong().IsFail())     { log.AddErrorEvent("Geometry Unit Test: TestLatLong Failed");     return; }
    if (RedTestGeometry::TestPoint3D().IsFail())     { log.AddErrorEvent("Geometry Unit Test: TestPoint3D Failed");     return; }
    if (RedTestGeometry::TestVector3D().IsFail())    { log.AddErrorEvent("Geometry Unit Test: TestVector3D Failed");    return; }

    // Units
    if (RedTestGeometry::TestAngle().IsFail())       { log.AddErrorEvent("Geometry Unit Test: TestAngle Failed");       return; }
    if (RedTestGeometry::TestArea().IsFail())        { log.AddErrorEvent("Geometry Unit Test: TestArea Failed");        return; }
    if (RedTestGeometry::TestDistance().IsFail())    { log.AddErrorEvent("Geometry Unit Test: TestDistance Failed");    return; }
    if (RedTestGeometry::TestTemperature().IsFail()) { log.AddErrorEvent("Geometry Unit Test: TestTemperature Failed"); return; }
    if (RedTestGeometry::TestVolume().IsFail())      { log.AddErrorEvent("Geometry Unit Test: TestVolume Failed");      return; }

    log.AddText("Geometry Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestCircle(void)
{
    RedPoint2D p(1.1, 1.1);
    RedNumber r(1.1);

    RedCircle x(p, r);

    RedNumber circum = x.Cirumference();
    if (!circum.IsEqualToWithinTollerance(6.9115, 0.0001)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestLine2D(void)
{
    // Setup the line as the hyp of a 3,4,5 triangle.
    RedPoint2D p1(1,1);
    RedPoint2D p2(4,5);
    RedLine2D l(p1, p2);

    RedNumber d = l.GetLength();
    if (!d.IsEqualToWithinTollerance(5.0, kFloatCompTollerance)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestPoint2D(void)
{
    //RedPoint2D p1(1,1);
    //RedPoint2D p2(2,2);

    //RedNumber d = p1.DistanceTo(p2);
    //if (!d.IsEqualToWithinTollerance(1.4142, 0.001)) return kResultFail;

    //p2.Set(1.2, 2.2);
    //RedVector2D v = p1.VectorTo(p2);
    //if (!v.X().IsEqualToWithinTollerance(0.2, kFloatCompTollerance)) return kResultFail;
    //if (!v.Y().IsEqualToWithinTollerance(1.2, kFloatCompTollerance)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestRect(void)
{
    RedRect x(1, 1, 10, 10);

    RedRectSize s = x.Size();
    s.Scale(0.5);

    if (!s.Height().IsEqualToWithinTollerance(4.5, 0.0001)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestRectSize(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestVector2D(void)
{
    //RedNumber a = 56.676;
    //RedNumber b = 1.234;

    //RedVector2D x(1, 2.1);
    //RedVector2D y(a, b);

    //x.Scale(2);
    //if (!x.X().IsEqualToWithinTollerance(2,   kFloatCompTollerance)) return kResultFail;
    //if (!x.Y().IsEqualToWithinTollerance(4.2, kFloatCompTollerance)) return kResultFail;

    //RedNumber mag = x.Magnitude();
    //if (!mag.IsEqualToWithinTollerance(4.6518, 0.0001)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestSphere(void)
{

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestLine3D(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestLatLong(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestPoint3D(void)
{
    {
        RedPoint3D  x(1,2,3);
        RedVector3D y(1.1,2.2,3.3);

        x.Translate(y);

        if (!x.X().IsEqualToWithinTollerance(2.1, 0.0001)) return kResultFail;
        if (!x.Y().IsEqualToWithinTollerance(4.2, 0.0001)) return kResultFail;
        if (!x.Z().IsEqualToWithinTollerance(6.3, 0.0001)) return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestVector3D(void)
{
    {
        RedVector3D y(1,2,3);
        y.Scale(1.1);
        if (!y.X().IsEqualToWithinTollerance(1.1, 0.0001)) return kResultFail;
        if (!y.Y().IsEqualToWithinTollerance(2.2, 0.0001)) return kResultFail;
        if (!y.Z().IsEqualToWithinTollerance(3.3, 0.0001)) return kResultFail;
    }
    
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Units
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestAngle(void)
{
    {
        RedAngle x;
        x.SetDegrees(360);
        RedNumber y = x.Radians();
        if (!y.IsEqualToWithinTollerance(two_pi, 0.00001))
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestArea(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestDistance(void)
{
    {
        RedDistance x;
        x.SetInches(1.0);
        RedNumber y = x.Centimetres();
        if (!y.IsEqualToWithinTollerance(2.54, 0.001))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestTemperature(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestGeometry::TestVolume(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




