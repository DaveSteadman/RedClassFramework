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

void RedVSIParseTreeVar::CalcResult(RedVSIContextInterface* pContext)
{
    RedVariant result;

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

void RedVSIParseTreeVar::AssignValue(RedVSIContextInterface* pContext, RedVariant& result)
{
    RedType* pVarObject = REDNULL;
    if (!pContext->FindDataItem(cVarName, pVarObject))
        throw;

//    RedType* pDataItem =0;
//
//    if (!FindDataItem(pContext, pDataItem)) 
//    { 
//        //RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_NoVar);
//        throw;
//    }
    if (!result.ExportTo(pVarObject))
    {
    //    RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_NoAssign);
        throw;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedVSIParseTreeVar::GetDetails(RedString& cOutVarName, RedVSIParseTreeInterface*& pOutVarIndexExpr)
//{
//    cOutVarName      = cVarName;
//    pOutVarIndexExpr = pVarIndexExpr;
//}
//
//// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedVSIParseTreeVar::SetDetails(RedString& cInVarName, RedVSIParseTreeInterface*& pInVarIndexExpr)
//{
//    cVarName      = cInVarName;
//    pVarIndexExpr = pInVarIndexExpr;
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIParseTreeVar::FindDataItem(RedVSIContextInterface* pContext, RedType*& pDataItem)
{
/*
    RedVariant RedResult;
    RedVariant cVarIndex;

    // get the data item
    RedType* pStartItem = 0;
    if (!pContext->FindDataItem(cVarName, pStartItem)) return 0;

    // if we have an expression for an array index 
    if (pVarIndexExpr)
    {
        // get the array index value
        cVarIndex = pContext->GetExprResult(pVarIndexExpr);
        
        // validate we have an array and an index number
        if (!pStartItem->Type().IsArray()) { RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_NotArray); }
        if (!cVarIndex.Type().IsNum())     { RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_IndexNotInteger); }
       
        CDataArray* pArray = (CDataArray*)pStartItem;
        CDataNumber cIndex = cVarIndex.GetNumber();
        
        // validate the index number is an integer
        if (!cIndex.IsInteger()) { RedVSIErrorCodes::Log(pContext->GetAnalysis(), RedVSIErrorCodes::eParseVar_IndexNotInteger); }
        
        // get the item out of the array
        RedType* pArrayDataItem = 0;
        pArray->Find(cIndex.GetInteger(), pArrayDataItem);
        
        // assign the result for an array
        pDataItem = pArrayDataItem;
    }
    else
    {
        // assign the result for a single value
        pDataItem = pStartItem;
    }
*/
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

