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

#include "RedVSIParseSerialiser.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseExpression(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeInterface* pExpr)
{
    if (!pExpr) return;
    
    RedVSILangElement cType = pExpr->Type();
    
    if      (cType.IsParseBinaryOp()) SerialiseBinaryOp(cTokenBuffer, dynamic_cast<RedVSIParseTreeBinaryOp*>(pExpr));
    else if (cType.IsParseValue())    SerialiseValue   (cTokenBuffer, dynamic_cast<RedVSIParseTreeVal*>(pExpr));
    else if (cType.IsParseVariable()) SerialiseVariable(cTokenBuffer, dynamic_cast<RedVSIParseTreeVar*>(pExpr));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseBinaryOp(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeBinaryOp* pExpr)
{
    RedVSIParseTreeInterface* pOutLeft;
    RedVSILangElement         cOutOp;
    RedToken               cOpTok;
    RedVSIParseTreeInterface* pOutRight;

    // read the data out of the expression
    pExpr->GetDetails(pOutLeft, cOutOp, pOutRight);

    // write the left side of the equation
    SerialiseExpression(cTokenBuffer, pOutLeft);

    // write the operator   
    if      (cOutOp.IsBinaryOpAssignEqual())          cOpTok.SetPredefined(RedTokenPredefType::SymbolAssignEqual());
    else if (cOutOp.IsBinaryOpAssignPlus())           cOpTok.SetPredefined(RedTokenPredefType::SymbolAssignPlus());
    else if (cOutOp.IsBinaryOpAssignMinus())          cOpTok.SetPredefined(RedTokenPredefType::SymbolAssignMinus());
    else if (cOutOp.IsBinaryOpAssignMultiply())       cOpTok.SetPredefined(RedTokenPredefType::SymbolAssignMultiply());
    else if (cOutOp.IsBinaryOpAssignDivide())         cOpTok.SetPredefined(RedTokenPredefType::SymbolAssignDivide());
    else if (cOutOp.IsBinaryOpCompareEqual())         cOpTok.SetPredefined(RedTokenPredefType::SymbolCompareEqual());
    else if (cOutOp.IsBinaryOpCompareNotEqual())      cOpTok.SetPredefined(RedTokenPredefType::SymbolCompareNotEqual());
    else if (cOutOp.IsBinaryOpCompareGreaterThan())   cOpTok.SetPredefined(RedTokenPredefType::SymbolCompareGreaterThan());
    else if (cOutOp.IsBinaryOpCompareLessThan())      cOpTok.SetPredefined(RedTokenPredefType::SymbolCompareLessThan());

    else if (cOutOp.IsBinaryOpLogicAnd())             cOpTok.SetPredefined(RedTokenPredefType::SymbolLogicAnd());
    else if (cOutOp.IsBinaryOpLogicOr())              cOpTok.SetPredefined(RedTokenPredefType::SymbolLogicOr());

    else if (cOutOp.IsBinaryOpPlus())                 cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorPlus());
    else if (cOutOp.IsBinaryOpMinus())                cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorMinus());
    else if (cOutOp.IsBinaryOpMultiply())             cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorMultiply());
    else if (cOutOp.IsBinaryOpDivide())               cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorDivide());
    else if (cOutOp.IsBinaryOpPower())                cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorPower());

    cTokenBuffer.AppendToken(cOpTok);

    // write the right side of the equation
    SerialiseExpression(cTokenBuffer, pOutRight);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseUnaryOp(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeUnaryOp* pExpr)
{
    RedVSILangElement         cOutOp;
    RedToken               cOpTok;
    RedVSIParseTreeInterface* pOutExpr;

    // read the data out of the expression
    pExpr->GetDetails(cOutOp, pOutExpr);

    // write the operator   
    if      (cOutOp.IsUnaryOpLogicNot())  cOpTok.SetPredefined(RedTokenPredefType::SymbolLogicNot());
    else if (cOutOp.IsUnaryOpMinus())     cOpTok.SetPredefined(RedTokenPredefType::SymbolOperatorMinus());

    cTokenBuffer.AppendToken(cOpTok);

    // write the left side of the equation
    SerialiseExpression(cTokenBuffer, pOutExpr);

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseValue(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeVal* pExpr)
{
    // define all the variables we will need
    RedDataVariant cOutVal;
    RedToken cValTok;
    
    // read the data out of the parse tree node
    cOutVal = pExpr->Value();
    
    // Write the name or number
    if (cOutVal.Type().IsNum()) 
        cValTok.SetNumber(cOutVal.StringValue(), cOutVal.NumberValue());
    else if (cOutVal.Type().IsStr()) 
        cValTok.SetName(cOutVal.StringValue() );
    
    cTokenBuffer.AppendToken(cValTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseVariable(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeVar* pExpr)
{
    // define all the variables we will need
    RedDataString                 cOutVarName;
    //RedVSIParseTreeInterface* pOutVarIndexExpr = NULL;
    RedToken               cNameTok;

    // read the data out of the parse tree node
//    pExpr->GetDetails(cOutVarName, pOutVarIndexExpr);

    // write the item name
    cNameTok.SetName(pExpr->VarName());
    cTokenBuffer.AppendToken(cNameTok);
    
//    if (pOutVarIndexExpr)
//    {
//        // write the open brakect for the item index
//        RedToken cBracketTok;
//        cBracketTok.SetPredefined(RedTokenPredefType::SymbolOpenBracket());
//        cTokenBuffer.AppendToken(cBracketTok);
//        
//        // write the item index expression
//        SerialiseExpression(cTokenBuffer, pOutVarIndexExpr);
//        
//        // write the close brakect for the item index
//        cBracketTok.SetPredefined(RedTokenPredefType::SymbolCloseBracket());
//        cTokenBuffer.AppendToken(cBracketTok);
//    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


