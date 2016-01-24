
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedVSIErrorCodes::GetErrorString(TErrorCodes eErrCode)
{
    RedString cErrStr = "Undefined Error Code";

    switch(eErrCode)
    {
    // Generic
    case eFile_FailedToOpen:            cErrStr = "FILE: Failed to open."; break;

    // Parse Factory
    case ePFact_Call_NoExpr:            cErrStr=""; break;
    case ePFact_ItemExpr_NoItem:        cErrStr=""; break;
    case ePFact_SubExpr_NoExpr:         cErrStr=""; break;
    case ePFact_SubExpr_NoExprEnd:      cErrStr=""; break;
    case ePFact_Var_NoArrayExpr:        cErrStr=""; break;
    case ePFact_Var_NoArrayExprEnd:     cErrStr=""; break;

    // Command Factory
    case eCFact_New_BadLoc:             cErrStr=""; break;
    case eCFact_New_BadType:            cErrStr=""; break;
    case eCFact_New_BadName:            cErrStr=""; break;
    case eCFact_New_NoInitExpr:         cErrStr=""; break;
    case eCFact_If_KeywordError:        cErrStr=""; break;
    case eCFact_If_NoExpr:              cErrStr=""; break;

    // Command
    case eNew_ResultTypeMismatch:       cErrStr="CommandNew: Initialising expression different type to declared data item."; break;

    // Parse
    case eParseVar_NoVar:               cErrStr=""; break;
    case eParseVar_NoAssign:            cErrStr=""; break;
    case eParseVar_NotArray:            cErrStr=""; break;
    case eParseVar_IndexNotInteger:     cErrStr="ParseVariable: Result of array index expression not integer."; break;
    case eParseBinOp_NotVar:            cErrStr="ParseBinaryOperator: Assignment to non-variable."; break;
    case eParseBinOp_NoResult:          cErrStr="ParseBinaryOperator: No result from expression."; break;
    case eParseBinOp_RightOnlyObj:      cErrStr="ParseBinaryOperator: Invalid object on right of expression."; break;

    // An error here is regarding an undefined error string, so halting execution helps highlight this.
    default: 
        throw;
    }

    return cErrStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
