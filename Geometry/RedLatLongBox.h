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


