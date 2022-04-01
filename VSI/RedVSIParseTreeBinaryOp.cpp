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

#include "RedCoreNamespace.h"

#include "math.h"

#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeVar.h"

#include "RedVSIErrorCodes.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeBinaryOp::RedVSIParseTreeBinaryOp(void)
{
    pLeft = NULL;
    cOp.Init();
    pRight = NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeBinaryOp::RedVSIParseTreeBinaryOp(RedVSIParseTreeInterface* pNewLeft, RedVSILangElement cNewOp, RedVSIParseTreeInterface* pNewRight)
{
    pLeft  = pNewLeft;
    cOp    = cNewOp;
    pRight = pNewRight;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeBinaryOp::~RedVSIParseTreeBinaryOp(void)
{
//    if (pLeft)
//    {
//        delete pLeft;
//        pLeft = NULL;
//    }
//    if (pRight)
//    {
//        delete pRight;
//        pRight = NULL;
//    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeBinaryOp::CalcResult(RedVSIContextRoutine* pContext)
{
    // Get the left/right node results
    RedDataVariant cLeftVal;
    RedDataVariant cRightVal;
    cLeftVal  = pContext->ExprResult(pLeft);
    cRightVal = pContext->ExprResult(pRight);

    // Create the output
    RedDataVariant cRetVal;

    // if the left of the expression is an object, we need an object operator
    //if (cLeftVal.Type().IsObj())
    //{
    //}
    // if the right is an object (when the left isn't) we have an error. 
    //else if (cRightVal.Type().IsObj())
    //{
    //    pContext->Log().AddText(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eParseBinOp_RightOnlyObj));
    //    return;
    //}

    // If we have an assignment operator, process it and return the value
    if (cOp.IsAssignOp())
    {
        // If the left is not a variable, we have an error.
        if (!pLeft->Type().IsParseVariable()) { pContext->Log()->AddText(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eParseBinOp_NotVar)); return; }

        // Calculate the result of the expression
        if      (cOp.IsBinaryOpAssignEqual())     cRetVal = cRightVal;
        else if (cOp.IsBinaryOpAssignPlus())      cRetVal = cLeftVal + cRightVal;
        else if (cOp.IsBinaryOpAssignMinus())     cRetVal = cLeftVal - cRightVal;
        else if (cOp.IsBinaryOpAssignMultiply())  cRetVal = cLeftVal * cRightVal;
        else if (cOp.IsBinaryOpAssignDivide())    cRetVal = cLeftVal / cRightVal;

        // Assign the result to the varable on the left node.
        RedVSIParseTreeVar* pVarLeft = dynamic_cast<RedVSIParseTreeVar*>(pLeft);
        pVarLeft->AssignValue(pContext, cRetVal);
    }

    // Else, perform normal "calculate and return" processing
    else
    {
        if      (cOp.IsBinaryOpPlus())                      cRetVal = cLeftVal + cRightVal;
        else if (cOp.IsBinaryOpMinus())                     cRetVal = cLeftVal - cRightVal;
        else if (cOp.IsBinaryOpMultiply())                  cRetVal = cLeftVal * cRightVal;
        else if (cOp.IsBinaryOpDivide())                    cRetVal = cLeftVal / cRightVal;
        else if (cOp.IsBinaryOpPower())                     cRetVal = CalcPowerOp(cLeftVal, cRightVal);

        else if (cOp.IsBinaryOpCompareNotEqual())           cRetVal.SetValue(RedDataBoolean(cLeftVal != cRightVal));
        else if (cOp.IsBinaryOpCompareEqual())              cRetVal.SetValue(RedDataBoolean(cLeftVal == cRightVal));
        else if (cOp.IsBinaryOpCompareLessThan())           cRetVal.SetValue(RedDataBoolean(cLeftVal <  cRightVal));
        else if (cOp.IsBinaryOpCompareGreaterThan())        cRetVal.SetValue(RedDataBoolean(cLeftVal >  cRightVal));
        else if (cOp.IsBinaryOpCompareLessThanOrEqual())    cRetVal.SetValue(RedDataBoolean(cLeftVal <= cRightVal));
        else if (cOp.IsBinaryOpCompareGreaterThanOrEqual()) cRetVal.SetValue(RedDataBoolean(cLeftVal >= cRightVal));
    }

    // Determine the validity of the outcome, raise an error if the operation
    // didn't produce a valid output.
    if (!cRetVal.IsValid()) { pContext->Log()->AddText(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eParseBinOp_NoResult)); return; }

    // Store the result to quicken future calls
    pContext->SetExprResult(this, cRetVal);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedVSIParseTreeBinaryOp::CalcPowerOp(RedDataVariant cLeftVal, RedDataVariant cRightVal)
{
    RedDataVariant cRetVal;

    if ( (cLeftVal.Type().IsNum()) && (cRightVal.Type().IsNum()) )
    {
        RedDataNumber cLeftNum  = cLeftVal.NumberValue();
        RedDataNumber cRightNum = cRightVal.NumberValue();

        double dblResult = pow(cLeftNum.DoubleValue(), cRightNum.DoubleValue());

        RedDataNumber RedResultNum = dblResult;
        cRetVal.SetValue(RedResultNum);
    }

    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeBinaryOp::GetDetails(RedVSIParseTreeInterface*& pOutLeft, RedVSILangElement& cOutOp, RedVSIParseTreeInterface*& pOutRight)
{
    pOutLeft  = pLeft;
    cOutOp    = cOp;
    pOutRight = pRight;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

