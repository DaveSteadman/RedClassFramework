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

#pragma once

#include "RedPoint2D.h"
#include "RedVector2D.h"

namespace Red {
namespace Geometry {

    using namespace Red::Core;

    const RedNumber kPi = 3.1415926;

    class RedCircle
    {
    public:

        RedCircle(void) { Init(); };
        RedCircle(const RedPoint2D& o, const RedNumber& r) : origin(o), radius(r) {};
        RedCircle(const RedCircle& c) : origin(c.origin), radius(c.radius) {};
        
        void Init(void) { origin.Init(); radius=0.0; };

        // Basic accessor operations
        void              Set(const RedCircle& c)                      { origin=c.origin; radius=c.radius; };
        void              Set(const RedPoint2D& o, const RedNumber& r) { origin=o; radius=r; };
        void              SetOrigin(const RedPoint2D& o)               { origin = o; };
        void              SetRadius(const RedNumber& r)                { radius = r; };
        const RedPoint2D  Origin(void) const { return origin; };
        const RedNumber   Radius(void) const { return radius; };

        // Simple math
        const RedNumber   Cirumference(void) const { RedNumber c = radius * 2.0 * kPi; return c; };
        const RedNumber   Area(void) const { RedNumber c = radius * radius * kPi; return c; };
        const RedVector2D VectorFromOriginToPoint(const RedPoint2D& p) const { RedVector2D v = origin.VectorTo(p); return v; };
        const RedNumber   DistanceFromOriginToPoint(const RedPoint2D& p) const { RedNumber n = origin.DistanceTo(p); return n; };
        const int         ContainsPoint(const RedPoint2D& p) const { if (DistanceFromOriginToPoint(p) > Radius()) return 1; return 0; };

        /// \todo Point routine to contribute to drawing
        const RedPoint2D  PointAtAngle(const RedNumber& a);

        void operator =(const RedCircle& c) { Set(c); };

    private:
        RedPoint2D  origin;
        RedNumber radius;
    };

} // Geometry
} // Red

