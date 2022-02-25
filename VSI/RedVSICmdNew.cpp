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
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Fundamental Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::RedVSICmdNew(void)
{
    // This object's attributes
    cType.Init();
    cLoc.Init();
    cName.Init();
    pDataInitExpr = NULL;

    // Parents attributes
    SetNextCmd(NULL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::RedVSICmdNew(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, const RedDataString& cInName, RedVSIParseTreeInterface* pInRecordIndexExpr, RedVSIParseTreeInterface* pInInitExpr)
{
    SetDetails(cInType, cInLoc, cInName, pInRecordIndexExpr, pInInitExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdNew::~RedVSICmdNew(void)
{
    if (pDataInitExpr != NULL)
    {
        delete pDataInitExpr;
        pDataInitExpr = NULL;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RedVSICmdInterface inherited routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::QueueExpr(RedVSIContextInterface* pContext)
{
    if (pDataInitExpr)
        pContext->QueueExpr(pDataInitExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::Execute(RedVSIContextInterface* pContext)
{
    RedType* pData = 0;

    // Call the context with the details, so it can create the new data item.
    // Pointer to new item returned
    pData = pContext->CreateDataItem(cLoc, cType, cName);

    // Check we created a data item
    if (pData == NULL)
    {
        pContext->Log()->AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eNew_CreateError));
        return;
    }
    
    // If we have an initialisation expression for the data item
    if (pDataInitExpr != NULL)
    {
        RedDataVariant cInitExprResult = pContext->ExprResult(pDataInitExpr);

        // If the type of the new variable and the expression don't match, raise an error
        if (!cInitExprResult.ExportTo(pData))
        {
            pContext->Log()->AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eNew_ResultTypeMismatch));
            return;
        }
    }
    
    // Queue the next command, we are done with this one
    pContext->QueueCommand( NextCmd() );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Wholesale access/assign operations
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::SetDetails(const RedVSILangElement& cInType, const RedVSILangElement& cInLoc, const RedDataString& cInName, RedVSIParseTreeInterface* pInRecordIndexExpr, RedVSIParseTreeInterface* pInInitExpr)
{
    cType            = cInType;
    cLoc             = cInLoc;
    cName            = cInName;
    pRecordIndexExpr = pInRecordIndexExpr;
    pDataInitExpr    = pInInitExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdNew::GetDetails(RedVSILangElement& cOutType, RedVSILangElement& cOutLoc, RedDataString& cOutName, RedVSIParseTreeInterface* pOutRecordIndexExpr, RedVSIParseTreeInterface*& pOutInitExpr) const
{
    cOutType            = cType;
    cOutLoc             = cLoc;
    cOutName            = cName;
    pOutRecordIndexExpr = pRecordIndexExpr;
    pOutInitExpr        = pDataInitExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


