// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSIErrorCodes::GetErrorString(TErrorCodes eErrCode)
{
    RedDataString cErrStr = "Undefined Error Code";

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
    case eNew_ResultTypeMismatch:       cErrStr = "CommandNew: Initialising expression different type to declared data item."; break;
    case eNew_CreateError:              cErrStr = "CommandNew: Data item not created."; break;

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
