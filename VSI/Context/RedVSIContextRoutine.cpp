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

#include "RedVSIContextRoutine.h"
//#include "CDataArray.h"
#include "RedVSILibInterface.h"
#include "RedVSIParseStackTraverser.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructor / Destructor
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedLog& initAnalysis) : cAnalysis(initAnalysis)
{
    // pThisObj     = 0;

    cReturnValue.Init();
    pCurrCmd       = REDNULL;
    pContextRecord = REDNULL;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedLog& initAnalysis, RedVSICmdInterface* pFirstCmd) : cAnalysis(initAnalysis)
{
    // pThisObj     = 0;

    cReturnValue.Init();
    pCurrCmd       = pFirstCmd;
    pContextRecord = REDNULL;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(const RedString& inClassName, const RedString& inRoutineName, RedVSICmdInterface* pFirstCmd, RedLog& inAnalysis) : cAnalysis(inAnalysis)
{
    ClassName      = inClassName;
    RoutineName    = inRoutineName;
    pCurrCmd       = pFirstCmd;
    pContextRecord = REDNULL;

    eCmdPhase = eCmdExecPhaseStart;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::~RedVSIContextRoutine(void)
{
    cLocalVariables.DelAll();
    
    //if (pReturnValue)
    //    delete pReturnValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Setup Calls
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedVSIContextRoutine::SetNameDetails(RedString& cNewObjectName, RedString& cNewClassName, RedString& cNewFuncName)
//{ 
//    //cObjectName = cNewObjectName;
//    cClassName  = cNewClassName; 
//    cFuncName   = cNewFuncName; 
//}
//
//// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedVSIContextRoutine::AddParam(RedString cName, RedType* pData)
//{
//     cRoutineData.Add(cName, pData->Clone());
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Data
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVSIContextRoutine::CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName)
{
    RedType* pNewData = REDNULL;

    // Basic Validation
    if (!cLocation.IsLocation()) throw;
    if (!cType.IsType()) throw;

    RedDataType DataType = RedVSILangElement::DataTypeForLangElemType(cType);

    if (cLocation.IsLocationStack())
    {
        pNewData = cLocalVariables.CreateAndAdd(cName, DataType);
    }
    else if (cLocation.IsLocationHeap())
    {
        if (pContextRecord != REDNULL)
        {
            pNewData = pContextRecord->CreateHeapDataItem(cType, cName);
        }
    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::FindDataItem(const RedString& cName, RedType*& pData)
{
    // first try and get the data from the local routine
    if (cLocalVariables.Find(cName, pData))
        return true;

    if (pContextRecord != REDNULL)
    {
        if (pContextRecord->FindHeapDataItem(cName, pData))
            return true;
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetReturnValue(const RedVariant& cData)
{
    // if we don't have an expression to write the data to, there is a serious issue.
    if (pCurrExpr != REDNULL)
        cExprResultList.Add(pCurrExpr, cData);
    else
        throw;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    RedVSIParseStackTraverser::PopulateStack(cExprStack, pExpr, cAnalysis);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result)
{
    cExprResultList.Add(pExpr, result);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVSIContextRoutine::ExprResult(RedVSIParseTreeInterface* pExpr)
{
    RedVariant cResult;
    if (!cExprResultList.Find(pExpr, cResult)) throw;

    return cResult;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::ExecuteExprQueue(void)
{
    int iBlocked = IsBlocked(this);
    while ( (!cExprStack.IsEmpty()) && (!iBlocked) )
    {
        pCurrExpr = cExprStack.Pop();
        pCurrExpr->CalcResult(this);
        iBlocked = IsBlocked(this);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature)
{
    if (pContextRecord != REDNULL)
    {
        const RedVSILibInterface* pLib = pContextRecord->CodeLib();
        RedVSILibRoutineInterface* pRtn = pLib->FindRoutine(cSignature);
    }
    // If there is no context-thread
    else
    {
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/// Routine is blocked if it is not the top routine on the thread-record routine stack.

bool RedVSIContextRoutine::IsBlocked(const RedVSIContextInterface* pRoutineContext)
{
    if (pContextRecord != REDNULL)
    {
        if (pContextRecord->TopRoutineOnStack() != this)
            return false;
    }

    return false;
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

    while ( (CommandCountdown > 0) && (pCurrCmd != REDNULL) )
    {
        if (eCmdPhase == eCmdExecPhaseStart)
        {
            // Queue up all the expressions needed by the command
            pCurrCmd->QueueExpr(this);
            eCmdPhase = eCmdExecPhaseExprExecuting;
        }

        if ( (eCmdPhase == eCmdExecPhaseExprExecuting) && (!IsBlocked(this)) )
        {
            ExecuteExprQueue();
            
            if (cExprStack.IsEmpty())
                eCmdPhase = eCmdExecPhaseCmdLogic;
        }

        if (eCmdPhase == eCmdExecPhaseCmdLogic)
        {
            // Execute the command (it will queue the next command as part of its execution)
            pCurrCmd->Execute(this);

            // An ending command-path can pop a Null. As long as we have further entries to Pop, look for a non-null
            pCurrCmd = cCmdStack.Pop();
            while ((pCurrCmd == REDNULL) && (!cCmdStack.IsEmpty()))
                pCurrCmd = cCmdStack.Pop();

            eCmdPhase = eCmdExecPhaseStart;
        }

    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextRoutine::HasCmdToExecute(void)
{ 
    if (!cCmdStack.IsEmpty()) return true;
    if (pCurrCmd) return true;
    
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedVSIContextRoutine::Execute(RedVSIInterfaceContext* pTopLevelContext)
//{
//    // Any command has the potential to affect the thread by adding a new (blocking) routine
//    // call, so each call execs only one command before returning for the thread to make the 
//    // next decision on what to do.
//
//    // if we have no command, get a new one and queue up the expressions
//    if (!pCurrCmd)
//    {
//        // get the top level command
//        pCurrCmd = cCmdStack.Pop();
//
//        // queue up all the expressions needed by the command
//        pCurrCmd->QueueExpr(pTopLevelContext);
//    }
//
//    // execute any expressions until we run out or get blocked
//    int iBlocked = pTopLevelContext->IsBlocked(this);
//    while ( (!cExprStack.IsEmpty()) && (!iBlocked) )
//    {
//        pCurrExpr = cExprStack.Pop();
//        pCurrExpr->CalcResult(pTopLevelContext);
//        iBlocked = pTopLevelContext->IsBlocked(this);
//    }
//    
//    // if all the expressions have completed, move on to process the command
//    if (!iBlocked)
//    {
//        pCurrCmd->Execute(pTopLevelContext);
//
//        // now clear out all the temp data associated with executing the command
//        cWorkingList.DelAll();
//        pCurrExpr = 0;
//        pCurrCmd = 0;
//    }
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

