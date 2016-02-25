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

#pragma once

#include "RedType.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Default tollerance on floating point equality statements
static const unsigned kRedString2AllocBlockSize = 32;

/// String class, containing numerous string search & manipulation functions and operators.
class RedString2 : public RedType
{
public:

    RedString2(const char* instr);

    // Inherited: RedType
    void              Init(void)        { Empty(); };
    const RedDataType Type(void) const  { return kDataTypeStr; };
    RedType*          Clone(void) const { RedString* newS = new RedString(*this); return (RedType*)newS; };

    // Public Main Routines
    const unsigned FirstIndex(void) const { return 0; };
    const unsigned LastIndex(void) const  { return datasize; };
    const char*    TextPtr(void) const    { return Txt; };

    void           Empty();
    void           Set(const char* pText);
    void           Append(const char ch);
    void           Delete(const unsigned Pos, const unsigned Count);
    void           Insert(const unsigned Pos, char Ch);
    const char     CharAtPos(const unsigned iPos) const;
    
    // Additional Routines (relying on Main Routines for operation)
    
private:

    // Private Main Routines
    char*          AllocData(const unsigned NumBlocks);
    const unsigned SizeForNumBlocks(const unsigned numblocks) { return kRedString2AllocBlockSize * numblocks; };

    // Given a string length, how many blocks do we need? Adds 1 to string length to allow space for at least
    // one \0 character. Adds one to end of result and the int value will chop any fractional element.
    const unsigned NumBlocksForSize(const unsigned strsize)   { return (strsize+1/kRedString2AllocBlockSize) + 1 };

    // Char pointer to an array of data
    char* data;

    // Size of the array
    unsigned datasize;

    // Length of data preceding an end null character, there must always be at least one.
    unsigned contentsize;

};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

