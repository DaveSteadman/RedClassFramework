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

#include "RedVSIParseTreeVar.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeVar::~RedVSIParseTreeVar()
{
//    if (pVarIndexExpr)
//    {
//        //delete pVarIndexExpr;
//        //pVarIndexExpr = 0;
//    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeVar::CalcResult(RedVSIContextRoutine* pContext)
{
    RedDataVariant result;

    // get the data item
    RedType* pDataItem = 0;
    if (!pContext->FindDataItem(cVarName, pDataItem))
    {
        throw;
        //RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_NoVar);
        return;
    }

    // copy out the value of the data item    
    result = pDataItem;

    // assign the result to the context
    pContext->SetExprResult(this, result);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeVar::AssignValue(RedVSIContextRoutine* pContext, RedDataVariant& result)
{
    RedType* pVarObject = NULL;
    if (!pContext->FindDataItem(cVarName, pVarObject))
        throw;

    if (!result.ExportTo(pVarObject))
        throw;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

