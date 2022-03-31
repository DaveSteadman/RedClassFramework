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

#include "RedBufferInput.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::Init(void)
{ 
    cStrBuffer.Empty(); 
    
    iCharPos = 0; 
    iRow     = 1;
    iCol     = 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataChar RedBufferInput::GetNextChar(void)
{
    // get the character
    RedDataChar cCharObj( cStrBuffer.CharAtIndex(iCharPos) );

    // increment to the next read position. The string class deals with any 
    // boundary checks.
    iCharPos++;
    iCol++;
    
    if (cCharObj.IsNewline()) AddRow();

    return cCharObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// routine to get the next character, but not move the position along.

RedDataChar RedBufferInput::PreviewNextChar(void)
{
    // get the character
    RedDataChar cCharObj( cStrBuffer.CharAtIndex(iCharPos) );

    return cCharObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataChar RedBufferInput::PreviewAhead(const unsigned IndexAhead)
{
    const unsigned required_index = (iCharPos - 1) + IndexAhead;

    RedDataChar retch( cStrBuffer.CharAtIndex(required_index));

    return retch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::GetCharAndPreview(RedDataChar& ch, RedDataChar& previewch)
{
    ch = this->GetNextChar();
    previewch = this->PreviewNextChar();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::SkipWhitespace(void)
{
    RedDataChar cChar;

    // look ahead to the next character
    cChar = PreviewNextChar();
    while (cChar.IsWhiteSpace())
    {
        // if the next character is a whitespace, read it (and throw it away).
        cChar = GetNextChar();
        
        // preview the next character for the next while evaluation
        cChar = PreviewNextChar();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::AddRow(void)
{
    // move the working position along
    iRow++; 
    iCol = 1;

    // Update the list of known newlines if the new count exceeds the last 
    // entered value. Add the new line if there is nothing in the list
    int iLastCharPos=0;
    if (cNewLineCharPosList.IsEmpty())
    {
       cNewLineCharPosList.AddLast(iCharPos);
    }   
    // else, look at the last position
    else if (cNewLineCharPosList.FindLast(iLastCharPos))
    {
        if (iCharPos > iLastCharPos)
            cNewLineCharPosList.AddLast(iCharPos);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::SetPos(int iNewPos)
{
    // if we jump forward, we can't determine if a newline has been missed, so
    // need to mandate backwards travel only.
    if (iNewPos > iCharPos) throw;

    // assign the new position
    iCharPos = iNewPos;

    // now lookup the old row/col so we can track the text position.
    ListItType cIt(&cNewLineCharPosList);
    cIt.First();
    int iFoundLine=0;
    while( (!cIt.IsDone()) && (!iFoundLine) )
    {
        // get the current line and character positions. When the search is done, 
        // the iteration will need to have overstepped the actual char pos, so
        // keeping a previous version.
        int iCurrLineCharPos = cIt.CurrentItem();
        int iCurrLineNumber  = cIt.CollectionIndex();
        int iPrevLineCharPos = iCurrLineCharPos;
        int iPrevLineNumber  = iCurrLineNumber;
        
        if (iNewPos <= iCurrLineCharPos)
        {
            iRow     = iPrevLineNumber;
            iCol     = iNewPos - iPrevLineCharPos;
            
            iFoundLine = 1;
        }
        
        cIt.Next();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


