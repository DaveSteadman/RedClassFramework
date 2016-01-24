
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIToken.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIErrorCodes
{
public:

    typedef enum TErrorCodes {

        // Generic
        eFile_FailedToOpen,

        // Parse Factory
        ePFact_Call_NoExpr,
        ePFact_ItemExpr_NoItem,
        ePFact_SubExpr_NoExpr,
        ePFact_SubExpr_NoExprEnd,
        ePFact_Var_NoArrayExpr,
        ePFact_Var_NoArrayExprEnd,
        
        eCFact_New_BadLoc,
        eCFact_New_BadType,
        eCFact_New_BadName,
        eCFact_New_NoInitExpr,
        eCFact_If_KeywordError,
        eCFact_If_NoExpr,

        eNew_ResultTypeMismatch,

        eParseVar_NoVar,
        eParseVar_NoAssign,
        eParseVar_NotArray,
        eParseVar_IndexNotInteger,
        eParseBinOp_NotVar,
        eParseBinOp_NoResult,
        eParseBinOp_RightOnlyObj
    } TErrorCodes;

    static RedString GetErrorString(TErrorCodes eErrCode);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
