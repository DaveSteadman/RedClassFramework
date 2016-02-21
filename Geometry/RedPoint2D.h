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

#include "RedNumber.h"

using namespace Red::Core;

namespace Red {
namespace Geometry {

class RedVector2D;

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


