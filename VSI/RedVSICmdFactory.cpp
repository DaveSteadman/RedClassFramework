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

#include "RedVSICmd.h"

#include "RedVSICmdFactory.h"

#include "RedVSICmdLet.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdLog.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdWhile.h"

#include "RedVSIToken.h"
#include "RedVSIParseFactory.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::RunConstuctionCompetition(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    RedVSICmd* pFirstObject = NULL;
    RedVSICmd* pTailObject  = NULL;
    bool       iEndOrError  = false;

    // Loop until the end of the input buffer or an error has broken the process
    while (!iEndOrError)
    {
        // The competition is run for each command, setup the starting conditions
        RedVSICmd* pNewObject      = 0;
        int        iCompEntry      = 1;
        int        iStartTokenPos  = cInputBuffer.GetTokenIndex();

        // Loop until we have a winner an error, or the end of the input.
        while ((pNewObject == 0) && (!iEndOrError))
        {
            // Move the token position to the start for this round of inputs
            cInputBuffer.SetTokenIndex(iStartTokenPos);

            // Create the new object if we can
            switch(iCompEntry)
            {
            case 1: iEndOrError = EOFComp   (cInputBuffer, RedLog); break;
            case 2: pNewObject  = IfComp    (cInputBuffer, RedLog); break;
            case 3: pNewObject  = NewComp   (cInputBuffer, RedLog); break;
            case 4: pNewObject  = ReturnComp(cInputBuffer, RedLog); break;
            case 5: pNewObject  = WhileComp (cInputBuffer, RedLog); break;
            case 6: pNewObject  = LogComp   (cInputBuffer, RedLog); break;
            case 7: pNewObject  = ExprComp  (cInputBuffer, RedLog); break;
            default:
                {
                    iEndOrError = true;
                    // Run off the end of the available tokens. Move back to start for a parent
                    // call to continue.
                    cInputBuffer.SetTokenIndex(iStartTokenPos);
                }
            }

            // Check for any error in the competition
            if (RedLog.ContainsError()) 
                iEndOrError = true;

            // Move onto the next entry
            iCompEntry++;
        }

        // If we have a new object to deal with
        if (pNewObject != 0)
        {
            // Assign the first object (which is returned) when it is created
            if (pFirstObject == 0)
                pFirstObject = pNewObject;
                
            // Else, try and assign the next object to the chain
            else if (pTailObject != 0)
                pTailObject->SetNextCmd(pNewObject);

            // The new object is now the tail
            pTailObject  = pNewObject;
        }
    }

    // Don't return any objects on error
    if (RedLog.ContainsError())
    {
        if (pFirstObject != NULL)
        {
            delete pFirstObject;
            pFirstObject = NULL;
        }
    }

    return pFirstObject;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSICmdFactory::EOFComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    RedVSIToken cTok = cInputBuffer.GetToken();

    // The EOF doesn't consume a token, so any close bracket can be read by the parent routine that
    // previously read the open bracket.
    cInputBuffer.SetTokenIndexBackOne();

    if (cInputBuffer.CurrIndexAtLastToken())  return true;
    if (cTok.Predef().IsSymbolBracketClose()) return true;
    if (cTok.IsEOF())                         return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::IfComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the if keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordIf()) return NULL;

    RedVSIParseTreeInterface* pExpr      = NULL;
    RedVSICmd*       pPosBranch = NULL;
    RedVSICmd*       pNegBranch = NULL;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if ((pExpr == NULL) || (RedLog.ContainsError())) { RedLog.AddErrorEvent("IF command: cant construction expression"); return NULL; }

    // Check for the THEN keyword
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordThen()) { RedLog.AddErrorEvent("IF command: no Then keyword found"); delete pExpr; return NULL; }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pPosBranch = RunConstuctionCompetition(cInputBuffer, RedLog);
    if ((pPosBranch == NULL) || (RedLog.ContainsError())) return NULL;

    // Read the ELSE related token and progress, or we have an error
    cTok = cInputBuffer.GetToken();
    if ( cTok.Predef().IsKeywordElse() )
    {
        // Read the list of commands, which ends with a token the competition doesn't understand
        pNegBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

        // control the loops based on a keyword (and return token if not a keyword)
        cTok = cInputBuffer.GetToken();
    }

    if (!cTok.Predef().IsKeywordEndif())
    {
        RedLog.AddErrorEvent("IF command: no ENDIF keyword found");
        delete pExpr;
        delete pPosBranch;
        if (pNegBranch != NULL) delete pNegBranch;
        return NULL;
    }
    if (RedLog.ContainsError())
    {
        delete pExpr;
        delete pPosBranch;
        if (pNegBranch != NULL) delete pNegBranch;
        return NULL;
    }

    RedVSICmdIf* pIfCmd = new RedVSICmdIf();

    pIfCmd->SetDetails(pExpr, pPosBranch, pNegBranch);

    return pIfCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::ExprComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    
    // if we have an expression and no error, then we can progress
    if ((pExpr) && (!RedLog.ContainsError()))
    {
        // if the top level element of the parse tree is an assignment or a 
        // routine call, then its a valid expression
        if ( (pExpr->Type().IsParseFuncCall()) || (pExpr->Type().IsParseBinaryOp()) )
        {
            // Create the command object to return.
            RedVSICmdLet* pCmd = new RedVSICmdLet();
            pCmd->SetDetails(pExpr);

            return pCmd;
        }
    }

    // something didn't match, so return zero.
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::LogComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordLog()) return NULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if (!pExpr)
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_Log_NoExpr));
        return NULL;
    }

    // Create the command object to return, and assign the data.
    RedVSICmdLog* pLogCmd = new RedVSICmdLog();
    pLogCmd->SetExpr(pExpr);

    return pLogCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::NewComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordNew()) return NULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read and validate the location, type and name
    RedVSIToken cLocTok  = cInputBuffer.GetToken();
    if (!cLocTok.Predef().IsLocationKeyword())
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_New_BadLoc));
        return NULL;
    }
    RedVSILangElement cLoc;
    if      (cLocTok.Predef().IsKeywordAttribute()) cLoc = RedVSILangElement::LocationAttribute();
    else if (cLocTok.Predef().IsKeywordStack())     cLoc = RedVSILangElement::LocationStack();
    else if (cLocTok.Predef().IsKeywordHeap())      cLoc = RedVSILangElement::LocationHeap();

    RedVSIToken cTypeTok = cInputBuffer.GetToken();
    if (!cTypeTok.Predef().IsTypeKeyword())
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_New_BadType));
        return NULL;
    }
    RedVSILangElement cType;
    if      (cTypeTok.Predef().IsKeywordBool())     cType = RedVSILangElement::TypeBool();
    else if (cTypeTok.Predef().IsKeywordChar())     cType = RedVSILangElement::TypeChar();
    else if (cTypeTok.Predef().IsKeywordList())     cType = RedVSILangElement::TypeList();
    else if (cTypeTok.Predef().IsKeywordNumber())   cType = RedVSILangElement::TypeNumber();
    else if (cTypeTok.Predef().IsKeywordRecord())   cType = RedVSILangElement::TypeRecord();
    else if (cTypeTok.Predef().IsKeywordString())   cType = RedVSILangElement::TypeString();

    RedVSIToken cNameTok = cInputBuffer.GetToken();
    if (!cNameTok.Type().IsName())
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_New_BadName));
        return NULL;
    }

    // If this is an attribute, we need to read an indexing expression after the name
    RedVSIParseTreeInterface* pIndexExpr = NULL;
    if (cLoc.IsLocationAttribute())
    {
        RedVSIToken bracketToken = cInputBuffer.GetToken();
        if (!bracketToken.Predef().IsSymbolBracketOpenSquare())
        {
            RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_New_BadLoc));
            return NULL;
        }

        pIndexExpr = RedVSIParseFactory::ConstructStatementExpr(cInputBuffer, RedLog);
        if (!pIndexExpr)
        {
            RedLog.AddErrorEvent("New Command: Bad attribute indexing expression");
            return NULL;
        }

        bracketToken = cInputBuffer.GetToken();
        if (!bracketToken.Predef().IsSymbolBracketCloseSquare())
        {
            RedLog.AddErrorEvent("New Command: Bad attribute indexing expression");
            delete pIndexExpr;
            return NULL;
        }
    }

    // Look for the optional initialisation clause
    RedVSIParseTreeInterface* pInitExpr = NULL;
    RedVSIToken cEqTok = cInputBuffer.GetToken();
    if (cEqTok.Predef().IsSymbolAssignEqual())
    {
        // Create the expression and handle creation errors
        pInitExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
        if (!pInitExpr)
        {
            RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_New_NoInitExpr));
            return NULL;
        }
    }
    else
        // Undo the read of the token which wasn't the expected equals.
        cInputBuffer.SetTokenIndexBackOne();

    // Create the command object to return, and assign the data.
    RedVSICmdNew* pNewCmd = new RedVSICmdNew();
    pNewCmd->SetDetails(cType, cLoc, cNameTok.Text(), NULL, pInitExpr);

    return pNewCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::ReturnComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordReturn()) return NULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    
    // if we have an expression and no error, then we can progress
    if ((pExpr) && (!RedLog.ContainsError()))
    {
        // If the top level element of the parse tree is an assignment or a
        // routine call, then its a valid expression
        if (pExpr)
        {
            // Create the command object to return.
            RedVSICmdReturn* pCmd = new RedVSICmdReturn();
            pCmd->SetDetails(pExpr);

            return pCmd;
        }
    }

    // something didn't match, so return zero.
    return NULL;
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmd* RedVSICmdFactory::WhileComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the WHILE keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordWhile()) return NULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    RedVSIParseTreeInterface* pExpr       = NULL;
    RedVSICmd*       pLoopBranch = NULL;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if (!pExpr)
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_While_ExprError));
        return NULL;
    }

    // Check for the LOOP keyword
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordLoop())
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_While_NoLoopKeyword));
        delete pExpr;
        return NULL;
    }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pLoopBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

    // Read the ENDLOOP related token and progress, or we have an error
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordEndloop())
    {
        RedLog.AddErrorEvent(RedVSIErrorCodes::GetErrorString(RedVSIErrorCodes::eCFact_While_NoEndLoopKeyword));
        delete pExpr;
        delete pLoopBranch;
        return NULL;
    }

    RedVSICmdWhile* pWhileCmd = new RedVSICmdWhile();

    pWhileCmd->SetDetails(pExpr, pLoopBranch);

    return pWhileCmd;
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



