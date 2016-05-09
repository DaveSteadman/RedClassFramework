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
#include "RedVSIToken.h"
#include "RedVSIParseTreeInterface.h"
#include "RedVSILangElement.h"
#include "RedVSIErrorCodes.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

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
    RedVSILangElement       Type(void) const   { return RedVSILangElement::ParseBinaryOp(); };

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



