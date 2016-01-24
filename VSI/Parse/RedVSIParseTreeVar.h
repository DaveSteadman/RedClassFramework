
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSIErrorCodes.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

class RedVSIParseTreeVar : public RedVSIParseTreeInterface
{
public:

    // construction;
    RedVSIParseTreeVar(void) { cVarName=""; };
    RedVSIParseTreeVar(RedString cNewVarName) { cVarName=cNewVarName; };
    //RedVSIParseTreeVar(RedString cNewVarName, RedVSIParseTreeInterface* pNewVarIndexExpr) { SetDetails(cNewVarName, pNewVarIndexExpr); };
    ~RedVSIParseTreeVar();

    // inherited
    void                    CalcResult(RedVSIContextInterface* pContext);
    const RedVSILangElement Type(void) const { return RedVSILangElement::ParseVariable(); };

    void             SetVarName(const RedString& cInVarName) { cVarName = cInVarName; };
    const RedString& VarName(void) const                     { return cVarName; };

    //void        SetDetails(RedString& cInVarName,  RedVSIParseTreeInterface*& pInVarIndexExpr);
    //void        GetDetails(RedString& cOutVarName, RedVSIParseTreeInterface*& pOutVarIndexExpr);


    void        AssignValue(RedVSIContextInterface* pContext, RedVariant& result);

private:

    int         FindDataItem(RedVSIContextInterface* pContext, RedType*& pDataItem);

    RedString                  cVarName;
    //RedVSIParseTreeInterface*  pVarIndexExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
