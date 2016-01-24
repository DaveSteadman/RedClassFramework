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

namespace Red {
namespace Test {


    //using namespace Red::Core;

    class RedTestCore
    {
    public:
        static int RunUnitTest(void);

    private:
        static int TestBoolean(void);
        static int TestChar(void);
        static int TestNumber(void);
        static int TestNumberRange(void);
        static int TestString(void);
        static int TestDataType(void);
        static int TestVariant(void);
        static int TestLinkedList(void);
        static int TestRecord(void);
        static int TestEventLog(void);
        static int TestSmartPtr(void);
        static int TestResult(void);

        // Time
        static int TestDate(void);
        static int TestTime(void);

        // IO
        static int TestInputBuffer(void);
        static int TestOutputBuffer(void);
    };


}
}