
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