// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"

#include "RedVSICmdFactory.h"

#include "RedVSICmdExpr.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdWhile.h"

#include "RedVSIToken.h"
#include "RedVSIParseFactory.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::RunConstuctionCompetition(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    RedVSICmdInterface* pFirstObject = 0;
    RedVSICmdInterface* pTailObject  = 0;
    int                 iEndOrError  = 0;

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
            case 6: pNewObject  = ExprComp  (cInputBuffer, RedLog); break;
            default:
                iEndOrError = 1;
            }

            // Check for any error in the competition
            if (RedLog.IsError()) 
                iEndOrError = 1;

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

            // restart the comp for the next round
            iCompEntry = 0;
        }
    }

    return pFirstObject;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSICmdFactory::EOFComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    RedVSIToken cTok = cInputBuffer.GetToken();

    // The EOF doesn't consume a token, so any close bracket can be read by the parent routine that
    // previously read the open bracket.
    cInputBuffer.SetTokenIndexBackOne();

    if (cInputBuffer.CurrIndexAtLastToken()) return 1;
    if (cTok.GetPredef().IsSymbolCloseBracket()) return 1;
    if (cTok.IsEOF()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::IfComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the if keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.GetPredef().IsKeywordIf()) return 0;

    RedVSIParseTreeInterface* pExpr;
    RedVSICmdInterface*       pPosBranch;
    RedVSICmdInterface*       pNegBranch;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    //if (!pExpr) { RedVSIErrorCodes::Log(RedLog, RedVSIErrorCodes::eCFact_If_NoExpr, cTok);  return 0; }

    // Check for the THEN keyword
    cTok = cInputBuffer.GetToken();
    //if (!cTok.GetPredef().IsThenKeyword()) { RedVSIErrorCodes::Log(RedLog, RedVSIErrorCodes::eCFact_If_KeywordError, cTok); return 0; }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pPosBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

    // Read the ELSE related token and progress, or we have an error
    int iNegBranchValid = 0;
    cTok = cInputBuffer.GetToken();
    if ( cTok.GetPredef().IsKeywordElse() ) iNegBranchValid = 1;

    //if ( (!cTok.GetPredef().IsElseKeyword()) && (!cTok.GetPredef().IsEndifKeyword()) )
    //    { RedVSIErrorCodes::Log(RedLog, RedVSIErrorCodes::eCFact_If_KeywordError, cTok);  return 0; }

    if(iNegBranchValid)
    {
        // Read the list of commands, which ends with a token the competition doesn't understand
        pNegBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

        // control the loops based on a keyword (and return token if not a keyword)
        cTok = cInputBuffer.GetToken();
        //if (!cTok.GetPredef().IsEndifKeyword()) { RedVSIErrorCodes::Log(RedLog, RedVSIErrorCodes::eCFact_If_KeywordError, cTok); return 0; }
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
    if (!cObjectNameTok.Type().IsName()) return 0;
    RedVSIToken cSeparatorTok = cInputBuffer.GetToken();
    if (!cSeparatorTok.GetPredef().IsSymbolPeriod()) return 0;
    RedVSIToken cRoutineNameTok = cInputBuffer.GetToken();
    if (!cRoutineNameTok.Type().IsName()) return 0;

    // read an expression
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
    return 0;
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
            RedVSICmdExpr* pCmd = new RedVSICmdExpr();
            pCmd->SetDetails(pExpr);

            return pCmd;
        }
    }

    // something didn't match, so return zero.
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::NewComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.GetPredef().IsKeywordNew()) return 0;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Read and validate the location, type and name
    RedVSIToken cLocTok  = cInputBuffer.GetToken();
    if (!cLocTok.GetPredef().IsLocationKeyword())
    {
        RedLog.AddErrorEvent("New Command: Bad Location Keyword.");
        return 0;
    }
    RedVSILangElement cLoc;
    if      (cLocTok.GetPredef().IsKeywordAttribute()) cLoc = RedVSILangElement::LocationAttribute();
    else if (cLocTok.GetPredef().IsKeywordStack())     cLoc = RedVSILangElement::LocationStack();
    else if (cLocTok.GetPredef().IsKeywordHeap())      cLoc = RedVSILangElement::LocationHeap();


    RedVSIToken cTypeTok = cInputBuffer.GetToken();
    if (!cTypeTok.GetPredef().IsTypeKeyword())
    {
        RedLog.AddErrorEvent("New Command: Bad Type Keyword.");
        return 0;
    }
    RedVSILangElement cType;
    if      (cTypeTok.GetPredef().IsKeywordArray())    cType = RedVSILangElement::TypeArray();
    else if (cTypeTok.GetPredef().IsKeywordChar())     cType = RedVSILangElement::TypeChar();
    else if (cTypeTok.GetPredef().IsKeywordNumber())   cType = RedVSILangElement::TypeNumber();
    else if (cTypeTok.GetPredef().IsKeywordString())   cType = RedVSILangElement::TypeString();

    RedVSIToken cNameTok = cInputBuffer.GetToken();
    if (!cNameTok.Type().IsName())
    {
        RedLog.AddErrorEvent("New Command: Bad Name Token.");
        return 0;
    }

    // Look for the optional initialisation clause
    RedVSIParseTreeInterface* pInitExpr = 0;
    RedVSIToken cEqTok = cInputBuffer.GetToken();
    if (cEqTok.GetPredef().IsSymbolAssignEqual())
    {
        // create the expression and handle creation errors
        pInitExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
        if (!pInitExpr)
        {
            RedLog.AddErrorEvent("New Command: Unable to read initialisation expression.");
            return 0;
        }
    }
    else
        // undo the read of the token which wasn't the expected equals.
        cInputBuffer.SetTokenIndexBackOne();

    // Create the command object to return, and assign the data.
    RedVSICmdNew* pNewCmd = new RedVSICmdNew();
    pNewCmd->SetDetails(cType, cLoc, cNameTok.GetText(), pInitExpr);

    return pNewCmd;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::ReturnComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // New is started with a keyword, we can instantly return if not right.
    RedVSIToken cKeywordTok = cInputBuffer.GetToken();
    if (!cKeywordTok.GetPredef().IsKeywordReturn()) return 0;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // read an expression
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
    return 0;
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSICmdInterface* RedVSICmdFactory::WhileComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog)
{
    // Read the WHILE keyword
    RedVSIToken cTok  = cInputBuffer.GetToken();
    if (!cTok.GetPredef().IsKeywordWhile()) return 0;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    RedVSIParseTreeInterface* pExpr       = REDNULL;
    RedVSICmdInterface*       pLoopBranch = REDNULL;

    // Read the expression to assign. If okay, assign it, else delete the command
    pExpr = RedVSIParseFactory::ConstructAssignExpr(cInputBuffer, RedLog);
    if (!pExpr)
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: unable to construct loop expression");
        return 0;
    }

    // Check for the LOOP keyword
    cTok = cInputBuffer.GetToken();
    if (!cTok.GetPredef().IsKeywordLoop())
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: No loop keyword");
        delete pExpr;
        return 0;
    }

    // Create the positive branch, Read the list of commands, which ends with a token the 
    // competition doesn't understand
    pLoopBranch = RunConstuctionCompetition(cInputBuffer, RedLog);

    // Read the ENDLOOP related token and progress, or we have an error
    cTok = cInputBuffer.GetToken();
    if (!cTok.GetPredef().IsKeywordEndloop())
    {
        RedLog.AddErrorEvent("Cmd Factory: While Cmd: No end-loop keyword");
        delete pExpr;
        delete pLoopBranch;
        return 0;
    }

    RedVSICmdWhile* pWhileCmd = new RedVSICmdWhile();

    pWhileCmd->SetDetails(pExpr, pLoopBranch);

    return pWhileCmd;
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



