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

#include "RedCoreNamespace.h"
#include "RedVSIContextThread.h"
#include "RedVSIContextRoutine.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Routine Stack
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine* RedVSIContextThread::TopRoutineOnStack(void)
{
    if (cRoutineStack.IsEmpty())
        return NULL;
    else
        return cRoutineStack.NextPopItem();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::PushRoutineOnStack(RedVSIContextRoutine* newRtn)
{
    cRoutineStack.Push(newRtn);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine* RedVSIContextThread::PopRoutineOffStack(void)
{
    return cRoutineStack.Pop();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Top level routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::Execute(const unsigned NumCmd)
{
    unsigned decementingCmdCount = NumCmd;

    RedVSIContextRoutine* pTopRoutineContext = TopRoutineOnStack();

    while (pTopRoutineContext != NULL)
    {
        pTopRoutineContext->Execute(decementingCmdCount);

        // Refresh the top routine on the stack and see if its execution is complete
        pTopRoutineContext = TopRoutineOnStack();
        if (pTopRoutineContext != NULL)
        {
            // Its execution is complete
            if (pTopRoutineContext->IsContextExecutionComplete(pTopRoutineContext))
            {
                // copy the return value to the calling routine
                RedDataVariant retval = pTopRoutineContext->ValueToReturn();

                // remove the record from the routine stack
                PopRoutineOffStack();

                pTopRoutineContext = TopRoutineOnStack();

                // If there is a further routine on the stack, write to it (won't be for the last routine.
                if (pTopRoutineContext != NULL)
                    pTopRoutineContext->SetReturnedValue(retval);
            }
        }

        pTopRoutineContext = TopRoutineOnStack();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

