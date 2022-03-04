// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedVSIParseTreeUnaryOp.h"
#include "RedVSIParseTreeVar.h"
#include "RedLogEvent.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeUnaryOp::RedVSIParseTreeUnaryOp(RedVSILangElement cNewOp, RedVSIParseTreeInterface* pNewExpr)
{
    pExpr = pNewExpr;
    cOp   = cNewOp;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeUnaryOp::~RedVSIParseTreeUnaryOp(void)
{
    if (pExpr) 
    {
        delete pExpr;
        pExpr = 0;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::CalcResult(RedVSIContextInterface* pContext)
{
    if (cOp.IsUnaryOpMinus()) CalcNegateResult(pContext);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::GetDetails(RedVSILangElement& cOutOp, RedVSIParseTreeInterface*& pNodeExpr)
{
    cOutOp    = cOp;
    pNodeExpr = pExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::CalcNegateResult(RedVSIContextInterface* pContext)
{
    // First check for previous execution and a return value
    RedDataVariant cInputExprVal;
    cInputExprVal = pContext->ExprResult(pExpr);

    if (cInputExprVal.IsValid())
    {
        if (cInputExprVal.Type().IsNum())
        {
            RedDataVariant cRetVal;
            RedDataNumber cRetNum;
            cRetNum = cInputExprVal.NumberValue() * -1;
            cRetVal = cRetNum;

            pContext->SetExprResult(this, cRetVal);
        }

        else if (cInputExprVal.Type().IsBool())
        {
            RedDataVariant cRetVal;
            RedDataBoolean cB = cInputExprVal.BoolValue();
            cB.Invert();

            cRetVal = cB;
            pContext->SetExprResult(this, cRetVal);
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



