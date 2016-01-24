
#pragma once

#include "RedVector2D.h"
#include "RedCoreNamespace.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedPoint2D
    {
    public:
    
        RedPoint2D(void)                                          { Init(); };
        RedPoint2D(const RedNumber& nx, const RedNumber& ny)      { Set(nx, ny); };
        RedPoint2D(const RedPoint2D& np)                          { Set(np); };

        void      Init(void)                                    { x=0; y=0; };
        void      Set(const RedPoint2D& np)                     { x=np.x; y=np.y; };
        void      Set(const RedNumber& nx, const RedNumber& ny) { x=nx; y=ny; };

        const RedNumber X(void) const { return x; };
        const RedNumber Y(void) const { return y; };

        const RedVector2D VectorTo(const RedPoint2D& newpos) const;
        const RedNumber DistanceTo(const RedPoint2D& newpos) const;

        void RelativeMove(const RedNumber& dx, const RedNumber& dy) { x+=dx; y+=dy; };


        void operator =(const RedPoint2D& newpos) { Set(newpos); };

    private:
        RedNumber x;
        RedNumber y;
    };

} // Geometry
} // Red


