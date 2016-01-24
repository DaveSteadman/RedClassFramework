
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace Test {

    using namespace Red::Core;

    class RedTestVSI
    {
    public:
        static int RunUnitTest(void);

    private:

        static RedResult TestParseTreeVal(void);
        static RedResult TestParseTreeVar(void);
        static RedResult TestParseTreeBinaryOp(void);

        static RedResult TestParseFactory_001(void);
        static RedResult TestParseFactory_002(void);
        static RedResult TestParseFactory_003(void);

        static RedResult TestCmdNew(void);
        static RedResult TestTokeniseCode(void);

        static RedResult TestLoadLibrary_001(void);
        static RedResult TestLoadLibrary_002(void);

        static RedResult TestSaveLibrary_001(void);

        static RedResult TestRunProg_001(void);

    };
}
}