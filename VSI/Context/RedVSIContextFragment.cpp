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

#include "RedVSIContextFragment.h"
//#include "CDataArray.h"

#include "RedVSIParseStackTraverser.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructor / Destructor
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextFragment::RedVSIContextFragment(RedLog& initAnalysis) : cAnalysis(initAnalysis)
{
    pCurrCmd     = REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextFragment::RedVSIContextFragment(RedLog& initAnalysis, RedVSICmdInterface* pSnippetCmd) : cAnalysis(initAnalysis)
{
    pCurrCmd     = pSnippetCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIContextFragment::~RedVSIContextFragment(void)
{
    cRoutineData.DelAll();
    
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

RedType* RedVSIContextFragment::CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName)
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

bool RedVSIContextFragment::FindDataItem(const RedString& cName, RedType*& pData)
{
    // first try and get the data from the local routine
    if (cRoutineData.Find(cName, pData))
        return true;

    // if not present, look in the This object
    // if (pThisObj)
    //     return pThisObj->Find(cName, pData);

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::SetReturnValue(const RedVariant& cData)
{
    // if we don't have an expression to write the data to, there is a serious issue.
    if (pCurrExpr != REDNULL)
        cExprResultList.Add(pCurrExpr, cData);
    else
        throw;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::QueueExpr(RedVSIParseTreeInterface* pExpr)
{
    RedVSIParseStackTraverser::PopulateStack(cExprStack, pExpr, cAnalysis);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result)
{
    cExprResultList.Add(pExpr, result);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVSIContextFragment::ExprResult(RedVSIParseTreeInterface* pExpr)
{
    RedVariant cResult;
    if (!cExprResultList.Find(pExpr, cResult)) throw;

    return cResult;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Execution
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::Execute(const unsigned CmdCount)
{
    unsigned CommandCountdown = CmdCount;

    while ( (CommandCountdown > 0) && (pCurrCmd != REDNULL) )
    {
        // Queue up all the expressions needed by the command
        pCurrCmd->QueueExpr(this);
        ExecuteExprQueue();

        if (IsBlocked(this))
        {
            cAnalysis.AddErrorEvent("Expression blocked on running code fragment.");
            return;
        }

        // Execute the command (it will queue the next command as part of its execution)
        pCurrCmd->Execute(this);

        // An ending command-path can pop a Null. As long as we have further entries to Pop, look for a non-null
        pCurrCmd = cCmdStack.Pop();
        while ((pCurrCmd == REDNULL) && (!cCmdStack.IsEmpty()))
            pCurrCmd = cCmdStack.Pop();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIContextFragment::HasCmdToExecute(void)
{ 
    if (!cCmdStack.IsEmpty()) return true;
    if (pCurrCmd) return true;
    
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIContextFragment::ExecuteExprQueue(void)
{
    while ( !cExprStack.IsEmpty() )
    {
        pCurrExpr = cExprStack.Pop();

        // Need to abort any expression with a function call in
        if (pCurrExpr->Type().IsParseFuncCall())
        {
            cAnalysis.AddErrorEvent("Routine call parse-node found inside code fragment.");
            return;
        }

        pCurrExpr->CalcResult(this);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

