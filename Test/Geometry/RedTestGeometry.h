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

    class RedTestGeometry
    {
    public:
        static int RunUnitTest(void);

    private:
        // 2D
        static int TestCircle(void);
        static int TestLine2D(void);
        static int TestPoint2D(void);
        static int TestRect(void);
        static int TestRectSize(void);
        static int TestVector2D(void);

        // 3D
        static int TestSphere(void);
        static int TestLine3D(void);
        static int TestLatLong(void);
        static int TestPoint3D(void);
        static int TestVector3D(void);

        // Units
        static int TestAngle(void);
        static int TestArea(void);
        static int TestDistance(void);
        static int TestTemperature(void);
        static int TestVolume(void);
    };

}
}