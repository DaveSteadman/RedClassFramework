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

#include "RedVSICmdNew.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Fundamental Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::RedVSICmdNew(void)
{
    // this object's attributes
    cType.Init();
    cLoc.Init();
    cName.Init();
    pInitExpr = REDNULL;

    // parents attributes
    SetNextCmd(0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::RedVSICmdNew(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, const RedString& cInName, RedVSIParseTreeInterface* pInInitExpr)
{
    SetDetails(cInType, cInLoc, cInName, pInInitExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::~RedVSICmdNew(void)
{
    if (pInitExpr != REDNULL)
    {
        delete pInitExpr;
        pInitExpr = REDNULL;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RedVSICmdInterface inherited routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pInitExpr)
        pContext->QueueExpr(pInitExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::Execute(RedVSIContextInterface* pContext)
{
    RedType* pData = 0;

    // Call the context with the details, so it can create the new data item.
    // Pointer to new item returned
    pData = pContext->CreateDataItem(cLoc, cType, cName);

    // Check we created a data item
    if (pData == REDNULL)
        throw;

    // if we have an initialisation expression for the data item
    if (pInitExpr != REDNULL)
    {
        RedVariant cInitExprResult = pContext->ExprResult(pInitExpr);

        // if the type of the new variable and the expression don't match, raise an error
        if (!cInitExprResult.ExportTo(pData))
        {
            pContext->Log().AddErrorEvent("New Command Execution: Unable to export expression result into variable");
            return;
        }
    }
    
    // queue the next command, we are done with this one
    pContext->QueueCommand( NextCmd() );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Wholesale access/assign operations
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::SetDetails(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, const RedString& cInName, RedVSIParseTreeInterface* pInInitExpr)
{
    cType     = cInType;
    cLoc      = cInLoc;
    cName     = cInName;
    pInitExpr = pInInitExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::GetDetails(RedVSILangElement& cOutType, RedVSILangElement& cOutLoc, RedString& cOutName, RedVSIParseTreeInterface*& pOutInitExpr) const
{
    cOutType     = cType;
    cOutLoc      = cLoc;
    cOutName     = cName;
    pOutInitExpr = pInitExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


