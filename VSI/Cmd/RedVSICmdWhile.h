
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"
#include "RedVSIParseTreeInterface.h"
#include "RedVSIErrorCodes.h"
#include "RedVSIContextInterface.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdWhile : public RedVSICmdInterface
{
public:

    RedVSICmdWhile(void);
    ~RedVSICmdWhile(void) {};

    RedVSILangElement Type(void) { return RedVSILangElement::CommandWhile(); };
    
    void         QueueExpr(RedVSIContextInterface* pContext);

    void SetDetails(RedVSIParseTreeInterface*& pInConditionExpr,  RedVSICmdInterface*& pInLoopBranch);
    void GetDetails(RedVSIParseTreeInterface*& pOutConditionExpr, RedVSICmdInterface*& pOutLoopBranch) const;

    void Execute(RedVSIContextInterface* pContext);

private:

    int IsSuccessVal(RedVariant& cVal);

    RedVSIParseTreeInterface* pConditionExpr;
    RedVSICmdInterface*       pLoopBranch;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

