
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CCmdExpr: Class to contain an expression, allowing the maths to exist in a 
// sequence. Essentially a BASIC LET statement.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdExpr : public RedVSICmdInterface
{
public: 

    // Fundamental Routines
    RedVSICmdExpr(void);
    RedVSICmdExpr(RedVSIParseTreeInterface*& pExpr) { SetDetails(pExpr); };
    ~RedVSICmdExpr(void) {};

    RedVSILangElement Type(void) { return RedVSILangElement::CommandLet(); };

    void SetDetails(RedVSIParseTreeInterface*& pInExpr)        { pExpr = pInExpr; };
    void GetDetails(RedVSIParseTreeInterface*& pOutExpr) const { pOutExpr = pExpr; };

    void SetExpr(RedVSIParseTreeInterface* pNewExpr)     { pExpr = pNewExpr; };

    void QueueExpr(RedVSIContextInterface* pContext);
    void Execute(RedVSIContextInterface* pContext);

private:

    RedVSIParseTreeInterface* pExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

