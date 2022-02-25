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
    RedVSIParseTreeCall(void) { pParamList = NULL; };
    ~RedVSIParseTreeCall(void);

    RedVSILangElement Type(void) const { return RedVSILangElement::ParseFuncCall(); };

    void SetDetails(const RedDataString& cInObjectName,  const RedDataString& cInClassName, const RedDataString& cInFuncName,  RedVSIParseList*& pInParamList);
    void GetDetails(      RedDataString& cOutObjectName,       RedDataString& cOutClassName,      RedDataString& cOutFuncName, RedVSIParseList*& pOutParamList);

    // Operation
    void CalcResult(RedVSIContextInterface* pContext);

private:

    // The static representation of the function-call parse-tree node is that it has a name and links to
    // parameters that are sub parse-tree nodes. On execution, the param list will become a list of variants.
    RedDataString          cObjectName;
    RedDataString          cClassName;
    RedDataString          cFuncName;
    RedVSIParseList*   pParamList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



