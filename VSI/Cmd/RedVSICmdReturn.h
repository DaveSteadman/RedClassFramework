
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"
#include "RedLog.h"
#include "RedVSIContextInterface.h"
#include "RedVSIParseTreeInterface.h"

#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdReturn : public RedVSICmdInterface
{
public:

    RedVSICmdReturn(void);
    ~RedVSICmdReturn(void) {};

    RedVSILangElement Type(void) { return RedVSILangElement::CommandReturn(); };
    
    void SetDetails(RedVSIParseTreeInterface*& pInReturnExpr)        { pReturnExpr    = pInReturnExpr; };
    void GetDetails(RedVSIParseTreeInterface*& pOutReturnExpr) const { pOutReturnExpr = pReturnExpr; };

    void QueueExpr(RedVSIContextInterface* pContext);
    void Execute(RedVSIContextInterface* pContext);

private:

    RedVSIParseTreeInterface* pReturnExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


