// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

#include "RedVSIContextFactory.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedVSIContextRoutine* RedVSIContextFactory::CreateRoutineContext(RedVSILibRoutineInterface& cRoutineCall, RedVSILibRoutineInterface* pRoutineLib, CDataObject* pThisObj)
//{
//    RedVSIContextRoutine* pNewRoutine = new RedVSIContextRoutine();
//
//    // Assign the routine name details to the context
//    pNewRoutine->SetNameDetails(cRoutineCall.GetObjectName(), cRoutineCall.GetClassName(), cRoutineCall.GetFuncName());
//
//    // Setup the core elements of the routine
//    pNewRoutine->SetThisObj(pThisObj);
//    pNewRoutine->QueueCommand(pRoutineLib->GetCode());
//
//    // Loop through the parameters
//    RedVSIDataListIterator cCallParamsIt(cRoutineCall.GetParams());
//    RedVSIStringStringTypeMapIterator cRoutineParamsIt(pRoutineLib->GetParams());
//    cCallParamsIt.First();
//    cRoutineParamsIt.First();
//
//    while ( (!cCallParamsIt.IsDone()) && (!cRoutineParamsIt.IsDone()) )
//    {
//        // get the data out of the lists to create the new data items
//        RedString  cName = cRoutineParamsIt.CurrentId();
//        RedVariant cData = cCallParamsIt.CurrentItem();
//        
//        pNewRoutine->AddParam(cName, cData.GetValue());
//
//        // move the list items on.
//        cCallParamsIt.Next();
//        cRoutineParamsIt.Next();
//    }
//
//    return pNewRoutine;  
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

