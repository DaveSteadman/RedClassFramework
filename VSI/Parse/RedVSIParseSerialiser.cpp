

#include "RedVSIParseSerialiser.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseExpression(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeInterface* pExpr)
{
    if (!pExpr) return;
    
    RedVSILangElement cType = pExpr->Type();
    
    if      (cType.IsParseBinaryOp()) SerialiseBinaryOp(cTokenBuffer, (RedVSIParseTreeBinaryOp*)pExpr);
    else if (cType.IsParseValue())    SerialiseValue(cTokenBuffer, (RedVSIParseTreeVal*)pExpr);
    else if (cType.IsParseVariable()) SerialiseVariable(cTokenBuffer, (RedVSIParseTreeVar*)pExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseBinaryOp(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeBinaryOp* pExpr)
{
    RedVSIParseTreeInterface* pOutLeft;
    RedVSILangElement         cOutOp;
    RedVSIToken               cOpTok;
    RedVSIParseTreeInterface* pOutRight;

    // read the data out of the expression
    pExpr->GetDetails(pOutLeft, cOutOp, pOutRight);

    // write the left side of the equation
    SerialiseExpression(cTokenBuffer, pOutLeft);

    // write the operator   
    if      (cOutOp.IsBinaryOpAssignEqual())          cOpTok.SetPredefined(RedVSIIOElement::SymbolAssignEqual());
    else if (cOutOp.IsBinaryOpAssignPlus())           cOpTok.SetPredefined(RedVSIIOElement::SymbolAssignPlus());
    else if (cOutOp.IsBinaryOpAssignMinus())          cOpTok.SetPredefined(RedVSIIOElement::SymbolAssignMinus());
    else if (cOutOp.IsBinaryOpAssignMultiply())       cOpTok.SetPredefined(RedVSIIOElement::SymbolAssignMultiply());
    else if (cOutOp.IsBinaryOpAssignDivide())         cOpTok.SetPredefined(RedVSIIOElement::SymbolAssignDivide());
    else if (cOutOp.IsBinaryOpCompareEqual())         cOpTok.SetPredefined(RedVSIIOElement::SymbolCompareEqual());
    else if (cOutOp.IsBinaryOpCompareNotEqual())      cOpTok.SetPredefined(RedVSIIOElement::SymbolCompareNotEqual());
    else if (cOutOp.IsBinaryOpCompareGreaterThan())   cOpTok.SetPredefined(RedVSIIOElement::SymbolCompareGreaterThan());
    else if (cOutOp.IsBinaryOpCompareLessThan())      cOpTok.SetPredefined(RedVSIIOElement::SymbolCompareLessThan());
    else if (cOutOp.IsBinaryOpLogicAnd())             cOpTok.SetPredefined(RedVSIIOElement::SymbolLogicAnd());
    else if (cOutOp.IsBinaryOpLogicOr())              cOpTok.SetPredefined(RedVSIIOElement::SymbolLogicOr());
    else if (cOutOp.IsBinaryOpPower())                cOpTok.SetPredefined(RedVSIIOElement::SymbolPower());
    else if (cOutOp.IsBinaryOpPlus())                 cOpTok.SetPredefined(RedVSIIOElement::SymbolPlus());
    else if (cOutOp.IsBinaryOpMinus())                cOpTok.SetPredefined(RedVSIIOElement::SymbolMinus());
    else if (cOutOp.IsBinaryOpMultiply())             cOpTok.SetPredefined(RedVSIIOElement::SymbolMultiply());
    else if (cOutOp.IsBinaryOpDivide())               cOpTok.SetPredefined(RedVSIIOElement::SymbolDivide());

    cTokenBuffer.AppendToken(cOpTok);

    // write the right side of the equation
    SerialiseExpression(cTokenBuffer, pOutRight);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseUnaryOp(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeUnaryOp* pExpr)
{
    RedVSILangElement         cOutOp;
    RedVSIToken               cOpTok;
    RedVSIParseTreeInterface* pOutExpr;

    // read the data out of the expression
    pExpr->GetDetails(cOutOp, pOutExpr);

    // write the operator   
    if      (cOutOp.IsUnaryOpLogicNot())          cOpTok.SetPredefined(RedVSIIOElement::SymbolLogicNot());
    else if (cOutOp.IsUnaryOpMinus())             cOpTok.SetPredefined(RedVSIIOElement::SymbolMinus());

    cTokenBuffer.AppendToken(cOpTok);

    // write the left side of the equation
    SerialiseExpression(cTokenBuffer, pOutExpr);

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseValue(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeVal* pExpr)
{
    // define all the variables we will need
    RedVariant cOutVal;
    RedVSIToken cValTok;
    
    // read the data out of the parse tree node
    cOutVal = pExpr->Value();
    
    // Write the name or number
    if      (cOutVal.Type().IsNum()) cValTok.SetNumber( cOutVal.NumberValue() );
    else if (cOutVal.Type().IsStr()) cValTok.SetName(   cOutVal.StringValue() );
    
    cTokenBuffer.AppendToken(cValTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseSerialiser::SerialiseVariable(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeVar* pExpr)
{
    // define all the variables we will need
    RedString                 cOutVarName;
    //RedVSIParseTreeInterface* pOutVarIndexExpr = REDNULL;
    RedVSIToken               cNameTok;

    // read the data out of the parse tree node
//    pExpr->GetDetails(cOutVarName, pOutVarIndexExpr);

    // write the item name
    cNameTok.SetName(pExpr->VarName());
    cTokenBuffer.AppendToken(cNameTok);
    
//    if (pOutVarIndexExpr)
//    {
//        // write the open brakect for the item index
//        RedVSIToken cBracketTok;
//        cBracketTok.SetPredefined(RedVSIIOElement::SymbolOpenBracket());
//        cTokenBuffer.AppendToken(cBracketTok);
//        
//        // write the item index expression
//        SerialiseExpression(cTokenBuffer, pOutVarIndexExpr);
//        
//        // write the close brakect for the item index
//        cBracketTok.SetPredefined(RedVSIIOElement::SymbolCloseBracket());
//        cTokenBuffer.AppendToken(cBracketTok);
//    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


