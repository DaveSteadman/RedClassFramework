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

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenFactory::CreateTokens(const RedDataString& cInputText, RedTokenBuffer& cOutputTokenList)
{
    cOutputTokenList.Init();
    RedBufferInput cCodeBuffer(cInputText);

    bool Result = CreateTokens(cCodeBuffer, cOutputTokenList);
    
    return Result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenFactory::CreateTokens(RedBufferInput& cInputBuffer, RedTokenBuffer& cOutputTokenList)
{
    cOutputTokenList.Init();
    cInputBuffer.SetStartPos();
    RedToken cNewTok;

    // Loop, creating tokens, until we run out of text (or get an error).
    do {
        // read the token data
        RunTokenComp(cInputBuffer, cNewTok);
        cOutputTokenList.AppendToken(cNewTok);
    }
    while ((cNewTok.IsValid()) && (!cNewTok.IsEOF()));

    // Initialise if we've not interpreted all the tokens right.
    if (!cNewTok.IsValid()) 
        return false;
    else
        return true;
}

// ============================================================================
// Private Routines
// ============================================================================

RedResult RedTokenFactory::RunTokenComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    // initialise the outputs
    cNewTok.Init();
    RedResult RedResult;
    RedResult.SetNoResult();

    // skip over whitespace characters until we get to a character we want to deal with
    cInputBuffer.SkipWhitespace();

    // get the buffer position, so each competition entry can start from the 
    // same point
    int        iStartPos = cInputBuffer.GetPos();
    RedBufferPos cBufPos = cInputBuffer.GetRowColPos();
    
    //RedDataChar cPreviewChar = cInputBuffer.PreviewNextChar();
    
    unsigned iCompetitionEntry = 1;
    bool bLoopValid = true;

    while (bLoopValid)
    {
        // Reset the start read pos
        cInputBuffer.SetPos(iStartPos);

        // Put the number competition ahead of the predefined, so a leading minus sign on a number
        // isn't recognised as a negative operator.
        switch(iCompetitionEntry)
        {
        case 1: RedResult = NumberComp(cInputBuffer, cNewTok);                break;
        case 2: RedResult = SymbolComp(cInputBuffer, cNewTok);                break;
        case 3: RedResult = NameComp(cInputBuffer, cNewTok);                  break;
        case 4: RedResult = StringLiteralComp(cInputBuffer, cNewTok);         break;
        case 5: RedResult = NonPrintableComp(cInputBuffer, cNewTok);          break;
        default:
            // Run out of entries in competition. 
            bLoopValid = false;
            cNewTok.SetEOF();
        }

        if (RedResult.IsSuccess())
            bLoopValid = false;

        iCompetitionEntry++;
    }

    // Update the token to a predefined version if available.
    if (cNewTok.IsPotentiallyPredef())
    {
        RedTokenPredefType cPredefElem;
        RedTokenPredefMap* pTokenMap = RedTokenPredefMap::getInstance();

        if (pTokenMap->FindPredefFromString(cNewTok.Text(), cPredefElem))
            cNewTok.SetPredefined(cPredefElem);
    }

    cNewTok.SetPos(cBufPos);
    return RedResult;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTokenFactory::NumberComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    bool          iProcessingComplete = false;
    bool          iDecimalPointUsed   = false;
    RedDataChar   cPreviewChar1;
    RedDataChar   cPreviewChar2;
    RedDataChar   cNewChar;
    RedDataString cTokenText;
    
    // If the first character isn't numeric, return false.
    cPreviewChar1 = cInputBuffer.PreviewAhead(1);
    cPreviewChar2 = cInputBuffer.PreviewAhead(2);

    if ( (cPreviewChar1.IsNumeric()) ||
         (cPreviewChar1.IsMinus() && cPreviewChar2.IsNumeric() ) )
    {
        while (!iProcessingComplete)
        {
            // Get the characters 
            cNewChar     = cInputBuffer.GetNextChar();
            cPreviewChar1 = cInputBuffer.PreviewAhead(1);

            // Set the fullstop used flag if we have just assigned one
            if (cNewChar.IsDecimalPoint())
                iDecimalPointUsed = true;

            // Assign the first character we've already read
            cTokenText += cNewChar;

            // Determine end condition, on no number character or a 2nd
            // decimal point
            if (!cPreviewChar1.IsNumeric())
                iProcessingComplete = true;
            if (cPreviewChar1.IsDecimalPoint() && iDecimalPointUsed)
                iProcessingComplete = true;
        }

        // We have a number token, so convert the input string to a numeric
        // value.
        cNewTok.SetNumber(cTokenText, RedDataActions::NumberFromString(cTokenText));
        return RedResult::Success();
    }
    else
    {
        return RedResult::NoResult();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTokenFactory::StringLiteralComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    RedDataChar   cPreviewChar;
    RedDataChar   cNewChar;
    RedDataString cTokenText;

    // create a quick list, so we can store a number of nested quote characters
    RedDataChar   aQuoteList[10];
    int         iQuotePos = 0;
    for (int i=0; i<10; i++) aQuoteList[i]='\0';
            
    // If the first character isn't a quote character, return false.
    cPreviewChar = cInputBuffer.PreviewNextChar();
    if ( !cPreviewChar.IsQuote() )
        return RedResult::NoResult();

    // Read the quote character which starts the string
    aQuoteList[iQuotePos] = cInputBuffer.GetNextChar();
    iQuotePos++;

    while (iQuotePos)
    {
        cNewChar = cInputBuffer.GetNextChar();

        if (cNewChar.IsQuote())
        {
            // if the character matches the last quote character, then we have an end
            // to the literal (while or nested). Otherwise, add the quote to the list
            // to check for
            if (cNewChar == aQuoteList[iQuotePos-1])
            {
                iQuotePos--;
            }
            else
            {
                aQuoteList[iQuotePos] = cNewChar.Char();
                iQuotePos++;
            }
        }

        // Unless we are about to end the loop (ie the last quote character) add
        // the just examined character to the token.
        if (iQuotePos)
            cTokenText += cNewChar;
    }

    // finalise and return the object
    cNewTok.SetStringLiteral(cTokenText);  
    return RedResult::Success();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTokenFactory::NonPrintableComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    RedDataChar   cPreviewChar;
    RedDataChar   cNewChar;
        
    // If the first character isn't a quote character, return false.
    cPreviewChar = cInputBuffer.PreviewNextChar();
    if ( !cPreviewChar.IsNonPrintable() )
        return RedResult::NoResult();

    cNewChar = cInputBuffer.GetNextChar();

    // finalise and return the object
    if (cNewChar.IsEOF())
        cNewTok.SetEOF();
    else
        cNewTok.SetNonPrintable(cNewChar);

    return RedResult::Success();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTokenFactory::NameComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    RedDataChar       cPreviewChar;
    RedDataChar       cNewChar;
    RedDataString     cPreviewStr;
    RedDataString     cValidStr;
    
    RedTokenPredefType  cElem;
    RedTokenPredefType  cFinalElem;

    // If the first character isn't a letter, return false.
    cPreviewChar = cInputBuffer.PreviewNextChar();
    if ( !cPreviewChar.IsAlpha() )
        return RedResult::NoResult();

    while (cPreviewChar.IsAlphaNumeric())
    {
        cValidStr += cInputBuffer.GetNextChar();
        cPreviewChar = cInputBuffer.PreviewNextChar();
    }
    
    cNewTok.SetName(cValidStr);
    return RedResult::Success();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTokenFactory::SymbolComp(RedBufferInput& cInputBuffer, RedToken& cNewTok)
{
    RedDataChar       cPreviewChar;
    RedDataChar       cNewChar;
    RedDataString     cPreviewStr;
    RedDataString     cValidStr;

    RedTokenPredefType  cElem;
    RedTokenPredefType  cFinalElem;

    // If the first character isn't a symbol, return false.
    cPreviewChar = cInputBuffer.PreviewNextChar();
    if (!cPreviewChar.IsSymbol())
        return RedResult::NoResult();

    // Read symbols until not a symbol
    while (cPreviewChar.IsSymbol())
    {
        cValidStr += cInputBuffer.GetNextChar();
        cPreviewChar = cInputBuffer.PreviewNextChar();
    }

    cNewTok.SetSymbol(cValidStr);
    return RedResult::Success();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




