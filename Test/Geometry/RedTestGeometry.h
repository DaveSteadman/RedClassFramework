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

#include "RedGeometryNamespace.h"

namespace Red {
namespace Test {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTestGeometry
{
public:
    static void RunUnitTest(RedLog& log);

private:

    // 2D
    static RedResult TestCircle(void);
    static RedResult TestLine2D(void);
    static RedResult TestPoint2D(void);
    static RedResult TestRect(void);
    static RedResult TestRectSize(void);
    static RedResult TestVector2D(void);

    // 3D
    static RedResult TestSphere(void);
    static RedResult TestLine3D(void);
    static RedResult TestLatLong(void);
    static RedResult TestPoint3D(void);
    static RedResult TestVector3D(void);

    // Units
    static RedResult TestAngle(void);
    static RedResult TestArea(void);
    static RedResult TestDistance(void);
    static RedResult TestTemperature(void);
    static RedResult TestVolume(void);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red