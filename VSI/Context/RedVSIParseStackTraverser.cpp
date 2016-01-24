// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseStackTraverser.h"

#include "RedVSILangElement.h"

#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeVar.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeCall.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operation taking a top-level expression node and adding it, and all its child nodes, to the expression stack.
// The queueing is done in an order to guarantee that every node will have all its dependencies resolved prior to its own
// execution, allowing the internal expression execution to not consider this issue.

void RedVSIParseStackTraverser::PopulateStack(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    RedVSILangElement cNodeType = pExpr->Type();
    
    if      (cNodeType.IsParseBinaryOp()) { RedVSIParseStackTraverser::AddBinaryOp(cStack, pExpr, log); }
    else if (cNodeType.IsParseVariable()) { RedVSIParseStackTraverser::AddVariable(cStack, pExpr, log); }
    else if (cNodeType.IsParseValue())    { RedVSIParseStackTraverser::AddValue(cStack, pExpr, log); }
    else if (cNodeType.IsParseFuncCall()) { RedVSIParseStackTraverser::AddCall(cStack, pExpr, log); }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddBinaryOp(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    RedVSIParseTreeBinaryOp*  pBinOp = (RedVSIParseTreeBinaryOp*)pExpr;
    
    RedVSIParseTreeInterface* pLeft;
    RedVSILangElement         cOp;
    RedVSIParseTreeInterface* pRight;
    
    pBinOp->GetDetails(pLeft, cOp, pRight);
    
    // quick validity check
    if ((!pLeft) || (!pRight)) { log.AddText("Badly Formed BinaryOp"); return; }
        
    // push top level onto stack
    cStack.Push(pExpr);

    // start process over for children
    RedVSIParseStackTraverser::PopulateStack(cStack, pLeft, log);
    RedVSIParseStackTraverser::PopulateStack(cStack, pRight, log);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddVariable(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    
//    RedVSIParseTreeVar* pVar = (RedVSIParseTreeVar*)pExpr;
//    
//    RedString cInVarName;
//    RedVSIParseTreeInterface* pInVarIndexExpr = REDNULL;
//    
//    //pVar->GetDetails(cInVarName, pInVarIndexExpr);
//
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
    // push expr onto stack
    cStack.Push(pExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseStackTraverser::AddCall(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log)
{
    // push call onto stack
    cStack.Push(pExpr);

    RedVSIParseTreeCall* pCall = (RedVSIParseTreeCall*)pExpr;

    // Get the call details
    RedString cOutObjectName;
    RedString cOutClassName;
    RedString cOutFuncName;
    RedVSIParseList* pOutParamList;
    pCall->GetDetails(cOutObjectName, cOutClassName, cOutFuncName, pOutParamList);
    
    // Get the iterator for the parameters list. Stack the params up backwards so
    // the first parameter is executed first.
    RedVSIParseListIterator cIt(pOutParamList);
    //cIt.SetSearchDirectionBackwards();
    
    // loop through and queue up parameters.
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

