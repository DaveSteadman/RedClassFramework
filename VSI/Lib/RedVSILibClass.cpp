// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILibClass.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

void RedVSILibClass::AddRoutine(RedVSILibRoutine* pNewRoutine)
{
    cRoutineList.AddLast(pNewRoutine);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibRoutine* RedVSILibClass::FindRoutine(RedVSIRoutineCallInterface& cSig)
{   
    // get the routine name we're looking for
    RedString cFindRoutineName = cSig.FuncName();
    
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
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

