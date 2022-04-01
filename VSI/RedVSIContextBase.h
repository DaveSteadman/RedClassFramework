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

#include "RedVSILib.h"
#include "RedVSIContextRoutine.h"

using namespace Red::Core;

// VSI Base Environment
    // Heap
    // Code Lib
    // Log
    // Threadlist (reduced to a list-object of routine calls?, MAPID with unique number/string)
    // Execute (iterate across threads, calls executes())
    // Create thread with routine
    // Create thread with fragment

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIContextRoutine;

typedef RedStackLIFO<RedVSIContextRoutine*>                   RedVSIRoutineContextStack;
typedef RedMapList<RedDataString, RedVSIRoutineContextStack*> RedVSIThreadList;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum class TEContextState {Running, Ended};

class RedVSIContextBase {

public:

    TEContextState eState = TEContextState::Running;

    RedVSILib        cCodeLib;
    RedLog           cLog;
    RedDataRecord    cHeap;
    RedVSIThreadList cThreadList;

private:

};

} // VSI
} // Red
