// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILib.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILib::AddClass(RedVSILibClass* pNewClass)
{
    // add the class
    cClassList.AddLast(pNewClass);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILib::DelClass(RedString& cClassName)
{
    IteratorType cIt(&cClassList);

    cIt.First();
    while (!cIt.IsDone())
    {
        RedVSILibClass* pCurrClass = cIt.CurrentItem();

        if (pCurrClass->ClassName() == cClassName)
            cIt.DeleteCurrentItem();

        cIt.Next();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibClass* RedVSILib::FindClass(RedString cClassName)
{
    IteratorType cIt(&cClassList);

    cIt.First();
    while (!cIt.IsDone())
    {
        RedVSILibClass* pCurrClass = cIt.CurrentItem();

        if (pCurrClass->ClassName() == cClassName)
            return pCurrClass;

        cIt.Next();
    }

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibRoutineInterface* RedVSILib::FindRoutine(RedVSIRoutineCallInterface& cSig)
{
    RedVSILibClass*            pClass   = FindClass(cSig.ClassName());
    RedVSILibRoutineInterface* pRoutine = 0;
    
    // if we found the first class
    if (pClass)
    { 
        // loop until we run out of parent classes or find a routine
        while (!pRoutine)
        {
            // look for the routine
            pRoutine = pClass->FindRoutine(cSig);

            // if we have no routine, look for a parent class
            if (!pRoutine)
            {
                // find the parent class or exit
                if (!pClass->HasParentClass())
                    return 0;
                pClass = FindClass(pClass->ParentClassName());
                if (!pClass) 
                    return 0;
            }
        }
    }
        
    return pRoutine;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


