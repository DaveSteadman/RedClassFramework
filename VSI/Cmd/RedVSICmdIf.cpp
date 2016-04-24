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

#include "RedVSICmdIf.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdIf::RedVSICmdIf(void)
{
    // this object's attributes
    pCmdExpr   = REDNULL;
    pPosBranch = REDNULL;
    pNegBranch = REDNULL;

    // parents attributes
    SetNextCmd(REDNULL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdIf::SetDetails(RedVSIParseTreeInterface*& pInCmdExpr,  RedVSICmdInterface*& pInPosBranch,  RedVSICmdInterface*& pInNegBranch)
{
    pCmdExpr   = pInCmdExpr;
    pPosBranch = pInPosBranch;
    pNegBranch = pInNegBranch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdIf::GetDetails(RedVSIParseTreeInterface*& pOutCmdExpr, RedVSICmdInterface*& pOutPosBranch, RedVSICmdInterface*& pOutNegBranch) const
{
    pOutCmdExpr   = pCmdExpr;
    pOutPosBranch = pPosBranch;
    pOutNegBranch = pNegBranch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdIf::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pCmdExpr)
        pContext->QueueExpr(pCmdExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdIf::Execute(RedVSIContextInterface* pContext)
{
    // Regardless of the expression outcome, queue the next command
    pContext->QueueCommand(NextCmd());

    // Get the result of the conditional expression
    RedVariant cExprResult = pContext->ExprResult(pCmdExpr);

    // Queue a branch depending on the expression
    if (IsSuccessVal(cExprResult))
        pContext->QueueCommand(pPosBranch);
    else
        pContext->QueueCommand(pNegBranch);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSICmdIf::IsSuccessVal(RedVariant& cVal)
{
    if (cVal.Type().IsNum())
    {
        if (!cVal.NumberValue().IsZero())
            return true;
    }
    
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



