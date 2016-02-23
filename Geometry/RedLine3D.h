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

#include "RedVector3D.h"
#include "RedPoint3D.h"

using namespace Red::Core;

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


