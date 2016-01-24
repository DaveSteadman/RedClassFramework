// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdReturn.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdReturn::RedVSICmdReturn(void)
{
    // this object's attributes
    pReturnExpr = 0;

    // parents attributes
    SetNextCmd(0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdReturn::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pReturnExpr)
        pContext->QueueExpr(pReturnExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdReturn::Execute(RedVSIContextInterface* pContext)
{
    // If we have an expression, just finish up and return
    if (pReturnExpr)
    {
        // Get the expression value
        RedVariant res = pContext->GetExprResult(pReturnExpr);
        
        // assign the return value
        pContext->SetReturnValue(res);
    }

    // remove any commands from the queue, so the routine terminates.
    pContext->ClearCommandQueue();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


