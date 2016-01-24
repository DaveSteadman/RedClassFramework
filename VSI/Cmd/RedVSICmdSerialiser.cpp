// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSICmdSerialiser.h"
#include "RedVSILangElement.h"
#include "RedVSIParseSerialiser.h"
#include "RedVSILibTokenMap.h"

#include "RedVSICmdExpr.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdWhile.h"

namespace Red {
namespace VSI {

using namespace Red::Core;
using namespace Red::VSI;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseCommandChain(RedVSITokenBuffer& cTokenBuffer, RedVSICmdInterface* pCmd)
{
    RedVSIToken cCRLFTok;
    cCRLFTok.SetWhitespace(RedString("\n"));

    // loop until we run out of commands
    while (pCmd)
    {
        // get the type, so we output with a specific command template
        RedVSILangElement cCmdType = pCmd->Type();

        if      (cCmdType.IsCommandLet())    SerialiseExprCmd  (cTokenBuffer, (RedVSICmdExpr*)pCmd);
        else if (cCmdType.IsCommandNew())    SerialiseNewCmd   (cTokenBuffer, (RedVSICmdNew*)pCmd);
        else if (cCmdType.IsCommandReturn()) SerialiseReturnCmd(cTokenBuffer, (RedVSICmdReturn*)pCmd);
        else if (cCmdType.IsCommandIf())     SerialiseIfCmd    (cTokenBuffer, (RedVSICmdIf*)pCmd);
        else if (cCmdType.IsCommandWhile())  SerialiseWhileCmd (cTokenBuffer, (RedVSICmdWhile*)pCmd);

        // move onto the next command, write a new line if its valid.
        pCmd = pCmd->NextCmd();
        if (pCmd != REDNULL)
            cTokenBuffer.AppendToken(cCRLFTok);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::TokenBufferToOutputBuffer(RedVSITokenBuffer& cInTokenBuffer, RedVSITokenElementMap& tokenMap, RedBufferOutput& outBuffer)
{
    RedVSITokenBuffer::IteratorType cTokenIt = cInTokenBuffer.GetIterator();
    cTokenIt.First();
    while(!cTokenIt.IsDone())
    {
        RedVSIToken CurrToken = cTokenIt.CurrentItem();

        if (CurrToken.Type().IsName())
        {
            outBuffer.Append( CurrToken.GetText() );
            outBuffer.Append( kTokenWhitespaceSpace.GetText() );
        }
        else if (CurrToken.Type().IsNumber())
        {
            outBuffer.Append( CurrToken.GetNumber() );
            outBuffer.Append( kTokenWhitespaceSpace.GetText() );
        }
        else if (CurrToken.Type().IsPredefined())
        {
            RedVSIIOElement ioElem = CurrToken.GetPredef();
            RedString       ioStr;

            if (tokenMap.FindString(ioElem, ioStr))
                outBuffer.Append(ioStr);

            outBuffer.Append( kTokenWhitespaceSpace.GetText() );
        }
        else if (CurrToken.Type().IsWhitespace())
        {
            outBuffer.Append(CurrToken.GetText());
        }

        cTokenIt.Next();
    }

    // convert into
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseExprCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdExpr* pCmd)
{
    RedVSIParseTreeInterface* pOutExpr;
    pCmd->GetDetails(pOutExpr);

    // serialise the expression 
    RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseNewCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdNew* pCmd)
{
    RedVSILangElement          cOutType;
    RedVSILangElement          cOutLoc;
    RedString                  cOutName;
    RedVSIParseTreeInterface*  pOutInitExpr;

    // get the data to tokenise
    pCmd->GetDetails(cOutType, cOutLoc, cOutName, pOutInitExpr);

    // write the command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordNew());
    cTokenBuffer.AppendToken(cCmdTok);

    RedVSIToken cLocTok;
    if (cOutLoc.IsLocationAttribute()) cLocTok.SetPredefined(RedVSIIOElement::KeywordAttribute());
    if (cOutLoc.IsLocationHeap())      cLocTok.SetPredefined(RedVSIIOElement::KeywordHeap());
    if (cOutLoc.IsLocationStack())     cLocTok.SetPredefined(RedVSIIOElement::KeywordStack());
    cTokenBuffer.AppendToken(cLocTok);

    RedVSIToken cTypeTok;
    if (cOutType.IsTypeArray())  cTypeTok.SetPredefined(RedVSIIOElement::KeywordArray());
    if (cOutType.IsTypeBool())   cTypeTok.SetPredefined(RedVSIIOElement::KeywordBool());
    if (cOutType.IsTypeChar())   cTypeTok.SetPredefined(RedVSIIOElement::KeywordChar());
    if (cOutType.IsTypeNumber()) cTypeTok.SetPredefined(RedVSIIOElement::KeywordNumber());
    if (cOutType.IsTypeString()) cTypeTok.SetPredefined(RedVSIIOElement::KeywordString());
    cTokenBuffer.AppendToken(cTypeTok);

    RedVSIToken cNameTok;
    cNameTok.SetName(cOutName);
    cTokenBuffer.AppendToken(cNameTok);
    
    // serialise the expression
    if (pOutInitExpr != REDNULL)
    {
        RedVSIToken cEqualTok(RedVSIIOElement::SymbolAssignEqual());
        cTokenBuffer.AppendToken(cEqualTok);

        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutInitExpr);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseReturnCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdReturn* pCmd)
{
    RedVSIParseTreeInterface* pReturnExpr;
    pCmd->GetDetails(pReturnExpr);
        
    // write the command keyword
    RedVSIToken cCmdTok;
    cCmdTok.SetPredefined(RedVSIIOElement::KeywordReturn());
    cTokenBuffer.AppendToken(cCmdTok);

    // serialise the expression
    if (pReturnExpr != REDNULL)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pReturnExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseIfCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdIf* pCmd)
{
    RedVSIParseTreeInterface* pIfExpr;
    RedVSICmdInterface*       pPosBranch;
    RedVSICmdInterface*       pNegBranch;
    pCmd->GetDetails(pIfExpr, pPosBranch, pNegBranch);

    // write the IF command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordIf());
    cTokenBuffer.AppendToken(cCmdTok);

    // Serialise positive branch
    if (pPosBranch != REDNULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pPosBranch);

    // write the ELSE command keyword
    RedVSIToken cElseCmdTok(RedVSIIOElement::KeywordElse());
    cTokenBuffer.AppendToken(cElseCmdTok);

    // Serialise negative branch
    if (pNegBranch != REDNULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pNegBranch);

    // write the ENDIF command keyword
    RedVSIToken cEndCmdTok(RedVSIIOElement::KeywordEndif());
    cTokenBuffer.AppendToken(cEndCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseWhileCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdWhile* pCmd)
{
    RedVSIParseTreeInterface* pConditionExpr;
    RedVSICmdInterface*       pLoopBranch;
    pCmd->GetDetails(pConditionExpr, pLoopBranch);

    // write the WHILE command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordWhile());
    cTokenBuffer.AppendToken(cCmdTok);

    if (pConditionExpr)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pConditionExpr);

    // write the LOOP command keyword
    RedVSIToken cLoopCmdTok(RedVSIIOElement::KeywordLoop());
    cTokenBuffer.AppendToken(cLoopCmdTok);

    // Serialise the loop branch
    if (pLoopBranch != REDNULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pLoopBranch);

    // write the ENDLOOP command keyword
    RedVSIToken cEndLoopCmdTok(RedVSIIOElement::KeywordEndloop());
    cTokenBuffer.AppendToken(cEndLoopCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




