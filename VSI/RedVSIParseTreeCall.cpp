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

#include "RedVSIParseTreeCall.h"

#include "RedVSIContextThread.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructors
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeCall::~RedVSIParseTreeCall()
{
    if (pParamList != NULL)
    {
        if (!pParamList->IsEmpty())
            pParamList->DelAll();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeCall::SetDetails(const RedDataString& cInObjName, const RedDataString& cInClassName, const RedDataString& cInFuncName, RedVSIParseList*& pInParamList)
{
    cObjectName = cInObjName;
    cClassName  = cInClassName;
    cFuncName   = cInFuncName;
    pParamList  = pInParamList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeCall::GetDetails(RedDataString& cOutObjName, RedDataString& cOutClassName, RedDataString& cOutFuncName, RedVSIParseList*& pOutParamList)
{
    cOutObjName   = cObjectName;
    cOutClassName = cClassName;
    cOutFuncName  = cFuncName;
    pOutParamList = pParamList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// The call to calculate a routine call results in the creation of a new layer on the stack.
// The execution then has to go back to the thread, to realise it needs to be a level higher
// start processing the new routine's commands.

void RedVSIParseTreeCall::CalcResult(RedVSIContextInterface* pContext)
{
    // The params results list
    RedVSIRoutineCallInterface cCall;

    // Assign the object anbd class information, even if its blank
    cCall.SetupCall(cClassName, cObjectName, cFuncName);

    // loop through the params list to calculate any we don't have a result for
    RedVSIParseListIterator cParseIt(pParamList);
    cParseIt.First();
    while(!cParseIt.IsDone())
    {
        // get the current parameter
        RedVSIParseTreeInterface* pCurrParam = cParseIt.CurrentItem();

        RedDataVariant r = pContext->ExprResult(pCurrParam);

        // add the result of the expr to the param list
        cCall.AddParam(pContext->ExprResult(pCurrParam));
        
        // move onto the next parameter
        cParseIt.Next();
    }

    // Call the context to setup the new routine call
    pContext->SetupRoutineCall(cCall);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

