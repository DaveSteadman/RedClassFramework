#pragma once

#include "RedVSIParseTreeInterface.h"
#include "RedVSILibRoutineInterface.h"
//#include "RedVSIObject.h"
#include "RedVSIErrorCodes.h"
#include "RedVSILangElement.h"
#include "RedVSICollections.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseTreeCall : public RedVSIParseTreeInterface
{
public:

    // Constructors
    RedVSIParseTreeCall(void) { pParamList=0; };
    ~RedVSIParseTreeCall(void);

    const RedVSILangElement Type(void) const { return RedVSILangElement::ParseFuncCall(); };

    void SetDetails(const RedString& cInObjectName,  const RedString& cInClassName, const RedString& cInFuncName,  RedVSIParseList*& pInParamList);
    void GetDetails(      RedString& cOutObjectName,       RedString& cOutClassName,       RedString& cOutFuncName, RedVSIParseList*& pOutParamList);

    // Operation
    void CalcResult(RedVSIContextInterface* pContext);

private:

    RedString          cObjectName;
    RedString          cClassName;
    RedString          cFuncName;
    RedVSIParseList*   pParamList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



