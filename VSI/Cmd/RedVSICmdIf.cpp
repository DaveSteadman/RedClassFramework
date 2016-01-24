

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdIf.h"

namespace Red {
namespace VSI {

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
    // regardless of the expression outcome, queue the next command
    pContext->QueueCommand(NextCmd());

    // Get the result of the conditional expression
    RedVariant cExprResult = pContext->GetExprResult(pCmdExpr);

    // Queue a branch depending on the expression
    if (IsSuccessVal(cExprResult))
        pContext->QueueCommand(pPosBranch);
    else
        pContext->QueueCommand(pNegBranch);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSICmdIf::IsSuccessVal(RedVariant& cVal)
{
    if (cVal.Type().IsNum())
    {
        if (!cVal.NumberValue().IsZero())
            return 1;
    }
    
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



