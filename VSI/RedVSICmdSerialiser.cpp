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

#include "RedCoreNamespace.h"

#include "RedVSICmdSerialiser.h"
#include "RedVSILangElement.h"
#include "RedVSIParseSerialiser.h"
#include "RedTokenPredefMap.h"

#include "RedVSICmdLet.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdWhile.h"

using namespace Red::Core;

namespace Red { 
namespace VSI { 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseCommandChain(RedTokenBuffer& cTokenBuffer, RedVSICmd* pCmd)
{
    RedToken cCRLFTok;
    cCRLFTok.SetWhitespace(RedDataString("\n"));

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

void RedVSICmdSerialiser::TokenBufferToOutputBuffer(RedTokenBuffer& cInTokenBuffer, RedBufferOutput& outBuffer)
{
    RedTokenPredefMap* pTokenMap = RedTokenPredefMap::getInstance();

    RedTokenBuffer::IteratorType cTokenIt = cInTokenBuffer.GetIterator();
    cTokenIt.First();

    while(!cTokenIt.IsDone())
    {
        RedToken CurrToken = cTokenIt.CurrentItem();

        if (CurrToken.Type().IsName())
        {
            outBuffer.Append(CurrToken.Text());
            outBuffer.Append(" ");
        }
        else if (CurrToken.Type().IsNumber())
        {
            outBuffer.Append(CurrToken.Number());
            outBuffer.Append(" ");
        }
        else if (CurrToken.Predef().IsValid())
        {
            RedTokenPredefType ioElem = CurrToken.Predef();
            RedDataString       ioStr;

            if (pTokenMap->FindStringFromPredef(ioElem, ioStr))
                outBuffer.Append(ioStr);

            outBuffer.Append(" ");
        }
        else if (CurrToken.Type().IsWhitespace())
        {
            outBuffer.Append(CurrToken.Text());
        }

        cTokenIt.Next();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseIfCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdIf* pCmd)
{
    RedVSIParseTreeInterface* pIfExpr;
    RedVSICmd*                pPosBranch;
    RedVSICmd*                pNegBranch;
    pCmd->GetDetails(pIfExpr, pPosBranch, pNegBranch);

    // write the IF command keyword
    RedToken cCmdTok(RedTokenPredefType::KeywordIf());
    cTokenBuffer.AppendToken(cCmdTok);

    // Serialise positive branch
    if (pPosBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pPosBranch);

    // Write the ELSE command keyword
    RedToken cElseCmdTok(RedTokenPredefType::KeywordElse());
    cTokenBuffer.AppendToken(cElseCmdTok);

    // Serialise negative branch
    if (pNegBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pNegBranch);

    // Write the ENDIF command keyword
    RedToken cEndCmdTok(RedTokenPredefType::KeywordEndif());
    cTokenBuffer.AppendToken(cEndCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseLetCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdLet* pCmd)
{
    RedVSIParseTreeInterface* pOutExpr;
    pCmd->GetDetails(pOutExpr);

    // Serialise the expression
    RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseLogCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdLog* pCmd)
{
    RedVSIParseTreeInterface* pOutExpr;
    pCmd->GetDetails(pOutExpr);

    // Write the command keyword
    RedToken cCmdTok(RedTokenPredefType::KeywordLog());
    cTokenBuffer.AppendToken(cCmdTok);

    // Serialise the expression
    RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutExpr);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseNewCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdNew* pCmd)
{
    RedVSILangElement          cOutType;
    RedVSILangElement          cOutLoc;
    RedDataString              cOutName;
    RedVSIParseTreeInterface*  pOutRecordIndexExpr = NULL;
    RedVSIParseTreeInterface*  pOutInitExpr = NULL;

    // Get the data to tokenise
    pCmd->GetDetails(cOutType, cOutLoc, cOutName, pOutRecordIndexExpr, pOutInitExpr);

    // Write the command keyword
    RedToken cCmdTok(RedTokenPredefType::KeywordNew());
    cTokenBuffer.AppendToken(cCmdTok);

    RedToken cLocTok;
    if      (cOutLoc.IsLocationAttribute()) cLocTok.SetPredefined(RedTokenPredefType::KeywordAttribute());
    else if (cOutLoc.IsLocationHeap())      cLocTok.SetPredefined(RedTokenPredefType::KeywordHeap());
    else if (cOutLoc.IsLocationStack())     cLocTok.SetPredefined(RedTokenPredefType::KeywordStack());
    cTokenBuffer.AppendToken(cLocTok);

    RedToken cTypeTok;
    if      (cOutType.IsTypeBool())         cTypeTok.SetPredefined(RedTokenPredefType::KeywordBool());
    else if (cOutType.IsTypeChar())         cTypeTok.SetPredefined(RedTokenPredefType::KeywordChar());
    else if (cOutType.IsTypeList())         cTypeTok.SetPredefined(RedTokenPredefType::KeywordList());
    else if (cOutType.IsTypeNumber())       cTypeTok.SetPredefined(RedTokenPredefType::KeywordNumber());
    else if (cOutType.IsTypeRecord())       cTypeTok.SetPredefined(RedTokenPredefType::KeywordRecord());
    else if (cOutType.IsTypeString())       cTypeTok.SetPredefined(RedTokenPredefType::KeywordString());
    cTokenBuffer.AppendToken(cTypeTok);

    RedToken cNameTok;
    cNameTok.SetName(cOutName);
    cTokenBuffer.AppendToken(cNameTok);

    // Serialise the record indexing expression
    if (cOutLoc.IsLocationAttribute())
    {
        RedToken cOpenBracket(RedTokenPredefType::SymbolBracketOpenSquare());
        cTokenBuffer.AppendToken(cOpenBracket);

        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutRecordIndexExpr);

        RedToken cCloseBracket(RedTokenPredefType::SymbolBracketCloseSquare());
        cTokenBuffer.AppendToken(cCloseBracket);
    }

    // Serialise the expression
    if (pOutInitExpr != NULL)
    {
        RedToken cEqualTok(RedTokenPredefType::SymbolAssignEqual());
        cTokenBuffer.AppendToken(cEqualTok);

        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pOutInitExpr);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseReturnCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdReturn* pCmd)
{
    RedVSIParseTreeInterface* pReturnExpr;
    pCmd->GetDetails(pReturnExpr);
        
    // write the command keyword
    RedToken cCmdTok;
    cCmdTok.SetPredefined(RedTokenPredefType::KeywordReturn());
    cTokenBuffer.AppendToken(cCmdTok);

    // serialise the expression
    if (pReturnExpr != NULL)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pReturnExpr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSICmdSerialiser::SerialiseWhileCmd(RedTokenBuffer& cTokenBuffer, RedVSICmdWhile* pCmd)
{
    RedVSIParseTreeInterface* pConditionExpr;
    RedVSICmd*                pLoopBranch;
    pCmd->GetDetails(pConditionExpr, pLoopBranch);

    // Write the WHILE command keyword
    RedToken cCmdTok(RedTokenPredefType::KeywordWhile());
    cTokenBuffer.AppendToken(cCmdTok);

    if (pConditionExpr)
        RedVSIParseSerialiser::SerialiseExpression(cTokenBuffer, pConditionExpr);

    // Write the LOOP command keyword
    RedToken cLoopCmdTok(RedTokenPredefType::KeywordLoop());
    cTokenBuffer.AppendToken(cLoopCmdTok);

    // Serialise the loop branch
    if (pLoopBranch != NULL)
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pLoopBranch);

    // Write the ENDLOOP command keyword
    RedToken cEndLoopCmdTok(RedTokenPredefType::KeywordEndloop());
    cTokenBuffer.AppendToken(cEndLoopCmdTok);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




