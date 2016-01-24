
/**
 * @file RedVector2D.h
 */
 
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedVector2D
    {
    public:
        RedVector2D()                                         { Init(); };
        RedVector2D(const RedNumber& nx, const RedNumber& ny) { x=nx; y=ny; };

        void Init(void)                                       { x=0; y=0; };
        void Set(const RedVector2D& newvect)                  { x=newvect.x; y=newvect.y; };
        void Set(const RedNumber& nx, const RedNumber& ny)    { x=nx; y=ny; };

        // Basic assessors
        const RedNumber X(void) const                         { return x; };
        const RedNumber Y(void) const                         { return y; };
        void            SetX(const RedNumber& nx)             { x=nx; };
        void            SetY(const RedNumber& ny)             { y=ny; };

        void            Scale(const RedNumber& f)             { x*=f; y*=f; };
        const RedNumber Magnitude(void) const;

        void operator =(const RedVector2D& newvect)           { Set(newvect); };

    private: 
        RedNumber x;
        RedNumber y; 
    };

} // Geometry
} // Red


