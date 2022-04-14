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

#pragma once

#include "RedData.h"
#include "RedDataType.h"
#include "RedCoreConsts.h"
#include "RedDataChar.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Default tollerance on floating point equality statements
static const unsigned kRedDataStringAllocBlockSize = 32;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// String class, containing numerous string search & manipulation functions and operators.
// All Index values start from zero.
class RedDataString : public RedData
{
public:

    // Construction
    RedDataString(void);
    RedDataString(const char* instr);
    RedDataString(const RedDataString& instr);

    // Inherited: RedData
    void           Init(void)        { Empty(); };
    RedDataType    Type(void)  const { return kDataTypeStr; };
    RedData*       Clone(void) const { RedDataString* newS = new RedDataString(*this); return dynamic_cast<RedData*>(newS); };

    // Public Main Routines
    unsigned       FirstContentIndex(void) const { return 0; };
    unsigned       LastContentIndex(void)  const { return contentsize-1; };
    char*          TextPtr(void)           const { return data; };
    unsigned       AllocSize(void)         const { return allocsize; };
    unsigned       ContentSize(void)       const { return contentsize; };

    unsigned       Length(void) const { return contentsize; };
    void           Empty(void);
    bool           IsEmpty(void) const { return (contentsize==0); };
    
    void           Set(const char Ch);
    void           Set(const char* pText);
    void           Set(const RedDataString& Str) { Set(Str.TextPtr()); };

    void           Append(const char Ch);
    void           Append(const char* Str);
    void           Append(const RedDataChar& Ch)    { Append(Ch.Char()); };
    void           Append(const RedDataString& Str) { Append(Str.TextPtr()); };

    void           InsertAtIndex(const unsigned Index, const char  Ch);
    void           InsertAtIndex(const unsigned Index, const char* Str);
    void           InsertAtIndex(const unsigned Index, const RedDataString& Str) { InsertAtIndex(Index, Str.TextPtr()); };

    char           CharAtIndex(const unsigned Index) const;
    RedDataChar    CharObjAtIndex(const unsigned Index) const { return RedDataChar( CharAtIndex(Index) ); };
    void           SetCharAtIndex(const unsigned Index, const char Ch);
    void           SetCharObjAtIndex(const unsigned Index, const RedDataChar cCh) { SetCharAtIndex(Index, cCh.Char()); };

    char           FirstChar(void)      const { return CharAtIndex(FirstContentIndex()); };
    RedDataChar    FirstCharObj(void)   const { return RedDataChar( CharAtIndex(FirstContentIndex()) ); };
    char           LastChar(void)       const { if (ContentSize() == 0) return '\0'; else return CharAtIndex(LastContentIndex()); };
    RedDataChar    LastCharObj(void)    const { return RedDataChar( CharAtIndex(LastContentIndex()) ); };

    void           DelCharsAtIndex(const unsigned Index, const unsigned Count);
    void           DelFirstChar(void) { DelCharsAtIndex(FirstContentIndex(), 1); };
    void           DelLastChar(void)  { DelCharsAtIndex(LastContentIndex(),  1); };

    RedDataString  SubStr(const unsigned StartIndex, const unsigned Count) const;
    bool           IsCharInString(char ch) const;
    bool           IsAlphaNumeric(void) const;

    // substring routines
    // CondenseAllocation

    unsigned       NumLines(void) const;
    bool           LineAtNum(const unsigned LineNum, RedDataString& Line) const;

    // Internal Main Routines
    static unsigned SizeForNumBlocks(const unsigned numblocks) { return kRedDataStringAllocBlockSize * numblocks; };
    static unsigned NumBlocksForSize(const unsigned strsize)   { return (strsize/kRedDataStringAllocBlockSize) + 1; };
    static char*    AllocData(const unsigned NumBlocks);

    // Derived Assignment/Access Operators
    void operator  =(const char Ch)             { Set(Ch); };
    void operator  =(const RedDataChar& Ch)     { Set(Ch.Char()); };
    void operator  =(const char* chStr)         { Set(chStr); };
    void operator  =(const RedDataString& Str)  { Set(Str.TextPtr()); };
    void operator +=(const char Ch)             { Append(Ch); };
    void operator +=(const RedDataChar& Ch)     { Append(Ch.Char()); };
    void operator +=(const char* chStr)         { Append(chStr); };
    void operator +=(const RedDataString& Str)  { Append(Str.TextPtr()); };

    char operator [](const unsigned Index) const { return CharAtIndex(Index); };

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
bool          operator ==(const RedDataString& lhs, const char* rhs);
bool          operator !=(const RedDataString& lhs, const char* rhs);

bool          operator ==(const RedDataString& lhs, const RedDataString& rhs);
bool          operator !=(const RedDataString& lhs, const RedDataString& rhs);

RedDataString operator +(const RedDataString& Str1, const RedDataString& Str2);
RedDataString operator +(const RedDataString& Str1, const RedDataChar& Chr2);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

