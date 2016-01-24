// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIContextThread.h"
//#include "CDataArray.h"
#include "RedVSIContextFactory.h"

//#include "RedVSIContextRoutineInterface.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextThread::RedVSIContextThread(void)
{
    pUserObj = 0;
    pCodeLib = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inherited
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::Execute(int& iCmdCount)
{
//    while ( (iCmdCount > 0) && (!cRoutineStack.IsEmpty()) )
//    {
//        RedVSIContextRoutine* pTopRoutine = cRoutineStack.NextPopItem();
//        
//        if (pTopRoutine->HasCmdToExecute())
//        {
//            pTopRoutine->Execute(this);
//            iCmdCount--;
//        }
//        else
//        {
//            //copy the data item out of the routine
//            RedVariant cRetVal = pTopRoutine->GetReturnValue();
//            
//            // actually take the top item off the routine stack and delete it
//            pTopRoutine = cRoutineStack.Pop();
//            delete pTopRoutine;
//
//            // if we have a calling routine to jump back to
//            if (!cRoutineStack.IsEmpty())
//            {
//                // get the new top item off the stack
//                cRoutineStack.NextPopItem()->SetSubroutineReturnValue(cRetVal);
//            }
//        }
//    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVSIContextThread::CreateDataItem(RedVSILangElement cLocation, RedVSILangElement cType, RedString cName)
{
    RedType* pNewData = REDNULL;

    // Basic Validation
    if (!cLocation.IsLocation()) throw;
    if (!cType.IsType()) throw;


    if (cLocation.IsLocationStack())
    {
    }
    if (cLocation.IsLocationHeap())
    {
    }
    if (cLocation.IsLocationAttribute())
    {
    }


//    if ( (cLocation.IsUserObj()) && (pUserObj) )
//    {
//        // create the data item
//        //if      (cType.IsAddr())  pNewData = new CDataAddress();
//        if (cType.IsChar())  pNewData = new RedChar();
//        //else if (cType.IsArray()) pNewData = new CDataArray();
//        else if (cType.IsNum())   pNewData = new RedNumber();
//        else if (cType.IsStr())   pNewData = new RedString();
//        //else if (cType.IsObj())   pNewData = new CDataObject(cType.GetObjectClass());
//
//        if (pNewData)
//            pUserObj->Add(cName, pNewData);
//    }
//    else
//    {
//        pNewData = cRoutineStack.NextPopItem()->CreateDataItem(cLocation, cType, cName);
//    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIContextThread::FindDataItem(RedString cName, RedType*& pData)
{
    pData = 0;

    if( cRoutineStack.NextPopItem()->FindDataItem(cName, pData) ) 
        return 1;
    
    // Otherwise, look in the User Object
    if (pUserObj)
        return pUserObj->Find(cName, pData);

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIContextThread::AssignReturnValue(RedVariant& cData)
{
    cRoutineStack.NextPopItem()->SetReturnValue(cData);

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::SetupRoutineCall(RedVSIRoutineCallInterface& cSignature)
{
//    RedType* pThisObj=0;
//
//    // if the call is internal, get the object/class details from the calling routine
//    if (cSignature.IsInternalCall())
//    {
//        cSignature.SetClassName( GetClassName() );
//        cSignature.SetObjectName( GetObjectName() );
//    }
//    
//    // first, try to find the object or error out
//    RedString cObjName = cSignature.GetObjectName();
//    CDataItem* pDataItem=REDNULL;
//    if (!cObjName.IsEmpty())
//    {
//        if(!FindDataItem(cObjName, pDataItem)) { cAnalysis.AddErrorEvent("ERROR: Call on non-object.");  return; }
//
//        // error if the routine call is on a data item which isn't an object
//        if (!pDataItem->GetType().IsObj()) { cAnalysis.AddErrorEvent("ERROR: Call on non-object.");  return; }
//        pThisObj = (CDataObject*)pDataItem;
//        
//        // extract the classname for the signature
//        cSignature.SetClassName(pThisObj->GetClassName());
//    }
//    // Find the routine
//    RedVSILibRoutineInterface* pRoutine = pCodeLib->FindRoutine(cSignature);
//    if (!pRoutine) { cAnalysis.AddErrorEvent("ERROR: Routine not found.");  return; }
//
//    // create the new routine context
//    RedVSIContextRoutine* pNewContext = RedVSIContextFactory::CreateRoutineContext(cSignature, pRoutine, pThisObj);
//
//    // add the routine to the stack for the next call
//    cRoutineStack.Push(pNewContext);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::QueueCommand(RedVSICmdInterface* pCmd)
{
    // only queue up non-zero commands
    if (pCmd)
    {
        // check the code object is a command and than the current routine is valid
        cRoutineStack.NextPopItem()->QueueCommand(pCmd);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::ClearCommandQueue(void)
{
    cRoutineStack.NextPopItem()->ClearCommandQueue();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    // check the code object is a command and than the current routine is valid
    cRoutineStack.NextPopItem()->QueueExpr(pExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::SetExprResult(RedVSIParseTreeInterface* pExpr, RedVariant& RedResult)
{
    cRoutineStack.NextPopItem()->SetExprResult(pExpr, RedResult);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVSIContextThread::GetExprResult(RedVSIParseTreeInterface* pExpr)
{
    return cRoutineStack.NextPopItem()->GetExprResult(pExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIContextThread::IsBlocked(RedVSIContextRoutine* pRoutineContext)
{
    // if the top of the routine stack matched the context, then that context
    // isn't blocked
    if (cRoutineStack.NextPopItem() == pRoutineContext)
        return 0;
        
    // the pointers are different, so the routine IS blocked.
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedVSIContextThread::ClassName(void)
{
    return cRoutineStack.NextPopItem()->ClassName();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedVSIContextThread::ObjectName(void)
{
    return cRoutineStack.NextPopItem()->ObjectName();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

