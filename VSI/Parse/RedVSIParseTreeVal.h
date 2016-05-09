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
#include "RedVSIContextInterface.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseTreeVal : public RedVSIParseTreeInterface
{
public:

    RedVSIParseTreeVal(void)                      { Init(); };
    RedVSIParseTreeVal(RedVariant cNewVal)        { SetValue(cNewVal); };
    ~RedVSIParseTreeVal(void)                     { };
    // Inherited RedType
    void              Init(void)            { cVal.Init(); };
    RedVSILangElement Type(void) const      { return RedVSILangElement::ParseValue(); };
	
    // Query
    const RedVariant Value(void) const            { return cVal;  };
    void             SetValue(RedVariant& cInVal) { cVal = cInVal; };

    // Inherited RedVSIParseTreeInterface
    void CalcResult(RedVSIContextInterface* pContext) { pContext->SetExprResult(this, cVal); };

private:
    RedVariant cVal;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


