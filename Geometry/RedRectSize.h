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

class RedRectSize
{
public:
    RedRectSize() { Init(); };

    void Init(void)                                  { width=0; height=0; };
    void Set(const RedRectSize& newsize)             { width=newsize.width; height=newsize.height; };
    void Set(const RedNumber& w, const RedNumber& h) { width=w; height=h; };

    void Adjust(const RedNumber& dx, const RedNumber& dy) { width+=dx; height+=dy; };

    void Scale(const RedNumber& f)     { width*=f; height*=f; };

    const RedNumber Width(void)  const { return width;  };
    const RedNumber Height(void) const { return height; };

    void operator =(const RedRectSize& newsize) { Set(newsize); };
    
private: 
    RedNumber width;
    RedNumber height;
};

} // Geometry
} // Red


