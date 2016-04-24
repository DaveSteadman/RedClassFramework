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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//#include "RedCoreNamespace.h"

#include "RedVSIContextRoutine.h"
//#include "RedVSIContextThread.h"
#include "RedVSILibRoutineInterface.h"
#include "RedVSIContextFragment.h"
#include "RedVSILibInterface.h"

#include "RedVSILib.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//using namespace Red::Core;

//class RedVSIContextRoutine;

/// Factory and top-level library class controlling the creation of any context object.
class RedVSIContextFactory
{
public:

    RedResult CreateContextForFragment(const RedString& InputCodeFragment, RedVSIContextFragment** OutputContext, RedLog& cLog);

//    RedResult CreateRoutineContextForRoutine(
//        const RedString&       InputClassName,
//        const RedString&       InputRoutineName,
//        RedVSILibInterface*    pInputLib,
//        RedVSIContextRoutine** OutputContext,
//        RedLog&                cLog);
//
//    RedResult CreateThreadContextForRoutine(
//        RedVSIRoutineCallInterface&  cInputRoutineCall,
//        RedVSILibInterface*          pInputLib,
//        RedVSIContextThread**        OutputContext,
//        RedLog&                      cLog);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

