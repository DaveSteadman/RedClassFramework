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

namespace Red {
namespace Geometry {

using namespace Red::Core;

class RedVector3D;

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

private:
    RedNumber x;
    RedNumber y;
    RedNumber z;
};

} // Geometry
} // Red


