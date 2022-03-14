// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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
#include "RedVSINamespace.h"

using namespace Red::Core;
using namespace Red::VSI;

namespace Red {
namespace VSI {

enum class TEShellState { Unknown, Running, Waiting, Ended };

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIShell
{
public:

    // Shell Commands:
    // - load/list/clear classes&routines.
    // - List data values heap etc
    // - Show/clear log
    // VSI Commands:
    // - execute routines
    // - execute fragments

    RedDataString ProcessCmdLine(RedDataString inputstr);

    TEShellState eState = TEShellState::Waiting;

    RedVSILib eCodeLib;

    // Data attributes
    RedDataRecord cHeap;

private:

    bool LibAddComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
    bool LibInitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
    bool LibListComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);

    bool DataAddComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
    bool DataInitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
    bool DataListComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);

    bool RunFragComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
    bool RunFuncComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);

    bool ExitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
