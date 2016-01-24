
#pragma once

#include "RedCoreNamespace.h"

#include "RedVector3D.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedPoint3D
    {
    public:
          
        // Constructors
        RedPoint3D(void) { Init(); };
        RedPoint3D(const RedNumber& nx, const RedNumber& ny, const RedNumber& nz)    { Set(nx, ny, nz); };

        // Basic accessors
        void      Init(void)                                                         { x=0; y=0; z=0; };
        void      Set(const RedPoint3D& p)                                           { x=p.x; y=p.y; z=p.z; };
        void      Set(const RedNumber& nx, const RedNumber& ny, const RedNumber& nz) { x=nx; y=ny; z=nz; };
        RedNumber X(void) const                                                      { return x; };
        RedNumber Y(void) const                                                      { return y; };
        RedNumber Z(void) const                                                      { return z; };

        void        Translate(const RedVector3D& move)                               { x+=move.X(); y+=move.Y(); z+=move.Z(); };
        RedVector3D VectorToPoint(const RedPoint3D& p) const                         { RedVector3D rv(p.x-x, p.y-y, p.z-z); return rv; };

        void operator =(const RedPoint3D& p) { Set(p); };
        //operator==

    private:
        RedNumber x;
        RedNumber y;
        RedNumber z;
    };

} // Geometry
} // Red


