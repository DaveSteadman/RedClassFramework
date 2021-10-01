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

#include "RedVSICmdLoadCode.h"

#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdLoadCode::RedVSICmdLoadCode(void)
{
    // This object's attributes
    pLoadPathExpr = NULL;

    // Parents attributes
    SetNextCmd(NULL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdLoadCode::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pLoadPathExpr)
        pContext->QueueExpr(pLoadPathExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdLoadCode::Execute(RedVSIContextInterface* pContext)
{
    // Get the result of the commands expression
    RedVariant cExprResult = pContext->ExprResult(pLoadPathExpr);

    // Get a string representation of the value
    pContext->Log()->AddText(cExprResult.StringValue());

    if (!RedIOHandler::FileExists(cExprResult.StringValue()))
    {
        pContext->Log()->AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eLoadCode_NoFile));
        return;
    }

    // Load the code into an available thread context
    if (pContext->pThreadContextRecord != NULL)
    {
        RedVSILibFactory libFact(pContext->pThreadContextRecord->pCodeLib);
    }
    
    // Expression will have been evaluated prior to the command,
    // so any actions already performed. Just queue up the next 
    // command.
    pContext->QueueCommand(NextCmd());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
