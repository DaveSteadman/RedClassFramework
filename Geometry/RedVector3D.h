
#pragma once

#include "RedCoreNamespace.h"

#include "math.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    // Note: Class has no dependency on RedPoint3D
    
    class RedVector3D
    {
    public:
        // Constructors
        RedVector3D(void) { Init(); };
        RedVector3D(const RedNumber& nx, const RedNumber& ny, const RedNumber& nz) { Set(nx, ny, nz); };

        // Basic accessors
        void Init(void)                                                         { x=0; y=0; z=0; };
        void Set(const RedVector3D& v)                                          { x=v.x; y=v.y; z=v.z; };
        void Set(const RedNumber& nx, const RedNumber& ny, const RedNumber& nz) { x=nx; y=ny; z=nz; };
        RedNumber X(void) const                                                 { return x; };
        RedNumber Y(void) const                                                 { return y; };
        RedNumber Z(void) const                                                 { return z; };

        RedNumber    Magnitude(void) const            { RedNumber n(x*x + y*y + z*z); double n2=n.DoubleValue(); return sqrt(n2); };
        void         Scale(const RedNumber& factor)   { x*=factor; y*=factor; z*=factor; };
        RedVector3D  DotProduct(const RedVector3D& v) { RedVector3D rv(x+v.x, y+v.y, z+v.z); return rv; };
        //RedVector3D CrossProduct(const RedVector3D& v);

        void operator =(const RedVector3D& v) { Set(v); };
        //operator==
        //operator+
        //operator-

    private:
        RedNumber x;
        RedNumber y;
        RedNumber z;
    };

} // Geometry
} // Red


