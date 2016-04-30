// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
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


#include "RedCoreNamespace.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedVSIErrorCodes.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class to contain an expression, allowing the maths to exist in a sequence.
/// Essentially a BASIC LET statement.
class RedVSICmdLet : public RedVSICmdInterface
{
public: 

    // Construction Routines
    RedVSICmdLet(void);
    RedVSICmdLet(RedVSIParseTreeInterface*& pExpr) { SetDetails(pExpr); };
    ~RedVSICmdLet(void) {};

    // RedVSICmdInterface inherited routines
    RedVSILangElement Type(void) { return kLangElementCommandLet; };
    void QueueExpr(RedVSIContextInterface* pContext);
    void Execute(RedVSIContextInterface* pContext);

    // Command Setup
    void SetExpr(RedVSIParseTreeInterface* pNewExpr)     { pExpr = pNewExpr; };

    // Wholesale access/assign operations
    void SetDetails(RedVSIParseTreeInterface*& pInExpr)        { pExpr = pInExpr; };
    void GetDetails(RedVSIParseTreeInterface*& pOutExpr) const { pOutExpr = pExpr; };

private:

    RedVSIParseTreeInterface* pExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

