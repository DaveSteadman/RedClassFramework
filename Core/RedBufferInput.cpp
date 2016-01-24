
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
    
    cNewLineCharPosList.DelAll(); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedChar RedBufferInput::GetNextChar(void)
{
    // get the character
    RedChar cCharObj( cStrBuffer.CharAtPos(iCharPos) );

    // increment to the next read position. The string class deals with any 
    // boundary checks.
    iCharPos++;
    iCol++;
    
    if (cCharObj.IsNewline()) AddRow();

    return cCharObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// routine to get the next character, but not move the position along.

RedChar RedBufferInput::PreviewNextChar(void)
{
    // get the character
    RedChar cCharObj( cStrBuffer.CharAtPos(iCharPos) );

    return cCharObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::GetCharAndPreview(RedChar& ch, RedChar& previewch)
{
    ch = this->GetNextChar();
    previewch = this->PreviewNextChar();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBufferInput::SkipWhitespace(void)
{
    RedChar cChar;

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
        int iCurrLineNumber  = cIt.GetListIndex();
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


