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
        void            Set(const RedCircle& c)                      { origin=c.origin; radius=c.radius; };
        void            Set(const RedPoint2D& o, const RedNumber& r) { origin=o; radius=r; };
        void            SetOrigin(const RedPoint2D& o)               { origin = o; };
        void            SetRadius(const RedNumber& r)                { radius = r; };
        const RedPoint2D  Origin(void) const { return origin; };
        const RedNumber Radius(void) const { return radius; };

        // Simple math
        const RedNumber Cirumference(void) const { RedNumber c = radius * 2.0 * kPi; return c; };
        const RedNumber Area(void) const { RedNumber c = radius * radius * kPi; return c; };
        const RedVector2D VectorFromOriginToPoint(const RedPoint2D& p) const { RedVector2D v = origin.VectorTo(p); return v; };
        const RedNumber DistanceFromOriginToPoint(const RedPoint2D& p) const { RedNumber n = origin.DistanceTo(p); return n; };
        const int       ContainsPoint(const RedPoint2D& p) const { if (DistanceFromOriginToPoint(p) > Radius()) return 1; return 0; };

        /// \todo Point routine to contribute to drawing
        const RedPoint2D PointAtAngle(const RedNumber& a);

        void operator =(const RedCircle& c) { Set(c); };

    private:
        RedPoint2D  origin;
        RedNumber radius;
    };

} // Geometry
} // Red

