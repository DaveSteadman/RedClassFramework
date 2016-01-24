
#pragma once

#include "RedCoreNamespace.h"

#include "RedVector3D.h"
#include "RedPoint3D.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedLine3D
    {
    public:
          
        // Constructors
        RedLine3D(void)                                              { Init(); };
        RedLine3D(const RedPoint3D& np1, const RedPoint3D& np2)      { Set(np1, np2); };

        // Basic accessors
        void       Init(void)                                        { p1.Init(); p2.Init(); };
        void       Set(const RedPoint3D& np1, const RedPoint3D& np2) { p1=np1; p2=np2; };
        void       SetP1(const RedPoint3D& np1)                      { p1=np1; };
        void       SetP2(const RedPoint3D& np2)                      { p2=np2; };
        RedPoint3D P1(void) const                                    { return p1; };
        RedPoint3D P2(void) const                                    { return p1; };

        // Detailed Accessors
        void       Translate(const RedVector3D& move)                { p1.Translate(move); p2.Translate(move); };
        RedNumber  Length(void) const                                { RedVector3D v = p1.VectorToPoint(p2); return v.Magnitude(); };

    private:
        RedPoint3D p1;
        RedPoint3D p2;
    };

} // Geometry
} // Red


