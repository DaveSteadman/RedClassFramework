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

#include "RedVSICmdWhile.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdWhile::RedVSICmdWhile(void)
{
    // this object's attributes
    pConditionExpr = NULL;
    pLoopBranch    = NULL;

    // parents attributes
    SetNextCmd(NULL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdWhile::SetDetails(RedVSIParseTreeInterface*& pInConditionExpr, RedVSICmdInterface*& pInLoopBranch)
{
    pConditionExpr = pInConditionExpr;
    pLoopBranch    = pInLoopBranch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdWhile::GetDetails(RedVSIParseTreeInterface*& pOutConditionExpr, RedVSICmdInterface*& pOutLoopBranch) const
{
    pOutConditionExpr = pConditionExpr;
    pOutLoopBranch    = pLoopBranch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdWhile::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pConditionExpr)
        pContext->QueueExpr(pConditionExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdWhile::Execute(RedVSIContextInterface* pContext)
{
    // Get the result of the conditional expression
    RedVariant cExprResult = pContext->ExprResult(pConditionExpr);

    // check if the value is a positive statement
    if (cExprResult.IsSuccessVal())
    {
        // First queue this command for re-evaluation, then queue the branch 
        // command on top of it
        pContext->QueueCommand(this);
        pContext->QueueCommand(pLoopBranch);
    }
    else
    {
        // condition failed, so queue the next command and move on.
        pContext->QueueCommand(NextCmd());
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


