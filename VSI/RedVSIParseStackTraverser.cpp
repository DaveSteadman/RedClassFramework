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

#include "RedCoreNamespace.h"

#include "RedVSIParseStackTraverser.h"

#include "RedVSILangElement.h"

#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeVar.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeCall.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operation taking a top-level expression node and adding it, and all its child nodes, to the expression stack.
// The queueing is done in an order to guarantee that every node will have all its dependencies resolved prior to its own
// execution, allowing the internal expression execution to not consider this issue.

void RedVSIParseStackTraverser::PopulateStack(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    RedVSILangElement cNodeType = pExpr->Type();
    
    if      (cNodeType.IsParseBinaryOp()) { RedVSIParseStackTraverser::AddBinaryOp(cStack, pExpr, log); }
    else if (cNodeType.IsParseVariable()) { RedVSIParseStackTraverser::AddVariable(cStack, pExpr, log); }
    else if (cNodeType.IsParseValue())    { RedVSIParseStackTraverser::AddValue   (cStack, pExpr, log); }
    else if (cNodeType.IsParseFuncCall()) { RedVSIParseStackTraverser::AddCall    (cStack, pExpr, log); }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddBinaryOp(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    RedVSIParseTreeBinaryOp*  pBinOp = dynamic_cast<RedVSIParseTreeBinaryOp*>(pExpr);
    
    RedVSIParseTreeInterface* pLeft;
    RedVSILangElement         cOp;
    RedVSIParseTreeInterface* pRight;
    
    pBinOp->GetDetails(pLeft, cOp, pRight);
    
    // Quick validity check
    if ((!pLeft) || (!pRight)) { log.AddErrorEvent("Badly Formed BinaryOp"); return; }
        
    // Push top level onto stack
    cStack.Push(pExpr);

    // Start process over for children
    RedVSIParseStackTraverser::PopulateStack(cStack, pLeft, log);
    RedVSIParseStackTraverser::PopulateStack(cStack, pRight, log);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddVariable(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
//    RedVSIParseTreeVar* pVar = (RedVSIParseTreeVar*)pExpr;
//    
//    RedDataString cInVarName;
//    RedVSIParseTreeInterface* pInVarIndexExpr = NULL;
//    
//    //pVar->GetDetails(cInVarName, pInVarIndexExpr);
//
    // push expr onto stack
    cStack.Push(pExpr);
//
//    // push index expression onto the stack if we need it.
//    if (pInVarIndexExpr)
//        cStack.Push(pInVarIndexExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddValue(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    // Push expr onto stack
    cStack.Push(pExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddCall(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    // Push call onto stack
    cStack.Push(pExpr);

    RedVSIParseTreeCall* pCall = dynamic_cast<RedVSIParseTreeCall*>(pExpr);

    // Get the call details
    RedDataString        cOutObjectName;
    RedDataString        cOutClassName;
    RedDataString        cOutFuncName;
    RedVSIParseList* pOutParamList;
    pCall->GetDetails(cOutObjectName, cOutClassName, cOutFuncName, pOutParamList);
    
    // Get the iterator for the parameters list. Stack the params up backwards so
    // the first parameter is executed first.
    RedVSIParseListIterator cIt(pOutParamList);
    
    // Loop through and queue up parameters.
    while (!cIt.IsDone())
    {
        RedVSIParseTreeInterface* pCurrParam  = cIt.CurrentItem();
        RedVSIParseStackTraverser::PopulateStack(cStack, pCurrParam, log);
        cIt.Next();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

