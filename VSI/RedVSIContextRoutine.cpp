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

#include "RedVSIContextRoutine.h"
//#include "CDataArray.h"
#include "RedVSILib.h"
#include "RedVSIParseStackTraverser.h"
#include "RedVSICollections.h"
#include "RedVSILibRoutine.h"

#include "RedVSIContextBase.h"

#include "RedCoreNamespace.h"
using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructor / Destructor
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext)
{
    // pThisObj     = 0;

    pBaseContext = pInitBaseContext;

    cReturnValue.Init();
    pCurrCmd     = NULL;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext, RedVSICmd* pFirstCmd)
{
    // pThisObj     = 0;

    pBaseContext = pInitBaseContext;

    cReturnValue.Init();
    pCurrCmd     = pFirstCmd;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext, const RedDataString& inClassName, const RedDataString& inRoutineName, RedVSICmd* pFirstCmd)
{
    pBaseContext = pInitBaseContext;

    ClassName    = inClassName;
    RoutineName  = inRoutineName;
    pCurrCmd     = pFirstCmd;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::~RedVSIContextRoutine(void)
{
    cLocalVariables.DelAll();

    // Does not delete the pLog object, as that is envisaged to be shared amongst several context objects.

    //if (pReturnValue)
    //    delete pReturnValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Setup Calls
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedVSIContextRoutine::SetNameDetails(RedDataString& cNewObjectName, RedDataString& cNewClassName, RedDataString& cNewFuncName)
//{ 
//    cObjectName = cNewObjectName;
//    cClassName  = cNewClassName; 
//    cFuncName   = cNewFuncName; 
//}
//
/// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedVSIContextRoutine::AddParam(RedDataString cName, RedData* pData)
//{
//     cRoutineData.Add(cName, pData->Clone());
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Data
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedVSIContextRoutine::CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedDataString& cName)
{
    RedData* pNewData = NULL;

    // Basic Validation
    if (!cLocation.IsLocation()) throw;
    if (!cType.IsType()) throw;

    RedDataType DataType = RedVSILangElement::DataTypeForLangElemType(cType);

    if (cLocation.IsLocationStack())
    {
        pNewData = cLocalVariables.CreateAddReturn(cName, DataType);
    }
  
    else if (cLocation.IsLocationHeap())
    {
        if (pBaseContext != NULL)
            pNewData = pBaseContext->cHeap.CreateAddReturn(cName, DataType);
    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedVSIContextRoutine::DuplicateDataItem(const RedVSILangElement& cLocation, const RedData* pDataItem, const RedDataString& cName)
{
    RedData* pNewData = pDataItem->Clone();

    // Basic Validation
    if (!cLocation.IsLocation()) throw;

    if (cLocation.IsLocationStack())
    {
        cLocalVariables.CloneAndAdd(cName, pDataItem);
    }
    else if (cLocation.IsLocationHeap())
    {
        if (pBaseContext != NULL)
        {
            pBaseContext->cHeap.CloneAndAdd(cName, pDataItem);
        }
    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::FindDataItem(const RedDataString& cName, RedData*& pData)
{
    // first try and get the data from the local routine
    if (cLocalVariables.FindFieldPtr(cName, pData))
        return true;

    if (pBaseContext != NULL)
    {
        if (pBaseContext->cHeap.FindFieldPtr(cName, pData))
            return true;
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedVSIContextRoutine::DataItemAsVariant(const RedDataString& cName)
{
    RedDataVariant RetVar;

    RedData* pData = NULL;

    bool found = FindDataItem(cName, pData);

    if (found)
    {
        RetVar = pData;
    }

    return RetVar;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILib* RedVSIContextRoutine::FindCodeLib(void)
{
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetValueToReturn(const RedDataVariant& cData)
{
    cReturnValue = cData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetReturnedValue(const RedDataVariant& cData)
{
    // if we don't have an expression to write the data to, there is a serious issue.
    if (pCurrExpr != NULL)
    {
        cExprResultList.Add(pCurrExpr, cData);
    }
    else
    {
        throw;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    RedVSIParseStackTraverser::PopulateStack(cExprStack, pExpr, pBaseContext->cLog);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetExprResult(RedVSIParseTreeInterface* pExpr, const RedDataVariant& result)
{
    cExprResultList.Add(pExpr, result);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedVSIContextRoutine::ExprResult(RedVSIParseTreeInterface* pExpr)
{
    RedDataVariant cResult;
    if (!cExprResultList.FindDataById(pExpr, cResult))
    {
        pBaseContext->cLog.AddErrorEvent("Failed to find expression result.");
    }

    return cResult;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::ExecuteExprQueue(void)
{
    bool Blocked = IsContextBlocked(this);
    while ((!cExprStack.IsEmpty()) && (!Blocked))
    {
        pCurrExpr = cExprStack.Pop();
        pCurrExpr->CalcResult(this);

        // pCurrExpr is a context attribute, left setup at the latest routine-call node when
        // it becomes blocked.
        Blocked = IsContextBlocked(this);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetupRoutineCall(const RedVSIRoutineSignature& cCallSignature)
{
    //if (pBaseContext != NULL)
    //{
    //    RedVSILib* pLib = &(pBaseContext->cCodeLib);

    //    if (pLib != NULL)
    //    {
    //        RedVSILibRoutine* pRtn = pLib->FindRoutine(cCallSignature);

    //        // If we found a routine in the library that matched the signature
    //        if (pRtn != NULL)
    //        {
    //            // Create the new routine context
    //            RedVSIContextRoutine* pSubroutineContext = new RedVSIContextRoutine(pBaseContext, cCallSignature.cClassName, cCallSignature.cFuncName, pRtn->FirstCommand());

    //            // Add the params as local vars - the types will have been validated on selecting the routine in the library
    //            // We iterate through the signature to get the names, and the call params to get the values.
    //            {
    //                if ((pRtn->Params()->NumItems() > 0) && (pRtn->Params()->NumItems()))
    //                {
    //                    unsigned RtnLibParamFirstIndex  = pRtn->Params()->FirstIndex();
    //                    unsigned RtnLibParamLastIndex   = pRtn->Params()->LastIndex();
    //                    unsigned RtnCallParamFirstIndex = cCallSignature.cParamTypeList.FirstIndex();
    //                    unsigned RtnCallParamLastIndex  = cCallSignature.cParamTypeList.LastIndex();

    //                    if (RtnLibParamFirstIndex != RtnCallParamFirstIndex) throw;
    //                    if (RtnLibParamLastIndex  != RtnCallParamLastIndex)  throw;

    //                    RedDataString  CurrLibParamName;
    //                    RedDataVariant CurrCallParamData;

    //                    for (unsigned CurrParamIndex = RtnLibParamFirstIndex; CurrParamIndex <= RtnLibParamLastIndex; CurrParamIndex++)
    //                    {
    //                        // Get name from library param list
    //                        pRtn->Params()->FindIdByIndex(CurrParamIndex, CurrLibParamName);

    //                        // Get data from call
    //                        cCallSignature.cParamTypeList.FindElementAtIndex(CurrParamIndex, CurrCallParamData);

    //                        // Add new local variable to the new routine
    //                        pSubroutineContext->DuplicateDataItem(kLangElementLocationStack, CurrCallParamData.Value(), CurrLibParamName);
    //                    }
    //                }
    //            }

    //            // Add the thread context
    //            pSubroutineContext->SetBaseContext(pBaseContext);

    //            // Push the routine on the stack - At this point, the current context is no longer the top of the stack and is considered blocked.
    //            pBaseContext->cCallStack.Push(pSubroutineContext);
    //        }
    //        else
    //        {
    //            pBaseContext->cLog.AddErrorEvent("Setup Routine Call: Unable to find routine");
    //        }
    //    }
    //}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Routine is blocked if it is not the top routine on the thread-record routine stack.

bool RedVSIContextRoutine::IsContextBlocked(const RedVSIContextRoutine* pRoutineContext) const
{
    //if (pRoutineContext == NULL)
    //    return false;

    //if (pRoutineContext->pThreadContextRecord != NULL)
    //{
    //    if (pRoutineContext->pThreadContextRecord->TopRoutineOnStack() != this)
    //        return true;
    //}

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::IsContextExecutionComplete(const RedVSIContextRoutine* pRoutineContext) const
{
    if (pRoutineContext == NULL)
        return false;

    if (IsContextBlocked(pRoutineContext))
        return false;

    if (pRoutineContext->HasCmdToExecute())
        return false;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::IsExecutionComplete(void) const
{
    if (IsContextBlocked(this))
        return false;

    if (HasCmdToExecute())
        return false;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Execution
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Stages of execution:
// - queue expression
// - execute expression off stack
// - command logic
// - queue next commands

void RedVSIContextRoutine::Execute(const unsigned CmdCount)
{
    unsigned CommandCountdown = CmdCount;

    while ((CommandCountdown > 0) && (HasCmdToExecute()) && (!IsContextBlocked(this)))
    {
        if (eCmdPhase == eCmdExecPhaseStart)
        {
            // On entering the loop, check we have a command to execute. Prior HasCmd call ensures
            // this will pass.
            if (pCurrCmd == NULL)
                pCurrCmd = cCmdStack.Pop();

            // Queue up all the expressions needed by the command
            pCurrCmd->QueueExpr(this);
            eCmdPhase = eCmdExecPhaseExprExecuting;
        }

        if ((eCmdPhase == eCmdExecPhaseExprExecuting) && (!IsContextBlocked(this)))
        {
            ExecuteExprQueue();

            if (cExprStack.IsEmpty())
                eCmdPhase = eCmdExecPhaseCmdLogic;
        }

        if (eCmdPhase == eCmdExecPhaseCmdLogic)
        {
            // Execute the command (it will queue the next command as part of its execution)
            pCurrCmd->Execute(this);

            // Clean up after execution
            cExprResultList.DelAll();
            CommandCountdown--;
            pCurrCmd = NULL;

            // Look for the next command to execute
            if (!cCmdStack.IsEmpty())
                pCurrCmd = cCmdStack.Pop();

            // Set the phase for the next command to start
            eCmdPhase = eCmdExecPhaseStart;
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::HasCmdToExecute(void) const
{
    if (!cCmdStack.IsEmpty()) return true;
    if (pCurrCmd) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
