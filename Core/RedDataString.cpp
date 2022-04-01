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

#define _CRT_SECURE_NO_WARNINGS

#include "RedDataString.h"

#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString::RedDataString(void)
{
    data        = NULL;
    allocsize   = 0;
    contentsize = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString::RedDataString(const char* instr)
{
    data        = NULL;
    allocsize   = 0;
    contentsize = 0;

    Set(instr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString::RedDataString(const RedDataString& instr)
{
    data        = NULL;
    allocsize   = 0;
    contentsize = 0;

    if (instr.TextPtr() != NULL)
        Set(instr.TextPtr());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Public Main Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::Empty(void)
{
    // Delete recreate the stored string
    DeleteData();
    data = AllocData(1);

    // Update the string size
    allocsize   = SizeForNumBlocks(1);
    contentsize = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::Set(const char Ch)
{
    if (Ch == '\0')
    {
        Empty();
    }
    else
    {
        const unsigned NumBlocksRequired = NumBlocksForSize(1);
        const unsigned AllocSizeRequired = SizeForNumBlocks(NumBlocksRequired);

        char*          NewData           = RedDataString::AllocData(NumBlocksRequired);

        // Clear Existing Data
        DeleteData();

        // Assign new array and size
        data        = NewData;
        allocsize   = AllocSizeRequired;
        contentsize = 1;

        // Assign content
        data[0] = Ch;

        // Loop to clear the rest of the string
        InitialiseNonContentChars();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::Set(const char* pText)
{
    if (pText == NULL)
    {
        Empty();
    }
    else
    {
        const unsigned StrLenNewData     = (unsigned)strlen(pText);
        const unsigned NumBlocksRequired = NumBlocksForSize(StrLenNewData);
        const unsigned AllocSizeRequired = SizeForNumBlocks(NumBlocksRequired);

        char*          NewData           = RedDataString::AllocData(NumBlocksRequired);

        // Clear Existing Data
        DeleteData();

        // Assign new array and size
        data      = NewData;
        allocsize = AllocSizeRequired;

        // Assign content
        strncpy(data, pText, StrLenNewData);
        contentsize = StrLenNewData;

        // Loop to clear the rest of the string
        InitialiseNonContentChars();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::Append(const char Ch)
{
    if (IsEmpty())
    {
        Set(Ch);
    }
    else
    {
        const unsigned NumBlocksRequired = NumBlocksForSize(contentsize+1);
        const unsigned AllocSizeRequired = SizeForNumBlocks(NumBlocksRequired);

        // If we can fit the characters into the current size, tack it on.
        if (AllocSizeRequired == allocsize)
        {
            // Add the character
            data[contentsize] = Ch;

            // Increment the content size
            contentsize++;

            // Initialise the new terminator character for robustness
            data[contentsize] = '\0';
        }
        // Else, we need to allocate into a larger string
        else
        {
            // Create the new data
            char* NewData = RedDataString::AllocData(NumBlocksRequired);

            // Copy the existing data
            strncpy(NewData, data, contentsize);

            // Add the character
            NewData[contentsize] = Ch;

            // Increment the content size
            contentsize++;

            // Delete the existing data string and using the newly created one
            DeleteData();
            data      = NewData;
            allocsize = AllocSizeRequired;

            // Loop to clear the rest of the string
            InitialiseNonContentChars();
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::Append(const char* Str)
{
    if (IsEmpty())
    {
        Set(Str);
    }
    else
    {
        const unsigned AppendSize           = (unsigned)strlen(Str);
        const unsigned NumBlocksRequired    = NumBlocksForSize(contentsize+AppendSize);
        const unsigned AllocSizeRequired    = SizeForNumBlocks(NumBlocksRequired);

        // If we can fit the characters into the current size, tack it on.
        if (AllocSizeRequired == allocsize)
        {
            // Append the new data
            strncpy(&data[contentsize], Str, AppendSize);

            // Increment the content size
            contentsize += AppendSize;

            // Initialise the new terminator character for robustness
            data[contentsize] = '\0';
        }
        // Else, we need to allocate into a larger string
        else
        {
            // Create the new data
            char* NewData = RedDataString::AllocData(NumBlocksRequired);

            // Copy the existing data
            strncpy(NewData, data, contentsize);

            // Append the new data
            strncpy(&NewData[contentsize], Str, AppendSize);

            // Assign all the new data and increment the size
            DeleteData();
            data      = NewData;
            allocsize = AllocSizeRequired;
            contentsize += AppendSize;

            // Loop to clear the rest of the string
            InitialiseNonContentChars();
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::DelCharsAtIndex(const unsigned Index, const unsigned Count)
{
    if (Index > LastContentIndex())
        return;

    unsigned CurrDeleteIndex = Index;
    unsigned CurrCopyIndex   = Index + Count;

    // Loop to copy characters
    while (CurrCopyIndex <= LastContentIndex())
    {
        // Overwrite the characters
        data[CurrDeleteIndex] = data[CurrCopyIndex];

        // Move the index values along
        CurrDeleteIndex++;
        CurrCopyIndex = CurrDeleteIndex + Count;
    }

    // Setup the new content length
    contentsize = CurrDeleteIndex;

    // Loop to clear the rest of the string
    InitialiseNonContentChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::InsertAtIndex(const unsigned Index, const char Ch)
{
    const unsigned NumBlocksRequired = NumBlocksForSize(contentsize+1);
    const unsigned AllocSizeRequired = SizeForNumBlocks(NumBlocksRequired);

    const unsigned FirstHalfLength  = Index - FirstContentIndex();
    const unsigned SecondHalfLength = LastContentIndex() - Index + 1;

    // Create the new data
    char* NewData = RedDataString::AllocData(NumBlocksRequired);

    // Copy the first half
    strncpy(NewData, data, FirstHalfLength);

    // Add the character
    NewData[Index] = Ch;

    // Copy the second half
    strncpy(&NewData[Index+1], &data[Index], SecondHalfLength);

    // Increment the content size
    contentsize++;

    // Delete the existing data string and using the newly created one
    DeleteData();
    data      = NewData;
    allocsize = AllocSizeRequired;

    // Loop to clear the rest of the string
    InitialiseNonContentChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::InsertAtIndex(const unsigned Index, const char* Str)
{
    const unsigned InsertSize           = (unsigned)strlen(Str);

    const unsigned NumBlocksRequired    = NumBlocksForSize(contentsize+InsertSize);
    const unsigned AllocSizeRequired    = SizeForNumBlocks(NumBlocksRequired);

    const unsigned FirstHalfLength      = Index - FirstContentIndex();
    const unsigned SecondHalfLength     = LastContentIndex() - Index + 1;

    const unsigned FirstHalfReadIndex   = FirstContentIndex();
    const unsigned SecondHalfReadIndex  = FirstHalfLength;

    const unsigned FirstHalfWriteIndex  = FirstContentIndex();
    const unsigned InsertWriteIndex     = FirstHalfWriteIndex + FirstHalfLength;
    const unsigned SecondHalfWriteindex = InsertWriteIndex + InsertSize;

    // Create the new data
    char* NewData = RedDataString::AllocData(NumBlocksRequired);

    // Copy the first half
    strncpy(&NewData[FirstHalfWriteIndex], &data[FirstHalfReadIndex], FirstHalfLength);

    // Copy the insert
    strncpy(&NewData[InsertWriteIndex], Str, InsertSize);

    // Copy the second half
    strncpy(&NewData[SecondHalfWriteindex], &data[SecondHalfReadIndex], SecondHalfLength);

    // Increment the content size
    contentsize += InsertSize;

    // Delete the existing data string and using the newly created one
    DeleteData();
    data      = NewData;
    allocsize = AllocSizeRequired;

    // Loop to clear the rest of the string
    InitialiseNonContentChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::SetCharAtIndex(const unsigned Index, const char Ch)
{
    if (Index > contentsize)
        return;

    data[Index] = Ch;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char RedDataString::CharAtIndex(const unsigned Index) const
{
    char x = '\0';

    if (Index > LastContentIndex())
        return x;

    x = data[Index];

    return x;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataString::SubStr(const unsigned StartIndex, const unsigned Count) const
{
    RedDataString OutStr;

    if (StartIndex > LastContentIndex())
        return OutStr;

    unsigned LastSubStrIndex = StartIndex + (Count - 1);
    if (LastSubStrIndex > LastContentIndex())
        LastSubStrIndex = LastContentIndex();

    unsigned SubStrLength = LastSubStrIndex - StartIndex + 1;
    unsigned SubStrBlocksRequired = NumBlocksForSize(SubStrLength);

    OutStr.data = AllocData(SubStrBlocksRequired);
    OutStr.allocsize = SizeForNumBlocks(SubStrBlocksRequired);
    OutStr.contentsize = SubStrLength;
    strncpy(OutStr.data, &data[StartIndex], SubStrLength);
    OutStr.InitialiseNonContentChars();

    return OutStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataString::IsCharInString(char ch) const
{
    for (unsigned Pos = 0; Pos < contentsize; ++Pos)
    {
        if (data[Pos] == ch)
            return true;
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataString::IsAlphaNumeric(void) const
{
    RedDataChar RedDataChar;
    for (unsigned iPos = 0; iPos < contentsize; ++iPos)
    {
        RedDataChar = CharObjAtIndex(iPos);

        if (!RedDataChar.IsAlphaNumeric())
            return false;
    }
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Derived Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDataString::NumLines(void) const
{
    unsigned NumLines = 0;

    for (unsigned i=0; i<ContentSize(); i++)
    {
        // account for the first line if we have a valid char
        if ( (NumLines == 0) && ( data[i] != '\0' ) )
            NumLines = 1;

        if ( data[i] == '\n' )
            NumLines++;
    }

    return NumLines;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataString::LineAtNum(const unsigned LineNum, RedDataString& Line) const
{
    unsigned iLineStartIndex, iLineLength, iCurrIndex;
    unsigned iOnLine;

    // initialise the return value
    Line = "";

    // initialise the working values
    iLineLength     = 0;
    iCurrIndex      = 0; 
    iOnLine         = 1;

    // Lines are indexed as we would want to see a position marker, from 1.
    // check we have enough lines to fullfill operation
    if ((LineNum > NumLines()) || (LineNum < 1))
        return false;

    // Loop to the first character of the line we need
    while (iOnLine < LineNum)
    {
        if ( data[iCurrIndex] == '\n' )
            iOnLine++;

         iCurrIndex++;
    }

    // mark the start of the line
    iLineStartIndex = iCurrIndex;

    // loop to the end of the line
    while ( (iCurrIndex<contentsize) && (data[iCurrIndex]!='\n') )
    {
        iCurrIndex++;
        iLineLength++;
    }

    // use the inbuilt routine to retrieve the section of line
    Line = SubStr(iLineStartIndex, iLineLength);

    return true;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Internal Main Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char* RedDataString::AllocData(const unsigned NumBlocks)
{
    const unsigned FirstIndex = 0;
    const unsigned LastIndex  = SizeForNumBlocks(NumBlocks);

    char* NewDataArray = new char[LastIndex];

    for(unsigned i=FirstIndex; i<LastIndex; i++)
        NewDataArray[i] = '\0';

    return NewDataArray;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataString::InitialiseNonContentChars(void)
{
    unsigned CurrIndex = LastContentIndex() + 1;

    // Loop to clear the rest of the string
    while (CurrIndex < allocsize)
    {
        data[CurrIndex] = '\0';
        CurrIndex++;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Non-Member Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator ==(const RedDataString& lhs, const char* rhs)
{
    // If the strings are different lengths, fail.
    if (strlen(rhs) != lhs.ContentSize())
        return false;

    const char* pStrTxt = lhs.TextPtr();

    // Compare each character, fail if any difference is found
    for (unsigned i=0; i<lhs.ContentSize(); i++)
    {
        if (rhs[i] != pStrTxt[i])
            return false;
    }

    // Return success, nothing failed to match
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator !=(const RedDataString& lhs, const char* rhs)
{
    // If the strings are different lengths, fail.
    if (strlen(rhs) != lhs.ContentSize())
        return true;

    const char* pStrTxt = lhs.TextPtr();

    // Compare each character, fail if any difference is found
    for (unsigned i=0; i<lhs.ContentSize(); i++)
    {
        if (rhs[i] != pStrTxt[i])
            return true;
    }

    // Return false, nothing matched
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator ==(const RedDataString& lhs, const RedDataString& rhs)
{
    return (lhs == rhs.TextPtr());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator !=(const RedDataString& lhs, const RedDataString& rhs)
{
    return (lhs != rhs.TextPtr());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString operator +(const RedDataString& Str1, const RedDataString& Str2)
{
    RedDataString RetStr(Str1);

    RetStr.Append(Str2);

    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString operator +(const RedDataString& Str1, const RedDataChar& Chr2)
{
    RedDataString RetStr(Str1);

    RetStr.Append(Chr2);

    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

