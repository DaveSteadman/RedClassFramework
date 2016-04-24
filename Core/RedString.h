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
#include "RedDataType.h"
#include "RedCoreConsts.h"
#include "RedChar.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Default tollerance on floating point equality statements
static const unsigned kRedStringAllocBlockSize = 32;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// String class, containing numerous string search & manipulation functions and operators.
/// All Index values start from zero.
class RedString : public RedType
{
public:

    // Construction
    RedString(void);
    RedString(const char* instr);
    RedString(const RedString& instr);

    // Inherited: RedType
    void              Init(void)        { Empty(); };
    const RedDataType Type(void)  const { return kDataTypeStr; };
    RedType*          Clone(void) const { RedString* newS = new RedString(*this); return (RedType*)newS; };

    // Public Main Routines
    const unsigned FirstContentIndex(void) const { return 0; };
    const unsigned LastContentIndex(void)  const { return contentsize-1; };
    const char*    TextPtr(void)           const { return data; };
    const unsigned AllocSize(void)         const { return allocsize; };
    const unsigned ContentSize(void)       const { return contentsize; };

    void           Empty(void);
    void           Set(const char Ch);
    void           Set(const char* pText);
    void           Append(const char Ch);
    void           Append(const char* Str);
    void           Delete(const unsigned Index, const unsigned Count);
    void           Insert(const unsigned Index, const char  Ch);
    void           Insert(const unsigned Index, const char* Str);
    const char     CharAtIndex(const unsigned Index) const;
    RedString      SubStr(const unsigned StartIndex, const unsigned Count) const;

    const bool     IsCharInString(char ch) const;
    const bool     IsAlphaNumeric(void) const;

    // Derived Routines
    void           Set(const RedString& Str)                          { Set(Str.TextPtr()); };
    void           Append(const RedChar& Ch)                          { Append(Ch.Char()); };
    void           Append(const RedString& Str)                       { Append(Str.TextPtr()); };
    void           Insert(const unsigned Index, const RedString& Str) { Insert(Index, Str.TextPtr()); };

    // Derived Routines
    const unsigned Length(void)                         const { return contentsize; };
    const bool     IsEmpty(void)                        const { return (contentsize==0); };
    const RedChar  CharObjAtIndex(const unsigned Index) const { return RedChar( CharAtIndex(Index) ); };
    const char     FirstChar(void)                      const { return CharAtIndex(FirstContentIndex()); };
    const RedChar  FirstCharObj(void)                   const { return RedChar( CharAtIndex(FirstContentIndex()) ); };
    const char     LastChar(void)                       const { return CharAtIndex(LastContentIndex()); };
    const RedChar  LastCharObj(void)                    const { return RedChar( CharAtIndex(LastContentIndex()) ); };


    const unsigned NumLines(void) const;
    const bool     LineAtNum(const unsigned LineNum, RedString& Line) const;

    void           DelFirstChar(void) { Delete(FirstContentIndex(), 1); };
    void           DelLastChar(void)  { Delete(LastContentIndex(),  1); };

    // substring routines
    // CondenseAllocation

    // Additional Routines (relying on Main Routines for operation)

    // Internal Main Routines
    static const unsigned SizeForNumBlocks(const unsigned numblocks)      { return kRedStringAllocBlockSize* numblocks; };
    static const unsigned NumBlocksForSize(const unsigned strsize)        { return (strsize/kRedStringAllocBlockSize) + 1; };
    static char*          AllocData(const unsigned NumBlocks);


    // Derived Assignment/Access Operators
    void operator  =(const char Ch)         { Set(Ch); };
    void operator  =(const RedChar& Ch)     { Set(Ch.Char()); };
    void operator  =(const char* chStr)     { Set(chStr); };
    void operator  =(const RedString& Str)  { Set(Str.TextPtr()); };
    void operator +=(const char Ch)         { Append(Ch); };
    void operator +=(const RedChar& Ch)     { Append(Ch.Char()); };
    void operator +=(const char* chStr)     { Append(chStr); };
    void operator +=(const RedString& Str)  { Append(Str.TextPtr()); };

    const char operator [](const unsigned Index) const { return CharAtIndex(FirstContentIndex()); };


private:

    void DeleteData(void) { if (data != REDNULL) { delete [] data; data = REDNULL; } };

    void InitialiseNonContentChars(void);

    // Char pointer to an array of data
    char* data;

    // Size of the array
    unsigned allocsize;

    // Length of data preceding an end null character, there must always be at least one.
    unsigned contentsize;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Non-Member Operators
const bool operator ==(const RedString& lhs, const char* rhs);
const bool operator !=(const RedString& lhs, const char* rhs);

const bool operator ==(const RedString& lhs, const RedString& rhs);
const bool operator !=(const RedString& lhs, const RedString& rhs);

RedString operator +(const RedString& Str1, const RedString& Str2);
RedString operator +(const RedString& Str1, const RedChar& Chr2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

