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
    void           Init(void)        { Empty(); };
    RedDataType    Type(void)  const { return kDataTypeStr; };
    RedType*       Clone(void) const { RedString* newS = new RedString(*this); return dynamic_cast<RedType*>(newS); };

    // Public Main Routines
    unsigned       FirstContentIndex(void) const { return 0; };
    unsigned       LastContentIndex(void)  const { return contentsize-1; };
    char*          TextPtr(void)           const { return data; };
    unsigned       AllocSize(void)         const { return allocsize; };
    unsigned       ContentSize(void)       const { return contentsize; };

    void           Empty(void);
    void           Set(const char Ch);
    void           Set(const char* pText);
    void           Append(const char Ch);
    void           Append(const char* Str);
    void           Delete(const unsigned Index, const unsigned Count);
    void           Insert(const unsigned Index, const char  Ch);
    void           Insert(const unsigned Index, const char* Str);
    char           CharAtIndex(const unsigned Index) const;
    RedString      SubStr(const unsigned StartIndex, const unsigned Count) const;

    bool           IsCharInString(char ch) const;
    bool           IsAlphaNumeric(void) const;

    // Derived Routines
    void           Set(const RedString& Str)                          { Set(Str.TextPtr()); };
    void           Append(const RedChar& Ch)                          { Append(Ch.Char()); };
    void           Append(const RedString& Str)                       { Append(Str.TextPtr()); };
    void           Insert(const unsigned Index, const RedString& Str) { Insert(Index, Str.TextPtr()); };

    unsigned       Length(void)                         const { return contentsize; };
    bool           IsEmpty(void)                        const { return (contentsize==0); };
    RedChar        CharObjAtIndex(const unsigned Index) const { return RedChar( CharAtIndex(Index) ); };
    char           FirstChar(void)                      const { return CharAtIndex(FirstContentIndex()); };
    RedChar        FirstCharObj(void)                   const { return RedChar( CharAtIndex(FirstContentIndex()) ); };
    char           LastChar(void)                       const { if (ContentSize() == 0) return '\0'; else return CharAtIndex(LastContentIndex()); };
    RedChar        LastCharObj(void)                    const { return RedChar( CharAtIndex(LastContentIndex()) ); };

    unsigned       NumLines(void) const;
    bool           LineAtNum(const unsigned LineNum, RedString& Line) const;

    void           DelFirstChar(void) { Delete(FirstContentIndex(), 1); };
    void           DelLastChar(void)  { Delete(LastContentIndex(),  1); };

    // substring routines
    // CondenseAllocation

    // Additional Routines (relying on Main Routines for operation)

    // Internal Main Routines
    static unsigned SizeForNumBlocks(const unsigned numblocks)      { return kRedStringAllocBlockSize* numblocks; };
    static unsigned NumBlocksForSize(const unsigned strsize)        { return (strsize/kRedStringAllocBlockSize) + 1; };
    static char*    AllocData(const unsigned NumBlocks);

    // Derived Assignment/Access Operators
    void operator  =(const char Ch)         { Set(Ch); };
    void operator  =(const RedChar& Ch)     { Set(Ch.Char()); };
    void operator  =(const char* chStr)     { Set(chStr); };
    void operator  =(const RedString& Str)  { Set(Str.TextPtr()); };
    void operator +=(const char Ch)         { Append(Ch); };
    void operator +=(const RedChar& Ch)     { Append(Ch.Char()); };
    void operator +=(const char* chStr)     { Append(chStr); };
    void operator +=(const RedString& Str)  { Append(Str.TextPtr()); };

    char operator [](const unsigned Index) const { return CharAtIndex(FirstContentIndex()); };

private:

    void DeleteData(void) { if (data != NULL) { delete [] data; data = NULL; } };

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
bool      operator ==(const RedString& lhs, const char* rhs);
bool      operator !=(const RedString& lhs, const char* rhs);

bool      operator ==(const RedString& lhs, const RedString& rhs);
bool      operator !=(const RedString& lhs, const RedString& rhs);

RedString operator +(const RedString& Str1, const RedString& Str2);
RedString operator +(const RedString& Str1, const RedChar& Chr2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

