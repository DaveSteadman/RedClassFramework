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

#include "RedCoreNamespace.h"

#include "RedVSICmdSerialiser.h"
#include "RedVSILangElement.h"
#include "RedVSIParseSerialiser.h"
#include "RedVSILibTokenMap.h"

#include "RedVSICmdLet.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdWhile.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseCommandChain(RedVSITokenBuffer& cTokenBuffer, RedVSICmdInterface* pCmd)
{
    RedVSIToken cCRLFTok;
    cCRLFTok.SetWhitespace(RedString("\n"));

    // Loop until we run out of commands
    while (pCmd)
    {
        // Get the type, so we output with a specific command template
        RedVSILangElement cCmdType = pCmd->Type();

        if      (cCmdType.IsCommandLet())    SerialiseLetCmd   (cTokenBuffer, dynamic_cast<RedVSICmdLet*>(pCmd));
        else if (cCmdType.IsCommandNew())    SerialiseNewCmd   (cTokenBuffer, dynamic_cast<RedVSICmdNew*>(pCmd));
        else if (cCmdType.IsCommandReturn()) SerialiseReturnCmd(cTokenBuffer, dynamic_cast<RedVSICmdReturn*>(pCmd));
        else if (cCmdType.IsCommandIf())     SerialiseIfCmd    (cTokenBuffer, dynamic_cast<RedVSICmdIf*>(pCmd));
        else if (cCmdType.IsCommandWhile())  SerialiseWhileCmd (cTokenBuffer, dynamic_cast<RedVSICmdWhile*>(pCmd));

        // Move onto the next command, write a new line if its valid.
        pCmd = pCmd->NextCmd();
        if (pCmd != NULL)
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
            outBuffer.Append( CurrToken.Text() );
            outBuffer.Append( kTokenWhitespaceSpace.Text() );
        }
        else if (CurrToken.Type().IsNumber())
        {
            outBuffer.Append( CurrToken.Number() );
            outBuffer.Append( kTokenWhitespaceSpace.Text() );
        }
        else if (CurrToken.Type().IsPredefined())
        {
            RedVSIIOElement ioElem = CurrToken.Predef();
            RedString       ioStr;

            if (tokenMap.FindString(ioElem, ioStr))
                outBuffer.Append(ioStr);

            outBuffer.Append( kTokenWhitespaceSpace.Text() );
        }
        else if (CurrToken.Type().IsWhitespace())
        {
            outBuffer.Append(CurrToken.Text());
        }

        cTokenIt.Next();
    }
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
    if (pPosBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pPosBranch);

    // Write the ELSE command keyword
    RedVSIToken cElseCmdTok(RedVSIIOElement::KeywordElse());
    cTokenBuffer.AppendToken(cElseCmdTok);

    // Serialise negative branch
    if (pNegBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pNegBranch);

    // Write the ENDIF command keyword
    RedVSIToken cEndCmdTok(RedVSIIOElement::KeywordEndif());
    cTokenBuffer.AppendToken(cEndCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseLetCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdLet* pCmd)
{
    RedVSIParseTreeInterface* pOutExpr;
    pCmd->GetDetails(pOutExpr);

    // Serialise the expression
    RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseLogCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdLog* pCmd)
{
    RedVSIParseTreeInterface* pOutExpr;
    pCmd->GetDetails(pOutExpr);

    // Write the command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordLog());
    cTokenBuffer.AppendToken(cCmdTok);

    // Serialise the expression
    RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutExpr);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseNewCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdNew* pCmd)
{
    RedVSILangElement          cOutType;
    RedVSILangElement          cOutLoc;
    RedString                  cOutName;
    RedVSIParseTreeInterface*  pOutRecordIndexExpr = NULL;
    RedVSIParseTreeInterface*  pOutInitExpr = NULL;

    // Get the data to tokenise
    pCmd->GetDetails(cOutType, cOutLoc, cOutName, pOutRecordIndexExpr, pOutInitExpr);

    // Write the command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordNew());
    cTokenBuffer.AppendToken(cCmdTok);

    RedVSIToken cLocTok;
    if      (cOutLoc.IsLocationAttribute()) cLocTok.SetPredefined(RedVSIIOElement::KeywordAttribute());
    else if (cOutLoc.IsLocationHeap())      cLocTok.SetPredefined(RedVSIIOElement::KeywordHeap());
    else if (cOutLoc.IsLocationStack())     cLocTok.SetPredefined(RedVSIIOElement::KeywordStack());
    cTokenBuffer.AppendToken(cLocTok);

    RedVSIToken cTypeTok;
    if      (cOutType.IsTypeBool())         cTypeTok.SetPredefined(RedVSIIOElement::KeywordBool());
    else if (cOutType.IsTypeChar())         cTypeTok.SetPredefined(RedVSIIOElement::KeywordChar());
    else if (cOutType.IsTypeList())         cTypeTok.SetPredefined(RedVSIIOElement::KeywordList());
    else if (cOutType.IsTypeNumber())       cTypeTok.SetPredefined(RedVSIIOElement::KeywordNumber());
    else if (cOutType.IsTypeRecord())       cTypeTok.SetPredefined(RedVSIIOElement::KeywordRecord());
    else if (cOutType.IsTypeString())       cTypeTok.SetPredefined(RedVSIIOElement::KeywordString());
    cTokenBuffer.AppendToken(cTypeTok);

    RedVSIToken cNameTok;
    cNameTok.SetName(cOutName);
    cTokenBuffer.AppendToken(cNameTok);

    // Serialise the record indexing expression
    if (cOutLoc.IsLocationAttribute())
    {
        RedVSIToken cOpenBracket(RedVSIIOElement::SymbolOpenSquareBracket());
        cTokenBuffer.AppendToken(cOpenBracket);

        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutRecordIndexExpr);

        RedVSIToken cCloseBracket(RedVSIIOElement::SymbolCloseSquareBracket());
        cTokenBuffer.AppendToken(cCloseBracket);
    }

    // Serialise the expression
    if (pOutInitExpr != NULL)
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
    if (pReturnExpr != NULL)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pReturnExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseWhileCmd(RedVSITokenBuffer& cTokenBuffer, RedVSICmdWhile* pCmd)
{
    RedVSIParseTreeInterface* pConditionExpr;
    RedVSICmdInterface*       pLoopBranch;
    pCmd->GetDetails(pConditionExpr, pLoopBranch);

    // Write the WHILE command keyword
    RedVSIToken cCmdTok(RedVSIIOElement::KeywordWhile());
    cTokenBuffer.AppendToken(cCmdTok);

    if (pConditionExpr)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pConditionExpr);

    // Write the LOOP command keyword
    RedVSIToken cLoopCmdTok(RedVSIIOElement::KeywordLoop());
    cTokenBuffer.AppendToken(cLoopCmdTok);

    // Serialise the loop branch
    if (pLoopBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pLoopBranch);

    // Write the ENDLOOP command keyword
    RedVSIToken cEndLoopCmdTok(RedVSIIOElement::KeywordEndloop());
    cTokenBuffer.AppendToken(cEndLoopCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




