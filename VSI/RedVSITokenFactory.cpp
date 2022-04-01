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

#include "RedVSITokenFactory.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSITokenFactory::CreateTokens(const RedDataString& cInputText, RedVSITokenElementMap& cTokenMap, RedVSITokenBuffer& cOutputTokenList)
{
    cOutputTokenList.Init();
    RedBufferInput cCodeBuffer(cInputText);

    bool Result = CreateTokens(cCodeBuffer, cTokenMap, cOutputTokenList);
    
    return Result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSITokenFactory::CreateTokens(RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSITokenBuffer& cOutputTokenList)
{
    cOutputTokenList.Init();
    cInputBuffer.SetStartPos();
    RedVSIToken cNewTok;

    do {
        // read the token data
        RunTokenComp(cInputBuffer, cTokenMap, cNewTok);
        
        // create the new token, so long as its valid
        if ( (cNewTok.IsValid()) && (!cNewTok.IsEOF()) )
            cOutputTokenList.AppendToken(cNewTok);
    }
    while( (!cNewTok.IsEOF()) && (cNewTok.IsValid()) );

    //RedDataString cRep = Test_RedVSITokenBuffer::CreateBufferReport(cOutputTokenList, cTokenMap);

    // Initialise if we've not interpreted all the tokens right.
    if (!cNewTok.IsValid()) 
    {
        cOutputTokenList.Init();
        return false;
    }
    return true;
}

// ============================================================================
// Private Routines
// ============================================================================

RedResult RedVSITokenFactory::RunTokenComp(RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSIToken& cNewTok)
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

    while (RedResult.IsNoResult())
    {
        // Reset the start read pos
        cInputBuffer.SetPos(iStartPos);

        // Put the number competition ahead of the predefined, so a leading minus sign on a number
        // isn't recognised as a negative operator.
        switch(iCompetitionEntry)
        {
        case 1: RedResult = NumberComp(cInputBuffer, cNewTok);                break;
        case 2: RedResult = PredefinedComp(cInputBuffer, cTokenMap, cNewTok); break;
        case 3: RedResult = NameComp(cInputBuffer, cNewTok);                  break;
        case 4: RedResult = StringLiteralComp(cInputBuffer, cNewTok);         break;
        case 5: RedResult = NonPrintableComp(cInputBuffer, cNewTok);          break;
        default:
            RedResult.SetFail();
        }
        
        iCompetitionEntry++;
    }
    
    cNewTok.SetPos(cBufPos);
    return RedResult;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSITokenFactory::NumberComp(RedBufferInput& cInputBuffer, RedVSIToken& cNewTok)
{
    bool      iProcessingComplete = false;
    bool      iDecimalPointUsed   = false;
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
        cNewTok.SetNumber(RedDataNumber(cTokenText));
        return RedResult::Success();
    }
    else
    {
        return RedResult::NoResult();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSITokenFactory::StringLiteralComp(RedBufferInput& cInputBuffer, RedVSIToken& cNewTok)
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

RedResult RedVSITokenFactory::NonPrintableComp(RedBufferInput& cInputBuffer, RedVSIToken& cNewTok)
{
    RedDataChar   cPreviewChar;
    RedDataChar   cNewChar;
        
    // If the first character isn't a quote character, return false.
    cPreviewChar = cInputBuffer.PreviewNextChar();
    if ( !cPreviewChar.IsNonPrintable() )
        return RedResult::NoResult();
        
    cNewChar = cInputBuffer.GetNextChar();

    // finalise and return the object
    cNewTok.SetNonPrintable(cNewChar);
    return RedResult::Success();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSITokenFactory::NameComp(RedBufferInput& cInputBuffer, RedVSIToken& cNewTok)
{
    RedDataChar       cPreviewChar;
    RedDataChar       cNewChar;
    RedDataString     cPreviewStr;
    RedDataString     cValidStr;
    
    RedVSIIOElement  cElem;
    RedVSIIOElement  cFinalElem;

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

RedResult RedVSITokenFactory::PredefinedComp(RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSIToken& cNewTok)
{
    bool          iProcessingComplete = false;
    RedDataChar       cPreviewChar;
    RedDataChar       cNewChar;
    RedDataString     cPreviewStr;
    RedDataString     cValidStr;
    
    RedVSIIOElement  cElem;
    RedVSIIOElement  cFinalElem;
    bool             iExactMatchFound = false;
    
    // skip over whitespace characters until we get to a character we want to deal with
    cPreviewChar = cInputBuffer.PreviewNextChar();

    while (!iProcessingComplete)
    {
        // Get the next potential character and create the new string to search for.
        cPreviewChar = cInputBuffer.PreviewNextChar();
        cPreviewStr = cValidStr + cPreviewChar;

        // Get the number of matches for the new string
        unsigned NumMatches = cTokenMap.CountMatchCandidates(cPreviewStr);
        if (NumMatches >= 1)
        {
            // We have matches, so get the character for real and look for an exact match
            cValidStr += cInputBuffer.GetNextChar();
        }
        else if (NumMatches == 1)
        {
            // We have matches, so get the character for real and look for an exact match
            if (cTokenMap.Find(cValidStr, cElem))
            {
                iExactMatchFound = true;
                cFinalElem = cElem;
                iProcessingComplete = true;
            }
        }
        // set complete when we run out of matches - we have to look beyond any match to ensure we haven't found a substring.
        else
        {
            iProcessingComplete = true;
        }
    }
        
    // if we found a match create a valid object we are going to return     
    if (iExactMatchFound)
    {
        cNewTok.SetPredefined(cElem);
        return RedResult::Success();
    }
    return RedResult::NoResult();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




