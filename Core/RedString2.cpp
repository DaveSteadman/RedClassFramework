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

#include "RedString2.h"

#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString2::RedString2(void)
{
    data        = REDNULL;
    allocsize   = 0;
    contentsize = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString2::RedString2(const char* instr)
{
    data        = REDNULL;
    allocsize   = 0;
    contentsize = 0;

    Set(instr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Public Main Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString2::Empty()
{
    // Delete recreate the stored string
    DeleteData();
    data = AllocData(1);

    // Update the string size
    allocsize   = SizeForNumBlocks(1);
    contentsize = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString2::Set(const char* pText)
{
    const unsigned StrLenNewData     = (unsigned)strlen(pText);
    const unsigned NumBlocksRequired = NumBlocksForSize(StrLenNewData);

    char*          NewData           = RedString2::AllocData(NumBlocksRequired);

    // Clear Existing Data
    DeleteData();

    // Assign new array and size
    data      = NewData;
    allocsize = SizeForNumBlocks(NumBlocksRequired);

    // Assign content
    strncpy(data, pText, StrLenNewData);
    contentsize = StrLenNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString2::Append(const char Ch)
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
        char* NewData = RedString2::AllocData(NumBlocksRequired);

        // Copy the existing data
        strncpy(NewData, data, contentsize);

        // Add the character
        NewData[contentsize] = Ch;

        // Increment the content size
        contentsize++;

        // Initialise the new terminator character for robustness
        NewData[contentsize] = '\0';

        // Delete the existing data string and using the newly created one
        DeleteData();
        data      = NewData;
        allocsize = AllocSizeRequired;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString2::Delete(const unsigned Index, const unsigned Count)
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

void RedString2::Insert(const unsigned Index, const char Ch)
{
    const unsigned NumBlocksRequired = NumBlocksForSize(contentsize+1);
    const unsigned AllocSizeRequired = SizeForNumBlocks(NumBlocksRequired);

    const unsigned FirstHalfLength  = Index - FirstContentIndex();
    const unsigned SecondHalfLength = LastContentIndex() - Index + 1;

    // Create the new data
    char* NewData = RedString2::AllocData(NumBlocksRequired);

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

void RedString2::Insert(const unsigned Index, const char* Str)
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
    char* NewData = RedString2::AllocData(NumBlocksRequired);

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

const char RedString2::CharAtIndex(const unsigned Index) const
{
    char x = '\0';

    if (Index > LastContentIndex())
        return x;

    x = data[Index];

    return x;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Internal Main Routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char* RedString2::AllocData(const unsigned NumBlocks)
{
    const unsigned FirstIndex = 0;
    const unsigned LastIndex  = SizeForNumBlocks(NumBlocks);

    char* NewDataArray = new char[LastIndex];

    for(unsigned i=FirstIndex; i<LastIndex; i++)
        NewDataArray[i] = '\0';

    return NewDataArray;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString2::InitialiseNonContentChars(void)
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

const bool operator ==(const RedString2& lhs, const char* rhs)
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

const bool operator !=(const RedString2& lhs, const char* rhs)
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

} // Core
} // Red

