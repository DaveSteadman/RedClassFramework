// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdWhile.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdWhile::RedVSICmdWhile(void)
{
    // this object's attributes
    pConditionExpr = 0;
    pLoopBranch = 0;

    // parents attributes
    SetNextCmd(0);
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
    RedVariant cExprResult = pContext->GetExprResult(pConditionExpr);

    // check if the value is a positive statement
    if (IsSuccessVal(cExprResult))
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

int RedVSICmdWhile::IsSuccessVal(RedVariant& cVal)
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


