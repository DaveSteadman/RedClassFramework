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

#include "RedVSICmdInterface.h"

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

RedVSICmdInterface* RedVSICmdFactory::RunConstuctionCompetition(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    RedVSICmdInterface* pFirstObject = REDNULL;
    RedVSICmdInterface* pTailObject  = REDNULL;
    bool                iEndOrError  = false;

    // Loop until the end of the input buffer or an error has broken the process
    while (!iEndOrError)
    {
        // The competition is run for each command, setup the starting conditions
        RedVSICmdInterface* pNewObject      = 0;
        int                 iCompEntry      = 1;
        int                 iStartTokenPos  = cInputBuffer.GetTokenIndex();

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
            if (RedLog.IsError()) 
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
    if (RedLog.IsError())
    {
        if (pFirstObject != REDNULL)
        {
            delete pFirstObject;
            pFirstObject = REDNULL;
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
    if (cTok.Predef().IsSymbolCloseBracket()) return true;
    if (cTok.IsEOF())                         return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::IfComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the if keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordIf()) return REDNULL;

    RedVSIParseTreeInterface* pExpr      = REDNULL;
    RedVSICmdInterface*       pPosBranch = REDNULL;
    RedVSICmdInterface*       pNegBranch = REDNULL;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if ((pExpr == REDNULL) || (RedLog.IsError())) { RedLog.AddErrorEvent("IF command: cant construction expression"); return REDNULL; }

    // Check for the THEN keyword
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordThen()) { RedLog.AddErrorEvent("IF command: no Then keyword found"); delete pExpr; return REDNULL; }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pPosBranch = RunConstuctionCompetition(cInputBuffer, RedLog);
    if ((pPosBranch == REDNULL) || (RedLog.IsError())) return REDNULL;

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
        if (pNegBranch != REDNULL) delete pNegBranch;
        return REDNULL;
    }
    if (RedLog.IsError())
    {
        delete pExpr;
        delete pPosBranch;
        if (pNegBranch != REDNULL) delete pNegBranch;
        return REDNULL;
    }

    RedVSICmdIf* pIfCmd = new RedVSICmdIf();

    pIfCmd->SetDetails(pExpr, pPosBranch, pNegBranch);

    return pIfCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::CallComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Call is started with a <name>.<name>.
    RedVSIToken cObjectNameTok = cInputBuffer.GetToken();
    if (!cObjectNameTok.Type().IsName()) return REDNULL;
    RedVSIToken cSeparatorTok = cInputBuffer.GetToken();
    if (!cSeparatorTok.Predef().IsSymbolPeriod()) return REDNULL;
    RedVSIToken cRoutineNameTok = cInputBuffer.GetToken();
    if (!cRoutineNameTok.Type().IsName()) return REDNULL;

    // Read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    
    // if we have an expression and no error, then we can progress
    if ((pExpr) && (!RedLog.IsError()))
    {
        // if the top level element of the parse tree is an assignment or a 
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
    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::ExprComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    
    // if we have an expression and no error, then we can progress
    if ((pExpr) && (!RedLog.IsError()))
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

RedVSICmdInterface* RedVSICmdFactory::LogComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordLog()) return REDNULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if (!pExpr)
    {
        RedLog.AddErrorEvent("Log Command: Unable to read expression.");
        return REDNULL;
    }

    // Create the command object to return, and assign the data.
    RedVSICmdLog* pLogCmd = new RedVSICmdLog();
    pLogCmd->SetExpr(pExpr);

    return pLogCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::NewComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordNew()) return REDNULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read and validate the location, type and name
    RedVSIToken cLocTok  = cInputBuffer.GetToken();
    if (!cLocTok.Predef().IsLocationKeyword())
    {
        RedLog.AddErrorEvent("New Command: Bad Location Keyword.");
        return REDNULL;
    }
    RedVSILangElement cLoc;
    if      (cLocTok.Predef().IsKeywordAttribute()) cLoc = RedVSILangElement::LocationAttribute();
    else if (cLocTok.Predef().IsKeywordStack())     cLoc = RedVSILangElement::LocationStack();
    else if (cLocTok.Predef().IsKeywordHeap())      cLoc = RedVSILangElement::LocationHeap();


    RedVSIToken cTypeTok = cInputBuffer.GetToken();
    if (!cTypeTok.Predef().IsTypeKeyword())
    {
        RedLog.AddErrorEvent("New Command: Bad Type Keyword.");
        return REDNULL;
    }
    RedVSILangElement cType;
    if      (cTypeTok.Predef().IsKeywordArray())    cType = RedVSILangElement::TypeArray();
    else if (cTypeTok.Predef().IsKeywordBool())     cType = RedVSILangElement::TypeBool();
    else if (cTypeTok.Predef().IsKeywordChar())     cType = RedVSILangElement::TypeChar();
    else if (cTypeTok.Predef().IsKeywordNumber())   cType = RedVSILangElement::TypeNumber();
    else if (cTypeTok.Predef().IsKeywordString())   cType = RedVSILangElement::TypeString();

    RedVSIToken cNameTok = cInputBuffer.GetToken();
    if (!cNameTok.Type().IsName())
    {
        RedLog.AddErrorEvent("New Command: Bad Name Token.");
        return REDNULL;
    }

    // Look for the optional initialisation clause
    RedVSIParseTreeInterface* pInitExpr = REDNULL;
    RedVSIToken cEqTok = cInputBuffer.GetToken();
    if (cEqTok.Predef().IsSymbolAssignEqual())
    {
        // Create the expression and handle creation errors
        pInitExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
        if (!pInitExpr)
        {
            RedLog.AddErrorEvent("New Command: Unable to read initialisation expression.");
            return REDNULL;
        }
    }
    else
        // Undo the read of the token which wasn't the expected equals.
        cInputBuffer.SetTokenIndexBackOne();

    // Create the command object to return, and assign the data.
    RedVSICmdNew* pNewCmd = new RedVSICmdNew();
    pNewCmd->SetDetails(cType, cLoc, cNameTok.Text(), pInitExpr);

    return pNewCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::ReturnComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.Predef().IsKeywordReturn()) return REDNULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read an expression
    RedVSIParseTreeInterface* pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    
    // if we have an expression and no error, then we can progress
    if ((pExpr) && (!RedLog.IsError()))
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
    return REDNULL;
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::WhileComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the WHILE keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordWhile()) return REDNULL;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    RedVSIParseTreeInterface* pExpr       = REDNULL;
    RedVSICmdInterface*       pLoopBranch = REDNULL;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if (!pExpr)
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: unable to construct loop expression");
        return REDNULL;
    }

    // Check for the LOOP keyword
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordLoop())
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: No loop keyword");
        delete pExpr;
        return REDNULL;
    }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pLoopBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

    // Read the ENDLOOP related token and progress, or we have an error
    cTok = cInputBuffer.GetToken();
    if (!cTok.Predef().IsKeywordEndloop())
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: No end-loop keyword");
        delete pExpr;
        delete pLoopBranch;
        return REDNULL;
    }

    RedVSICmdWhile* pWhileCmd = new RedVSICmdWhile();

    pWhileCmd->SetDetails(pExpr, pLoopBranch);

    return pWhileCmd;
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



