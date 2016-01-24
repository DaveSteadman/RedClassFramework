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


#include "RedSmartPtr.h"
#include "RedChar.h"
#include "RedType.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define REDSTRING_ALLOCSIZE 16

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// String class, containing numerous string search & manipulation functions and operators.
class RedString : public RedType
{
public:

    // Construction
    RedString(void);
    RedString(const RedString& Str);
    RedString(const char* Cstr);
    RedString(char FillCh, int Count);
    ~RedString();

    // Inherited: RedType
    void              Init(void)        { Empty(); };
    const RedDataType Type(void) const  { return kDataTypeStr; };
    RedType*          Clone(void) const { RedString* newS = new RedString(*this); return (RedType*)newS; };

    // Assignments
    void          Empty(void);
    void          SetChar(const int Pos, const char chNewChar);
    void          Set(const RedString& Str);
    void          Set(const char* pText);
    void          Delete(int Pos, int Count);
    void          Insert(int Pos, char Ch);
    void          Insert(int Pos, const RedString& Str);
    void          Insert(int Pos, const char* Str);
    void          Append(const RedString& Str);
    void          Append(const char* pText);
    void          Append(const char ch);
    void          Append(const RedChar ch);
    void          Append(const int num);
    void          Append(const unsigned num);
    void          DelFirstChar(void);
    void          DelLastChar(void);

    // Queries
    const int     Length(void) const           { return Len; };
    const int     IsEmpty(void) const          { return (Len==0); };

    const char    CharAtPos(int iPos) const;
    const RedChar CharObjAtPos(int iPos) const { return RedChar( CharAtPos(iPos) ); };
    const char    FirstChar(void) const        { return CharAtPos(0); };
    const RedChar FirstCharObj(void) const     { return RedChar( CharAtPos(0) ); };
    const char    LastChar(void) const         { return CharAtPos(Len-1); };
    const RedChar LastCharObj(void) const      { return RedChar( CharAtPos(Len-1) ); };

    const int     NumLines(void) const;
    const int     LineAtNum(int iLineNum, RedString& Line) const;
    const char*   TextPtr(void) const { return Txt; };
    RedString     SubStr(int Start, int Count) const;
    RedString     StringFromPos(int iPos) const;

    // Complex Operations
    RedString     ToUpper(void);
    RedString     ToLower(void);
    const int     IsCharInString(char ch) const;
    const int     IsAlphaNumeric(void) const;
    const int     IsEqualTo(const RedString& Str) const;
    const int     IsEqualTo(const char* Str) const;

    enum StrCompVal  { SC_LESS, SC_EQUAL, SC_GREATER };
    enum StrCompMode { SM_CASE_SENSITIVE, SM_IGNORE_CASE };
    StrCompVal Compare(const RedString& Str, StrCompMode Case) const;

    // Assignment/Access Operators
    void operator  =(const char* chStr);
    void operator  =(const RedChar& cChr);
    void operator  =(const RedString& Str);

    char operator [](const int Pos) const;

    void operator +=(const RedString& Str) { Append(Str); };
    void operator +=(const RedChar ch)     { Append(ch); };
    void operator +=(const char ch)        { Append(ch); };
    void operator +=(const char* ch)       { Append(ch); };

    friend RedString operator +(const RedString& Str1, const RedString& Str2);
    friend RedString operator +(const RedString& Str,  const RedChar ch);

    // Comparison Operators
    const int operator  <(const RedString Str) const;
    const int operator <=(const RedString& Str) const;
    const int operator  >(const RedString& Str) const;
    const int operator >=(const RedString& Str) const;
    const int operator ==(const RedString& Str) const;
    const int operator ==(const char* Str) const;
    const int operator !=(const RedString& Str) const;

    // Test Routines
    void DebugDump(void);

private:

    // Private Operations to control the array of characters.
    void InitUnsetChars(void);
    void Shrink();

    // Static attribs to control the allocation on all strings. 
    // - The AllocationIncrement, the size of the blocks.
    // - The InitChar, the character assigned to initialise the characters.
    static int  AllocIncr;
    static char chInitChar;

    // Size: allocated number of character.
    int   Siz;
    // Length: Size of the string assigned to the allocated array. Must be <= the size.
    int   Len;
    // Text: The allocated array of charcters.
    char* Txt;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedString> RedStringSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


