
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedDataType.h"
#include "RedVSIParseTreeInterface.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdNew : public RedVSICmdInterface
{
public:

    // Fundamental Routines
    RedVSICmdNew();
    RedVSICmdNew(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, RedString cInName, RedVSIParseTreeInterface* pInInitExpr) { SetDetails(cInType, cInLoc, cInName, pInInitExpr); };


    ~RedVSICmdNew(void) {};

    RedVSILangElement Type(void) { return RedVSILangElement::CommandNew(); };

    void SetDetails(const RedVSILangElement& cInType,  const RedVSILangElement& cInLoc,  RedString cInName,  RedVSIParseTreeInterface* pInInitExpr);
    void GetDetails(RedVSILangElement& cOutType, RedVSILangElement& cOutLoc, RedString& cOutName, RedVSIParseTreeInterface*& pOutInitExpr) const;

    void QueueExpr(RedVSIContextInterface* pContext);
    void Execute(RedVSIContextInterface* pContext);

    void SetType(RedVSILangElement cNewType)                 { if (!cLoc.IsType())     throw; cType=cNewType; };
    void SetLoc(RedVSILangElement cNewLoc)                   { if (!cLoc.IsLocation()) throw; cLoc=cNewLoc; };
    void SetName(const RedString& cNewName)                  { cName=cNewName; };
    void SetInitExpr(RedVSIParseTreeInterface* pNewInitExpr) { pInitExpr=pNewInitExpr; };

private:
    
    RedVSILangElement         cType;
    RedVSILangElement         cLoc;
    RedString                 cName;
    RedVSIParseTreeInterface* pInitExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


