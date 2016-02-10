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

#include "RedVSIParseStackTraverser.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructor / Destructor
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::RedVSIContextRoutine(RedLog& initAnalysis) : cAnalysis(initAnalysis)
{
    // pThisObj     = 0;

    cReturnValue.Init();
    pCurrCmd     = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextRoutine::~RedVSIContextRoutine(void)
{
    cRoutineData.DelAll();
    
    //if (pReturnValue)
    //    delete pReturnValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Setup Calls
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetNameDetails(RedString& cNewObjectName, RedString& cNewClassName, RedString& cNewFuncName)
{ 
    //cObjectName = cNewObjectName;
    cClassName  = cNewClassName; 
    cFuncName   = cNewFuncName; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::AddParam(RedString cName, RedType* pData)
{
     cRoutineData.Add(cName, pData->Clone());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Data
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVSIContextRoutine::CreateDataItem(RedVSILangElement cLocation, RedVSILangElement cType, RedString cName)
{
    RedType* pNewData = REDNULL;

    // Basic Validation
    if (!cLocation.IsLocation()) throw;
    if (!cType.IsType()) throw;

    if (cLocation.IsLocationStack())
    {
        if      (cType.IsTypeBool())   pNewData = new RedBoolean();
        else if (cType.IsTypeChar())   pNewData = new RedChar();
        else if (cType.IsTypeNumber()) pNewData = new RedNumber();
        else if (cType.IsTypeString()) pNewData = new RedString();
        else
            throw;

        cRoutineData.Add(cName, pNewData);
    }
    else if (cLocation.IsLocationAttribute())
    {
        throw;
    }
    else
    {
        throw;
    }

    // return the pointer to the new object (or zero)
    return pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIContextRoutine::FindDataItem(const RedString& cName, RedType*& pData)
{
    // first try and get the data from the local routine
    if (cRoutineData.Find(cName, pData))
        return 1;

    // if not present, look in the This object
    // if (pThisObj)
    //     return pThisObj->Find(cName, pData);

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetReturnValue(const RedVariant& cData)
{
    // copy the variant data item across and return success
    cReturnValue = cData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetSubroutineReturnValue(RedVariant& cData)
{
    // if we don't have an expression to write the data to, there is a serious issue.
    if (pCurrExpr != REDNULL)
        cWorkingList.Add(pCurrExpr, cData);
    else
        throw;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIContextRoutine::HasCmdToExecute(void)
{ 
    if (!cCmdStack.IsEmpty()) return 1;
    if (pCurrCmd) return 1;
    
    return 0; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    RedVSIParseStackTraverser::PopulateStack(cExprStack, pExpr, cAnalysis);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextRoutine::SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result)
{
    cWorkingList.Add(pExpr, result);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVSIContextRoutine::ExprResult(RedVSIParseTreeInterface* pExpr)
{
    RedVariant cResult;
    if (!cWorkingList.Find(pExpr, cResult)) throw;

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
// Execution
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

