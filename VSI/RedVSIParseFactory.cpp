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

#include "RedVSIParseFactory.h"
#include "RedVSIParseTreeVar.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeCall.h"

#include "RedVSIErrorCodes.h"

#include "RedToken.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::ConstructAssignExpr(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    return RedVSIParseFactory::RunExprAssignCompetition(cInputBuffer, log);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::ConstructStatementExpr(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    return RedVSIParseFactory::RunCompareExprCompetition(cInputBuffer, log);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::ConstructValueExpr(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    return RedVSIParseFactory::RunSumExprCompetition(cInputBuffer, log);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private Operations
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunExprAssignCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = 0;

    // Read the left hand expression item.
    RedVSIParseTreeInterface* pLeft = RunCompareExprCompetition(cInputBuffer, log);
    if (pLeft==0) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                        iOpFound = 1;
    RedVSIParseTreeInterface*  pRight   = 0;
    RedVSIParseTreeBinaryOp*   pCurrOp  = 0;
    RedVSIParseTreeBinaryOp*   pPrevOp  = 0;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( (cOp.Predef().IsAssignOpSymbol()) )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            if      (cOp.Predef().IsSymbolAssignEqual())    pCurrOp->SetOp(RedVSILangElement::BinaryOpAssignEqual());
            else if (cOp.Predef().IsSymbolAssignPlus())     pCurrOp->SetOp(RedVSILangElement::BinaryOpAssignPlus());
            else if (cOp.Predef().IsSymbolAssignMinus())    pCurrOp->SetOp(RedVSILangElement::BinaryOpAssignMinus());
            else if (cOp.Predef().IsSymbolAssignDivide())   pCurrOp->SetOp(RedVSILangElement::BinaryOpAssignDivide());
            else if (cOp.Predef().IsSymbolAssignMultiply()) pCurrOp->SetOp(RedVSILangElement::BinaryOpAssignMultiply());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == 0) 
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunCompareExprCompetition(cInputBuffer, log);
            if (pRight)
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = 0; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunCompareExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = 0;

    // Read the left hand expression item.
    RedVSIParseTreeInterface* pLeft = RunLogicExprCompetition(cInputBuffer, log);
    if (pLeft==0) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                        iOpFound = 1;
    RedVSIParseTreeInterface*  pRight   = 0;
    RedVSIParseTreeBinaryOp*   pCurrOp  = 0;
    RedVSIParseTreeBinaryOp*   pPrevOp  = 0;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( (cOp.Predef().IsCompareOpSymbol()) )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            if      (cOp.Predef().IsSymbolCompareEqual())        pCurrOp->SetOp(RedVSILangElement::BinaryOpCompareEqual());
            else if (cOp.Predef().IsSymbolCompareNotEqual())     pCurrOp->SetOp(RedVSILangElement::BinaryOpCompareNotEqual());
            else if (cOp.Predef().IsSymbolCompareGreaterThan())  pCurrOp->SetOp(RedVSILangElement::BinaryOpCompareGreaterThan());
            else if (cOp.Predef().IsSymbolCompareLessThan())     pCurrOp->SetOp(RedVSILangElement::BinaryOpCompareLessThan());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == 0) 
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunLogicExprCompetition(cInputBuffer, log);
            if (pRight)
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = 0; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunLogicExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = 0;

    // Read the left hand expression item.
    RedVSIParseTreeInterface* pLeft = RunSumExprCompetition(cInputBuffer, log);
    if (pLeft==0) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                          iOpFound = 1;
    RedVSIParseTreeInterface*    pRight   = 0;
    RedVSIParseTreeBinaryOp*     pCurrOp  = 0;
    RedVSIParseTreeBinaryOp*     pPrevOp  = 0;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( (cOp.Predef().IsLogicOpSymbol()) )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            if      (cOp.Predef().IsSymbolLogicAnd()) pCurrOp->SetOp(RedVSILangElement::BinaryOpLogicAnd());
            else if (cOp.Predef().IsSymbolLogicOr())  pCurrOp->SetOp(RedVSILangElement::BinaryOpLogicOr());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == 0) 
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunSumExprCompetition(cInputBuffer, log);
            if (pRight)
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = 0; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunSumExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = NULL;

    // Read the left hand expression item.
    RedVSIParseTreeInterface* pLeft = RunMultiExprCompetition(cInputBuffer, log);
    if (pLeft==NULL) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                       iOpFound = 1;
    RedVSIParseTreeInterface* pRight   = NULL;
    RedVSIParseTreeBinaryOp*  pCurrOp  = NULL;
    RedVSIParseTreeBinaryOp*  pPrevOp  = NULL;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( (cOp.Predef().IsSymbolOperatorPlus()) || (cOp.Predef().IsSymbolOperatorMinus()) )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            if      (cOp.Predef().IsSymbolOperatorPlus())  pCurrOp->SetOp(RedVSILangElement::BinaryOpPlus());
            else if (cOp.Predef().IsSymbolOperatorMinus()) pCurrOp->SetOp(RedVSILangElement::BinaryOpMinus());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == NULL)
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunMultiExprCompetition(cInputBuffer, log);
            if (pRight) 
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = NULL; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunMultiExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = 0;

    // Read the left hand expression item. Any errors already reported.
    RedVSIParseTreeInterface* pLeft = RunPowExprCompetition(cInputBuffer, log);
    if (pLeft==0) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                        iOpFound = 1;
    RedVSIParseTreeInterface*  pRight   = 0;
    RedVSIParseTreeBinaryOp*   pCurrOp  = 0;
    RedVSIParseTreeBinaryOp*   pPrevOp  = 0;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( (cOp.Predef().IsSymbolOperatorMultiply()) || (cOp.Predef().IsSymbolOperatorDivide()) )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            if      (cOp.Predef().IsSymbolOperatorMultiply()) 
                pCurrOp->SetOp(RedVSILangElement::BinaryOpMultiply());
            else if (cOp.Predef().IsSymbolOperatorDivide())   
                pCurrOp->SetOp(RedVSILangElement::BinaryOpDivide());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == 0) 
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunPowExprCompetition(cInputBuffer, log);
            if (pRight)
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = 0; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunPowExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Top Element, returned to the caller
    RedVSIParseTreeInterface* pTopElem = 0;

    // Read the left hand expression item. Any errors will already have been reported.
    RedVSIParseTreeInterface* pLeft = RunItemExprCompetition(cInputBuffer, log);
    if (pLeft==0) { return NULL; }
    pTopElem = pLeft;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int                       iOpFound = 1;
    RedVSIParseTreeInterface* pRight   = NULL;
    RedVSIParseTreeBinaryOp*  pCurrOp  = NULL;
    RedVSIParseTreeBinaryOp*  pPrevOp  = NULL;

    while ( (iOpFound) && (!log.ContainsError()) )
    {
        // Read the operator
        RedToken cOp = cInputBuffer.GetToken();
        if ( cOp.Predef().IsSymbolOperatorPower() )
        {
            // Create the operator object
            pCurrOp = new RedVSIParseTreeBinaryOp();
            pCurrOp->SetOp(RedVSILangElement::BinaryOpPower());

            // shuffle nodes to accomodate the new operator
            pTopElem = pCurrOp;
            if (pPrevOp == 0) 
                pCurrOp->SetLeftChild(pLeft);
            else
                pCurrOp->SetLeftChild(pPrevOp);

            // Read the new right hand expression element
            pRight = RunItemExprCompetition(cInputBuffer, log);
            if (pRight) 
                pCurrOp->SetRightChild(pRight);

            // copy the current operator ready for any subsequent iteration
            pPrevOp = pCurrOp;
        }
        else
        {
            iOpFound = 0;
            cInputBuffer.SetTokenIndexBackOne();
        }
    } 

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // properly delete any new object on an error
    if ( (log.ContainsError()) && (pTopElem!=0) ) { delete pTopElem; pTopElem = 0; }

    return pTopElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunItemExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    RedVSIParseTreeInterface* pEntry = NULL;

    // Record the start position in the competition, so we can reset it when we don't get a match
    int iCompStartPos = cInputBuffer.GetTokenIndex();
    int iCurrEntry = 1;

    bool runloop = true;

    // Loop until we have an entity or an error
    while ( (pEntry == NULL) && (!log.ContainsError()) && (runloop == true) )
    {
        // Reset the comp start position
        cInputBuffer.SetTokenIndex(iCompStartPos);

        // Attempt to input an entity
        switch(iCurrEntry)
        {
        case 1: pEntry = RunSubExprCompetition     (cInputBuffer, log); break;
        case 2: pEntry = RunExternalCallCompetition(cInputBuffer, log); break;
        case 3: pEntry = RunInternalCallCompetition(cInputBuffer, log); break;
        case 4: pEntry = RunValueCompetition       (cInputBuffer, log); break;
        case 5: pEntry = RunVariableCompetition    (cInputBuffer, log); break;

        // When the counter has incremented past all the entrants, we will never find
        // a match, so setup an exit.
        default:
            {
                runloop = false;
                cInputBuffer.SetTokenIndex(iCompStartPos);
            }
            break;
        }

        // Move counter on for next iteration
        iCurrEntry++;
    }

    // Mop-up. If we have an entry and an error, delete the entity.
    if ( (pEntry != NULL) && (log.ContainsError()) ) { delete pEntry; pEntry = NULL; }
    
    return pEntry;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunSubExprCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    RedToken cTok = cInputBuffer.GetToken();

    if (cTok.Predef().IsSymbolBracketOpen())
    {
        // Read the sub expression
        RedVSIParseTreeInterface* pSubExpr = RunCompareExprCompetition(cInputBuffer, log);
        if (!pSubExpr)
        {
            log.AddText(cTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_SubExpr_NoExpr));
            return 0;
         }
        
        // Ensure the expression ends with a close bracket
        cTok = cInputBuffer.GetToken();
        if (!cTok.Predef().IsSymbolBracketClose())
        {
            log.AddText(cTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_SubExpr_NoExprEnd));
            return 0;
        }
        return pSubExpr;
    }

    // Return valid zero
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunValueCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    RedToken cTok = cInputBuffer.GetToken();
  
    if (IsValueToken(cTok))
    {
        RedDataVariant cNodeVal;
        if      (cTok.Type().IsNumber())        cNodeVal = cTok.Number();
        else if (cTok.Type().IsStringLiteral()) cNodeVal = cTok.Text();
        else if (cTok.Predef().IsBoolKeyword())
        {
            if      (cTok.Predef().IsKeywordTrue())  cNodeVal = kBoolTRUE;
            else if (cTok.Predef().IsKeywordFalse()) cNodeVal = kBoolFALSE;
        }

        RedVSIParseTreeVal* pParseValNode = new RedVSIParseTreeVal(cNodeVal);
        
        return pParseValNode;
    }
    
    // return valid zero
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunVariableCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    RedToken cTok = cInputBuffer.GetToken();

    if (IsVariableToken(cTok))
    {
        // Data to go into the constructor (name already checked)
        RedDataString                 cVarName   = cTok.Text();
        RedVSIParseTreeInterface* pIndexExpr = NULL;
    
        // check for an array index after the variable name
        cTok = cInputBuffer.GetToken();
        if (cTok.Predef().IsSymbolBracketOpenSquare())
        {
            // Read the array index expression
            pIndexExpr = RunCompareExprCompetition(cInputBuffer, log);
            if (!pIndexExpr)
            {
                log.AddText(cTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_Var_NoArrayExpr));
                return NULL;
            }

            // read the closing array bracket, which isn't part of the expression.
            cTok = cInputBuffer.GetToken();
            if (!cTok.Predef().IsSymbolBracketCloseSquare())
            {
                log.AddText(cTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_Var_NoArrayExprEnd));
                return NULL;
            }
        }  
        else
        {
            // put back token if its not for an array
            cInputBuffer.SetTokenIndexBackOne();
        }  
        
        RedVSIParseTreeVar* pNewVar = new RedVSIParseTreeVar(cVarName, pIndexExpr);
        return pNewVar;
    }
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunExternalCallCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Check the four elements which start a function call
    RedToken cUnitNameTok    = cInputBuffer.GetToken();
    RedToken cSeparatorTok   = cInputBuffer.GetToken();
    RedToken cFuncTok        = cInputBuffer.GetToken();
    RedToken cOpenBracketTok = cInputBuffer.GetToken();

    if (!cUnitNameTok.Type().IsName())                   { return NULL; }
    if (!cSeparatorTok.Predef().IsSymbolDoubleColon())   { return NULL; }
    if (!cFuncTok.Type().IsName())                       { return NULL; }
    if (!cOpenBracketTok.Predef().IsSymbolBracketOpen()) { return NULL; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // create a call object and assign the basic name information
    RedVSIParseTreeCall* pNewCmd    = new RedVSIParseTreeCall;
    RedVSIParseList*     pParamList = new RedVSIParseList;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // determine the class/object names from the inputs
    RedDataString cClassName;
    RedDataString cObjectName;
    if (cSeparatorTok.Predef().IsSymbolPeriod())
        cObjectName = cUnitNameTok.Text();
    else if (cSeparatorTok.Predef().IsSymbolDoubleColon())
        cClassName = cUnitNameTok.Text();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // iterate to populate the call with parameters
    RedToken cParamTok;
    RedToken cCommaTok;
    int         iParamsComplete = 0;
    
    while (!iParamsComplete)
    {
        // check for the end of the params first
        cParamTok = cInputBuffer.GetToken();
        if (cParamTok.IsEOF())
        {
            // EOF == Error, failed to close paralist.
            log.AddErrorEvent(
                "EOF found when traversing parameter list for: " + 
                cUnitNameTok.Text() + kIOStringSymbolDoubleColon + cFuncTok.Text());
        }
        if (cParamTok.Predef().IsSymbolBracketClose())
        {
            iParamsComplete = 1;
        }
        else
        {
            // return the token, so we can correctly read the expr.
            cInputBuffer.SetTokenIndexBackOne();

            // Read the parameter, and check the expression object is valid
            RedVSIParseTreeInterface* pExpr = RunCompareExprCompetition(cInputBuffer, log);

            // if we have a valid parameter, add it.
            if (pExpr)
            {
                pParamList->AddLast(pExpr);

                // look for a delimiter
                cCommaTok = cInputBuffer.GetToken();
                if (!cCommaTok.Predef().IsSymbolComma())
                    cInputBuffer.SetTokenIndexBackOne();
            }
            else
            {
                log.AddText(cParamTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_Call_NoExpr));
                delete pNewCmd; 
                delete pParamList; 
                return NULL;
            }
        }
    }
    
    // Assign the final details and return the command
    pNewCmd->SetDetails(cObjectName, cClassName, cFuncTok.Text(), pParamList);
    return pNewCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeInterface* RedVSIParseFactory::RunInternalCallCompetition(RedTokenBuffer& cInputBuffer, RedLog& log)
{
    // Check the elements which start an internal function call
    RedToken cFuncTok        = cInputBuffer.GetToken();    
    RedToken cOpenBracketTok = cInputBuffer.GetToken();

    if (!cFuncTok.Type().IsName())                       { return NULL; }
    if (!cOpenBracketTok.Predef().IsSymbolBracketOpen()) { return NULL; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // create a call object and assign the basic name information
    RedVSIParseTreeCall* pNewCmd    = new RedVSIParseTreeCall;
    RedVSIParseList*     pParamList = new RedVSIParseList;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // determine the class/object names from the inputs
    RedDataString cClassName;
    RedDataString cObjectName;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // iterate to populate the call with parameters
    RedToken cParamTok;
    RedToken cCommaTok;
    int    iParamsComplete = 0;    
    
    while (!iParamsComplete)
    {
        // check for the end of the params first
        cParamTok = cInputBuffer.GetToken();
        if (cParamTok.Predef().IsSymbolBracketClose())
        {
            iParamsComplete = 1;
        }
        else
        {
            // return the token, so we can correctly read the expr.
            cInputBuffer.SetTokenIndexBackOne();

            // Read the parameter, and check the expression object is valid
            RedVSIParseTreeInterface* pExpr = RunCompareExprCompetition(cInputBuffer, log);

            // if we have a valid parameter, add it.
            if (pExpr)
            {
                pParamList->AddLast(pExpr);

                // look for a delimiter
                cCommaTok = cInputBuffer.GetToken();
                if (!cCommaTok.Predef().IsSymbolComma())
                    cInputBuffer.SetTokenIndexBackOne();
            }
            else
            {
                log.AddText(cParamTok.GetPos().PosText() + RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::ePFact_Call_NoExpr));
                delete pNewCmd; 
                delete pParamList; 
                return NULL;
            }
        }
    }
    
    // Assign the final details and return the command
    RedDataString cNullClassName;
    pNewCmd->SetDetails(cClassName, cObjectName, cFuncTok.Text(), pParamList);
    return pNewCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIParseFactory::IsValueToken(const RedToken& cTok)
{
    if ( cTok.Type().IsNumber() )        return true;
    if ( cTok.Type().IsStringLiteral() ) return true;
    if ( cTok.Predef().IsBoolKeyword() ) return true;
    
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIParseFactory::IsVariableToken(const RedToken& cTok) 
{
    if ( cTok.Type().IsName() ) return true;
    
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



