#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIParseTreeInterface.h"
#include "RedVariant.h"
#include "RedVSIErrorCodes.h"
#include "RedVSIContextInterface.h"
#include "RedVSIErrorCodes.h"
#include "RedVSILangElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSIParseTreeUnaryOp : public RedVSIParseTreeInterface
{
public:

    RedVSIParseTreeUnaryOp(RedVSILangElement cNewOp, RedVSIParseTreeInterface* pNewExpr);
    ~RedVSIParseTreeUnaryOp(void);

    const RedVSILangElement Type(void) const { return RedVSILangElement::ParseUnaryOp(); };

    void                    SetOp(RedVSILangElement cNewOp)   { cOp = cNewOp; };
    RedVSILangElement       Op(void) const                    { return cOp; };

    void CalcResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete);

    void GetDetails(RedVSILangElement& cOutOp, RedVSIParseTreeInterface*& pNodeExpr);

protected:
    
    void CalcNegateResult    (RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete);
    void CalcAddrOfItemResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete);
    void CalcItemAtAddrResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete);
    
private:

    void LogError(RedVSIContextInterface& cContext, RedVSIErrorCodes::TErrorCodes eErr);

    RedVSILangElement         cOp;
    RedVSIParseTreeInterface* pExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


