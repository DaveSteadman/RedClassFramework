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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSIErrorCodes.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

class RedVSIParseTreeVar : public RedVSIParseTreeInterface
{
public:

    // construction;
    RedVSIParseTreeVar(void) { cVarName=""; };
    RedVSIParseTreeVar(RedString cNewVarName) { cVarName=cNewVarName; };
    //RedVSIParseTreeVar(RedString cNewVarName, RedVSIParseTreeInterface* pNewVarIndexExpr) { SetDetails(cNewVarName, pNewVarIndexExpr); };
    ~RedVSIParseTreeVar();

    // inherited
    void                    CalcResult(RedVSIContextInterface* pContext);
    const RedVSILangElement Type(void) const { return RedVSILangElement::ParseVariable(); };

    void             SetVarName(const RedString& cInVarName) { cVarName = cInVarName; };
    const RedString& VarName(void) const                     { return cVarName; };

    //void        SetDetails(RedString& cInVarName,  RedVSIParseTreeInterface*& pInVarIndexExpr);
    //void        GetDetails(RedString& cOutVarName, RedVSIParseTreeInterface*& pOutVarIndexExpr);


    void        AssignValue(RedVSIContextInterface* pContext, RedVariant& result);

private:

    int         FindDataItem(RedVSIContextInterface* pContext, RedType*& pDataItem);

    RedString                  cVarName;
    //RedVSIParseTreeInterface*  pVarIndexExpr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
