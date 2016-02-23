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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


