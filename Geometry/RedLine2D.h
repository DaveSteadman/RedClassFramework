
/*
 * @file: RedLine2D.h
 */

#pragma once

#include "RedCoreNamespace.h"

#include "RedLine2D.h"
#include "RedPoint2D.h"


namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedLine2D
    {
    public:
        RedLine2D(void) { Init(); };
        RedLine2D(const RedLine2D& nl) { Set(nl); };
        RedLine2D(const RedPoint2D& np1, const RedPoint2D& np2) { Set(np1, np2); };
        RedLine2D(const RedNumber& p1x, const RedNumber& p1y, const RedNumber& p2x, const RedNumber& p2y) { Set(p1x, p1y, p2x, p2y); };
        
        void Init(void) { p1.Init(); p2.Init(); };
        void Set(const RedLine2D& nl) { p1=nl.p1; p2=nl.p2; };
        void Set(const RedPoint2D& np1, const RedPoint2D& np2) { p1=np1; p2=np2; };
        void Set(const RedNumber& p1x, const RedNumber& p1y, const RedNumber& p2x, const RedNumber& p2y) { p1.Set(p1x, p1y); p2.Set(p1x, p1y); };

        const RedNumber GetLength(void) const  { return p1.DistanceTo(p2); };

        void operator =(const RedLine2D& nl) { Set(nl); };

    private:
        RedPoint2D p1;
        RedPoint2D p2;
    };

} // Geometry
} // Red


