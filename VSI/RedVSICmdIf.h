// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedVSICmd.h"
#include "RedVSIErrorCodes.h"
#include "RedLog.h"
#include "RedVSIContextInterface.h"
#include "RedVSIParseTreeInterface.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdIf : public RedVSICmd
{
public:

    // Construction Routines
    RedVSICmdIf(void);
    ~RedVSICmdIf(void) {};

    // RedVSICmd inherited routines
    RedVSILangElement Type(void) const { return kLangElementCommandIf; };
    void              QueueExpr(RedVSIContextInterface* pContext);
    void              Execute(RedVSIContextInterface* pContext);

    // Wholesale access/assign operations
    void              SetDetails(RedVSIParseTreeInterface*& pInCmdExpr,  RedVSICmd*& pInPosBranch,  RedVSICmd*& pInNegBranch);
    void              GetDetails(RedVSIParseTreeInterface*& pOutCmdExpr, RedVSICmd*& pOutPosBranch, RedVSICmd*& pOutNegBranch) const;

private:

    RedVSIParseTreeInterface* pCmdExpr   = NULL;
    RedVSICmd*       pPosBranch = NULL;
    RedVSICmd*       pNegBranch = NULL;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
