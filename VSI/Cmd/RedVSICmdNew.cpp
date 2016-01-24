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
    pInitExpr = 0;

    // parents attributes
    SetNextCmd(0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::SetDetails(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, RedString cInName, RedVSIParseTreeInterface* pInInitExpr)
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

void RedVSICmdNew::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pInitExpr)
        pContext->QueueExpr(pInitExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::Execute(RedVSIContextInterface* pContext)
{
    RedType* pData = 0;

    // if we have an initialisation expression for the data item
    if ( pInitExpr )
    {
        RedVariant cInitExprResult = pContext->GetExprResult(pInitExpr);

        // create the new data item
        pData = pContext->CreateDataItem(cLoc, cType, cName);

        // if the type of the new variable and the expression don't match, raise an error
        if (!cInitExprResult.ExportTo(pData))
        {
            //RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eNew_ResultTypeMismatch);
            return;
        }
    }
    // else, we have no initialisation expression to deal with, so just create the data item and move on.
    else
    {
        // create the new data item
        pData = pContext->CreateDataItem(cLoc, cType, cName);
    }
    
    // queue the next command, we are done with this one
    pContext->QueueCommand( NextCmd() );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




