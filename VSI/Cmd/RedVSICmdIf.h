
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"
#include "RedVSIErrorCodes.h"
#include "RedLog.h"
#include "RedVSIContextInterface.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdIf : public RedVSICmdInterface
{
public:

    RedVSICmdIf(void);
    ~RedVSICmdIf(void) {};

    RedVSILangElement Type(void) { return RedVSILangElement::CommandIf(); };
    
    void            QueueExpr(RedVSIContextInterface* pContext);

    void SetDetails(RedVSIParseTreeInterface*& pInCmdExpr,  RedVSICmdInterface*& pInPosBranch,  RedVSICmdInterface*& pInNegBranch);
    void GetDetails(RedVSIParseTreeInterface*& pOutCmdExpr, RedVSICmdInterface*& pOutPosBranch, RedVSICmdInterface*& pOutNegBranch) const;

    void Execute(RedVSIContextInterface* pContext);

private:

    int IsSuccessVal(RedVariant& cVal);

    RedVSIParseTreeInterface* pCmdExpr;
    RedVSICmdInterface*       pPosBranch;
    RedVSICmdInterface*       pNegBranch;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


