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

#include "RedVSIContextThread.h"
//#include "CDataArray.h"
#include "RedVSIContextFactory.h"

//#include "RedVSIContextRoutineInterface.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextThread::RedVSIContextThread(const RedVSILibInterface* pInitCodeLib, const RedVSIRoutineCallInterface& cStartingSignature)
{
    pCodeLib = pInitCodeLib;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextThread::RedVSIContextThread(void)
{
    pCodeLib = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inherited
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVSIContextThread::CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName)
{
    RedType* pNewData = REDNULL;

    // Basic Validation
    if (!cLocation.IsLocation()) throw;
    if (!cType.IsType()) throw;

    if (cLocation.IsLocationStack())
    {
        RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

        if (pCurrRoutine)
        {
            pNewData = pCurrRoutine->CreateDataItem(cLocation, cType, cName);
        }
    }
    else if (cLocation.IsLocationHeap())
    {
        RedDataType DataType;
        if (cType.IsTypeBool())   DataType = kDataTypeBool;
        if (cType.IsTypeChar())   DataType = kDataTypeChar;
        if (cType.IsTypeNumber()) DataType = kDataTypeNum;
        if (cType.IsTypeString()) DataType = kDataTypeStr;

        pNewData = cHeap.CreateAndAdd(cName, DataType);
    }
    else
    {
        throw;
    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextThread::FindDataItem(const RedString& cName, RedType*& pData)
{
    // Initialise output pointer
    pData = REDNULL;

    // If we have a routine and find it.
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();
    if (pCurrRoutine)
    {
        if ( pCurrRoutine->FindDataItem(cName, pData) )
            return true;
    }

    // Look in the thread heap
    if (cHeap.Find(cName, pData))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::SetReturnValue(const RedVariant& cData)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    if (pCurrRoutine)
        pCurrRoutine->SetReturnValue(cData);
    else
        cAnalysis.AddErrorEvent("AssignReturnValue with no routine context");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    if (pCurrRoutine)
        pCurrRoutine->QueueExpr(pExpr);
    else
        cAnalysis.AddErrorEvent("QueueExpr with no routine context");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& RedResult)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    if (pCurrRoutine)
        pCurrRoutine->SetExprResult(pExpr, RedResult);
    else
        cAnalysis.AddErrorEvent("SetExprResult with no routine context");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVSIContextThread::ExprResult(RedVSIParseTreeInterface* pExpr)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();
    RedVariant            retval;

    if (pCurrRoutine)
        retval = pCurrRoutine->ExprResult(pExpr);

    return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::ExecuteExprQueue(void)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    if (pCurrRoutine)
        pCurrRoutine->ExecuteExprQueue();
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
//        if (!FindDataItem(cObjName, pDataItem)) { cAnalysis.AddErrorEvent("ERROR: Call on non-object.");  return; }
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

bool RedVSIContextThread::IsBlocked(const RedVSIContextInterface* pRoutineContext)
{
    // if the top of the routine stack matched the context, then that context
    // isn't blocked
    if (cRoutineStack.NextPopItem() == pRoutineContext)
        return false;
        
    // the pointers are different, so the routine IS blocked.
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::QueueCommand(RedVSICmdInterface* pCmd)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    // only queue up non-zero commands
    if ((pCmd) && (pCurrRoutine))
    {
        pCurrRoutine->QueueCommand(pCmd);
    }
    else
    {
        if (!pCmd)         cAnalysis.AddErrorEvent("QueueCommand with no command");
        if (!pCurrRoutine) cAnalysis.AddErrorEvent("QueueCommand with no routine context");
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::ClearCommandQueue(void)
{
    RedVSIContextRoutine* pCurrRoutine = cRoutineStack.NextPopItem();

    if (pCurrRoutine)
        pCurrRoutine->ClearCommandQueue();
    else
        cAnalysis.AddErrorEvent("ClearCommandQueue with no routine context");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedString RedVSIContextThread::ClassName(void)
//{
//    return cRoutineStack.NextPopItem()->ClassName();
//}
//
//// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//RedString RedVSIContextThread::ObjectName(void)
//{
//    return cRoutineStack.NextPopItem()->ObjectName();
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextThread::Execute(const unsigned CmdCount)
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

} // VSI
} // Red

