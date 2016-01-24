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

void RedVSIParseTreeUnaryOp::CalcResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete)
{
/*
    // First check for previous execution and a return value
    RedVariant cRetVal = cContext.GetCmdDataItem(this, cCalcResultRetValName);
    if (cRetVal.IsValid())
    {
        cResult   = cRetVal;
        iComplete = 1;
    }
    else
    {
        pExpr->CalcResult(cContext, cExprVal, iExprComplete);
    
        if      (cOp.IsMinusOp())      CalcNegateResult(cContext, cResult, iComplete);
        else if (cOp.IsAddrOfItemOp()) CalcAddrOfItemResult(cContext, cResult, iComplete);
        else if (cOp.IsItemAtAddrOp()) CalcItemAtAddrResult(cContext, cResult, iComplete);

        // If we have a valid result, put it in the temporary store in case its needed again
        if (iComplete)
            cContext.SetCmdDataItem(this, cCalcResultRetValName, cResult);
    }
*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::GetDetails(RedVSILangElement& cOutOp, RedVSIParseTreeInterface*& pNodeExpr)
{
    cOutOp    = cOp;
    pNodeExpr = pExpr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::CalcNegateResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete)
{
    // first, initialise the outputs
    cResult.Init();
    iComplete = 0;

    RedVariant cExprVal; 
    int        iExprComplete =0;

    if (pExpr)
    {
        //pExpr->CalcResult(cContext, cExprVal, iExprComplete);

        if (iExprComplete)
        {
            // Check the expression gave us a valid value we can negate
            if (cExprVal.Type().IsNum())
            {
                cResult = cExprVal.NumberValue() * kNumberMinusOne;
                iComplete = 1;
            }
            else
                cContext.Log().AddErrorEvent("RedVSIParseTreeUnaryOp::CalcNegateResult");
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::CalcAddrOfItemResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete)
{
/*
    // first, initialise the outputs
    cResult.Init();
    iComplete = 0;

    // If we have an expression which is a variable (can't get an address from a 
    // value calculated in  an expression, so here we aren't executing anything)
    if ( (pExpr) && (pExpr->Type().IsVariable()) )
    {
        // Get the variable, then its name.
        RedVSIParseTreeVar* pExprVar = (RedVSIParseTreeVar*)pExpr;
        if (!pExprVar) { LogError(cContext, RedVSILangErrorCodes::eGen_NoCode); return; }
        //RedString cVarName = ->GetVarName();

        // Get the address object if we correctly obtained the variable
        CCoreData* pVar = cContext.GetDataItem(cVarName);
        if (!pVar) { LogError(cContext, RedVSILangErrorCodes::eGen_NoCode); return ; }

        // setup the positive result
        CCoreAddress* pVarAddr = (CCoreAddress*)pVar->GetAddressObj();
        cResult = *pVarAddr;
        delete pVarAddr;
        iComplete = 1;
    }
    else
        LogError(cContext, RedVSILangErrorCodes::eGen_NoCode);
*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeUnaryOp::CalcItemAtAddrResult(RedVSIContextInterface& cContext, RedVariant& cResult, int& iComplete)
{
/*
    // first, initialise the outputs
    cResult.Init();
    iComplete = 0;

    RedVariant cExprVal; 
    int       iExprComplete =0;

    // If we have a valid expression
    if (pExpr)
    {
        pExpr->CalcResult(cContext, cExprVal, iExprComplete);

        // if the expression is complete and resulting in an address, assign the 
        // referenced object to the output.
        if ( (iExprComplete) && (cExprVal.IsAddress()) )
        {
            CCoreAddress cAddr = cExprVal.GetAddress();
            cResult.Import( cAddr.GetAddressVal() );
            iComplete = 1;
        }
        else
            LogError(cContext, RedVSILangErrorCodes::eGen_NoCode);
    }
    else
        LogError(cContext, RedVSILangErrorCodes::eGen_NoCode);
*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedVSIParseTreeVar::LogError(RedVSIContextInterface& cContext, RedVSILangErrorCodes::TErrorCodes eErr)
//{
/*
    RedString cErrText = RedVSILangErrorCodes::GetErrorString(eErr);

    cContext.GetAnalysis()->AddErrorEvent§(cErrText);
*/
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



