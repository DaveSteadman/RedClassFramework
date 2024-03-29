// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

using namespace Red::Core;

namespace Red {
namespace Test {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTestVSI
{
public:
    static void RunUnitTest(RedLog& log);

private:

    static RedResult TestParseTreeVal(void);
    static RedResult TestParseTreeVar(void);
    static RedResult TestParseTreeBinaryOp(void);

    static RedResult TestParseFactory_001(void);
    static RedResult TestParseFactory_002(void);
    static RedResult TestParseFactory_003(void);

    static RedResult TestCmdNew(void);
    static RedResult TestTokeniseCode(void);

    static RedResult TestFragment_New(void);
    static RedResult TestFragment_NewTypes(void);
    static RedResult TestFragment_Expr(void);
    static RedResult TestFragment_If(void);
    static RedResult TestFragment_While(void);
    static RedResult TestFragment_Log(void);

//    static RedResult TestLoadLibrary_001(void);
//    static RedResult TestLoadLibrary_002(void);
//    static RedResult TestSaveLibrary_001(void);

    static RedResult TestRunProg_001(void);

    static RedResult TestSignature(void);

};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red