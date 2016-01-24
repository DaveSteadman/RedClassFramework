
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIToken.h"
#include "RedVSIParseTreeInterface.h"

#include "RedVSILangElement.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseTreeBinaryOp : public RedVSIParseTreeInterface
{
public:

    // constructor
    RedVSIParseTreeBinaryOp(void);
    RedVSIParseTreeBinaryOp(RedVSIParseTreeInterface* pLeft, RedVSILangElement cOp, RedVSIParseTreeInterface* pRight);

    // inherited
    ~RedVSIParseTreeBinaryOp(void);
    void                    CalcResult(RedVSIContextInterface* pContext);
    const RedVSILangElement Type(void) const   { return RedVSILangElement::ParseBinaryOp(); };

    // Assign/Query operations
    void                        SetLeftChild(RedVSIParseTreeInterface* pNewLeft)   { pLeft=pNewLeft; };
    void                        SetRightChild(RedVSIParseTreeInterface* pNewRight) { pRight=pNewRight; };
    void                        SetOp(RedVSILangElement cNewOp)                    { cOp = cNewOp; };
    RedVSIParseTreeInterface*   LeftChild(void) const                              { return pLeft; };
    RedVSIParseTreeInterface*   RightChild(void) const                             { return pRight; };
    RedVSILangElement           Op(void) const                                     { return cOp; };

    void                        GetDetails(RedVSIParseTreeInterface*& pOutLeft, RedVSILangElement& cOutOp, RedVSIParseTreeInterface*& pOutRight);

private:

    RedVariant                  CalcPowerOp(RedVariant cLeftVal, RedVariant cRightVal);

    RedVSILangElement         cOp;
    RedVSIParseTreeInterface* pLeft;
    RedVSIParseTreeInterface* pRight;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



