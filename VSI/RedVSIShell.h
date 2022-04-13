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
#include "RedVSINamespace.h"

using namespace Red::Core;
using namespace Red::VSI;

namespace Red {
namespace VSI {

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

    // Shell
        // Run command line
        // Query BaseEnv
    // VSI Base Environment
        // Heap
        // Code Lib
        // Log
        // Threadlist (reduced to a list-object of routine calls?, MAPID with unique number/string)
        // Execute (iterate across threads, calls executes())
        // Create thread with routine
        // Create thread with fragment
    // Routine
        // Stack
        // Parse tree
        // BaseEnv pointer
        // Threadlist ptr
        // Execute (jump through commands and parse trees, queue up calls and return, return on command count limit).

    // Futures
        // Save/load whole machine state?
        // Save command line history
        // Break into execute() https://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c

    RedDataString ProcessCmdLine(RedDataString inputstr);

    TEContextState RunState(void) { return cVSIBase.eState; };

private:

    RedVSIContextBase cVSIBase;

    bool LibAddComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
    bool LibInitComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
    bool LibListComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);

    bool DataAddComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
    bool DataInitComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
    bool DataListComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);

    bool RunFragComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
    bool RunFuncComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);

    bool ExitComp(RedTokenBuffer& cInputBuffer, RedLog& cLog);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
