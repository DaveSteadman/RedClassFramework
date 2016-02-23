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

#include "math.h"

using namespace Red::Core;

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


