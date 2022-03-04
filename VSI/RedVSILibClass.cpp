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

#include "RedVSILibClass.h"

#include "RedVSILib.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

void RedVSILibClass::AddRoutine(RedVSILibRoutine* pNewRoutine)
{
    cRoutineList.AddLast(pNewRoutine);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibRoutine* RedVSILibClass::FindRoutine(const RedVSIRoutineCallInterface& cSig)
{   
    // get the routine name we're looking for
    RedDataString cFindRoutineName = cSig.FuncName();
    
    RedVSILibRoutine* pCurrRoutine =0;
    
    // look through all of the routines
    RoutineIteratorType cIt(&cRoutineList);
    cIt.First();
    while (!cIt.IsDone())
    {
        pCurrRoutine = cIt.CurrentItem();

        // If we get a match on the routine name
        if (pCurrRoutine->IsMatching(cSig))
            return pCurrRoutine;        

        cIt.Next();
    }

    // failed to find the routine in this class
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibRoutine* RedVSILibClass::FindRoutineByName(const RedDataString& cNewRoutineName)
{
    RedVSILibRoutine* pCurrRoutine = NULL;
    
    // look through all of the routines
    RoutineIteratorType cIt(&cRoutineList);
    cIt.First();
    while (!cIt.IsDone())
    {
        pCurrRoutine = cIt.CurrentItem();

        // If we get a match on the routine name
        if (pCurrRoutine->cName == cNewRoutineName)
            return pCurrRoutine;        

        cIt.Next();
    }

    // failed to find the routine in this class
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

