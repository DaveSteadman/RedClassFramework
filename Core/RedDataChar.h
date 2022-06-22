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

namespace Red {
namespace Core {

class RedDataString;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class representing a character. A child of RedData. Contains many type querying operations.
class RedDataChar : public RedData
{
public:

    // constructor
    RedDataChar(void)        { Init();     };
    RedDataChar(char NewCh)  { Set(NewCh); };
    ~RedDataChar(void)       { };

    // Inherited: RedData
    void        Init(void)        { Set('\0'); };
    RedDataType Type(void) const  { return kDataTypeChar; };
    RedData*    Clone(void) const { RedDataChar* newC = new RedDataChar(); newC->ch = ch; return dynamic_cast<RedDataChar*>(newC); };

    // simple set & get operations
    void       Set(const char NewCh)        { ch = NewCh; };
    void       Set(int NewCh)               { if ((NewCh > 0) && (NewCh<256)) ch = NewCh; };
    void       Set(const RedDataChar& cNew) { ch = cNew.ch; };

    char       Char(void)             const { return ch; };
    bool       IsChar(char NewCh)     const { return ch == NewCh; };

    // queries
    bool       IsAlpha(void)          const { return ( ((ch>='a')&&(ch<='z')) || ((ch>='A')&&(ch<='Z')) ); };
    bool       IsBracket(void)        const { return ( (ch=='(') || (ch==')') || (ch=='[') || (ch==']') || (ch=='{') || (ch=='}') ); };
    bool       IsComma(void)          const { return (ch == ','); };
    bool       IsDecimalNumber(void)  const { return ( (ch >= '0') && (ch <= '9') ); };
    bool       IsDecimalPoint(void)   const { return (ch == '.'); };
    bool       IsEOF(void)            const { return (ch == '\0'); };
    bool       IsEOL(void)            const { return (ch == '\n'); };
    bool       IsFullstop(void)       const { return (ch == '.'); };
    bool       IsHexNumber(void)      const { return ( ((ch>='0')&&(ch<='9')) || ((ch>='a')&&(ch<='f')) || ((ch>='A')&&(ch<='F')) ); };
    bool       IsMinus(void)          const { return (ch == '-'); };
    bool       IsNewline(void)        const { return (ch == '\n'); };
    bool       IsNonPrintable(void)   const { return (ch<32); };
    bool       IsOperator(void)       const { return ( (ch=='=') || (ch=='+') || (ch=='-') || (ch=='*') || (ch=='/') || (ch=='<') || (ch=='>') ); };
    bool       IsPrintable(void)      const { return (ch>=32); };
    bool       IsQuote(void)          const { return ( (ch == '"') || (ch == '\'') ); };
    bool       IsWhiteSpace(void)     const { return ( (ch == '\n') || (ch == ' ') || (ch == '\t') ); };

    bool       IsAlphaNumeric(void)   const { return (IsAlpha() || IsDecimalNumber()); };
    bool       IsNumeric(void)        const { return (IsDecimalNumber() || IsFullstop()); };
    bool       IsSymbol(void)         const { return (IsPrintable() && (!IsAlphaNumeric()) && (!IsQuote()) && (!IsWhiteSpace())); };

    int        IntFromCharNum(void)   const { return (IsDecimalNumber()) ? (int)ch - (int)'0' : 0; };

    // Assignment Operators
    void operator =(const int      newVal)  { Set(newVal); };
    void operator =(const char     newVal)  { Set(newVal); };
    void operator =(const RedDataChar& nV)  { Set(nV);     };

private:

    char ch;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataChar& lhs, const RedDataChar& rhs);
bool operator!=(const RedDataChar& lhs, const RedDataChar& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

