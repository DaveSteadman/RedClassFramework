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

int RedTestGeometry::RunUnitTest(void)
{
    int CirclePassed    = RedTestGeometry::TestCircle();
    int LinePassed      = RedTestGeometry::TestLine2D();
    int PointPassed     = RedTestGeometry::TestPoint2D();
    int RectPassed      = RedTestGeometry::TestRect();
    int RectSizePassed  = RedTestGeometry::TestRectSize();
    int VectorPassed    = RedTestGeometry::TestVector2D();

    int TwoDimensionsPassed   = 0;

    if ((CirclePassed    == 1) &&
        (LinePassed      == 1) &&
        (PointPassed     == 1) &&
        (RectPassed      == 1) &&
        (RectSizePassed  == 1) &&
        (VectorPassed    == 1))
    {
        TwoDimensionsPassed = 1;
    }

    int SpherePassed      = RedTestGeometry::TestSphere();
    int Line3DPassed      = RedTestGeometry::TestLine3D();
    int LatLongPassed     = RedTestGeometry::TestLatLong();
    int Point3DPassed     = RedTestGeometry::TestPoint3D();
    int Vector3DPassed    = RedTestGeometry::TestVector3D();

    int ThreeDimensionsPassed   = 0;

    if ((SpherePassed      == 1) &&
        (Line3DPassed      == 1) &&
        (LatLongPassed     == 1) &&
        (Point3DPassed     == 1) &&
        (Vector3DPassed    == 1))
    {
        ThreeDimensionsPassed = 1;
    }

    if (!RedTestGeometry::TestAngle())       return 0;
    if (!RedTestGeometry::TestArea())        return 0;
    if (!RedTestGeometry::TestDistance())    return 0;
    if (!RedTestGeometry::TestTemperature()) return 0;
    if (!RedTestGeometry::TestVolume())      return 0;

    return (TwoDimensionsPassed && ThreeDimensionsPassed);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestCircle(void)
{
    RedPoint2D p(1.1, 1.1);
    RedNumber r(1.1);

    RedCircle x(p, r);

    RedNumber circum = x.Cirumference();
    if (!circum.IsEqualToWithinTollerance(6.9115, 0.0001)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestLine2D(void)
{
    // Setup the line as the hyp of a 3,4,5 triangle.
    RedPoint2D p1(1,1);
    RedPoint2D p2(4,5);
    RedLine2D l(p1, p2);

    RedNumber d = l.GetLength();
    if (!d.IsEqualToWithinTollerance(5.0, kFloatCompTollerance)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestPoint2D(void)
{
    RedPoint2D p1(1,1);
    RedPoint2D p2(2,2);

    RedNumber d = p1.DistanceTo(p2);
    if (!d.IsEqualToWithinTollerance(1.4142, 0.001)) return 0;

    p2.Set(1.2, 2.2);
    RedVector2D v = p1.VectorTo(p2);
    if (!v.X().IsEqualToWithinTollerance(0.2, kFloatCompTollerance)) return 0;
    if (!v.Y().IsEqualToWithinTollerance(1.2, kFloatCompTollerance)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestRect(void)
{
    RedRect x(1, 1, 10, 10);

    RedRectSize s = x.Size();
    s.Scale(0.5);

    if (!s.Height().IsEqualToWithinTollerance(4.5, 0.0001)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestRectSize(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestVector2D(void)
{
    RedNumber a = 56.676;
    RedNumber b = 1.234;

    RedVector2D x(1, 2.1);
    RedVector2D y(a, b);

    x.Scale(2);
    if (!x.X().IsEqualToWithinTollerance(2,   kFloatCompTollerance)) return 0;
    if (!x.Y().IsEqualToWithinTollerance(4.2, kFloatCompTollerance)) return 0;

    RedNumber mag = x.Magnitude();
    if (!mag.IsEqualToWithinTollerance(4.6518, 0.0001)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestSphere(void)
{

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestLine3D(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestLatLong(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestPoint3D(void)
{
    {
        RedPoint3D  x(1,2,3);
        RedVector3D y(1.1,2.2,3.3);

        x.Translate(y);

        if (!x.X().IsEqualToWithinTollerance(2.1, 0.0001)) return 0;
        if (!x.Y().IsEqualToWithinTollerance(4.2, 0.0001)) return 0;
        if (!x.Z().IsEqualToWithinTollerance(6.3, 0.0001)) return 0;
    }

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestVector3D(void)
{
    {
        RedVector3D y(1,2,3);
        y.Scale(1.1);
        if (!y.X().IsEqualToWithinTollerance(1.1, 0.0001)) return 0;
        if (!y.Y().IsEqualToWithinTollerance(2.2, 0.0001)) return 0;
        if (!y.Z().IsEqualToWithinTollerance(3.3, 0.0001)) return 0;
    }
    
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma mark - Units
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestAngle(void)
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

int RedTestGeometry::TestArea(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestDistance(void)
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

int RedTestGeometry::TestTemperature(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestGeometry::TestVolume(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




