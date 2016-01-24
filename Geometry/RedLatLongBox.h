
#pragma once

#include "RedCoreNamespace.h"
#include "RedLatLong.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

    class RedLatLongBox
    {
    public:
          
        // Constructors
        RedLatLongBox(void)                                            { Init(); };
        RedLatLongBox(const RedLatLong& tl, const RedLatLong& br)      { SetBox(tl, br); };

        // Basic accessors
        void      Init(void)                                           { topleft.Init(); bottomright.Init(); };
        void      SetBox(const RedLatLong& tl, const RedLatLong& br)   { topleft=tl; bottomright=br; };
        void      Set(const RedLatLongBox& b)                          { topleft=b.topleft; bottomright=b.bottomright; };

        // Compled accessors
        int       IsLatLongInBox(const RedLatLong& p) const;

        void operator =(const RedLatLongBox& p) { Set(p); };
        //operator==

    private:
        RedLatLong topleft;
        RedLatLong bottomright;
    };

} // Geometry
} // Red


