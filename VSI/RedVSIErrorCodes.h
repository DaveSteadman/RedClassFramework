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
        eCFact_Log_NoExpr,

        eCFact_While_ExprError,
        eCFact_While_NoLoopKeyword,
        eCFact_While_NoEndLoopKeyword,
        
        eNew_CreateError,
        eNew_ResultTypeMismatch,
        eLoadCode_NoFile,

        eParseVar_NoVar,
        eParseVar_NoAssign,
        eParseVar_NotArray,
        eParseVar_IndexNotInteger,
        eParseBinOp_NotVar,
        eParseBinOp_NoResult,
        eParseBinOp_RightOnlyObj
    } TErrorCodes;

    static RedDataString GetErrorString(TErrorCodes eErrCode);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
