

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

