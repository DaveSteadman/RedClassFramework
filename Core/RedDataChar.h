// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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
#include "RedType.h"
#include "RedDataType.h"

namespace Red {
namespace Core {

class RedDataString;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class representing a character. A child of RedType. Contains many type querying operations.
class RedDataChar : public RedType
{
public:

    // constructor
    RedDataChar(void)        { Init();     };
    RedDataChar(char NewCh)  { Set(NewCh); };
    ~RedDataChar(void)       { };

    // Inherited: RedType
    void        Init(void)        { Set('\0'); };
    RedDataType Type(void) const  { return kDataTypeChar; };
    RedType*    Clone(void) const { RedDataChar* newC = new RedDataChar(); newC->ch = ch; return dynamic_cast<RedDataChar*>(newC); };

    // simple set & get operations
    void       Set(const char NewCh)        { ch = NewCh; };
    void       Set(int NewCh)               { if ((NewCh > 0) && (NewCh<256)) ch = NewCh; };
    void       Set(const RedDataChar& cNewVal)  { ch = cNewVal.ch; };

    char       Char(void)             const { return ch; };
    bool       IsChar(char NewCh)     const { return ch == NewCh; };
    int        DecimalNumber(void)    const;

    // queries
    bool       IsAlpha(void)          const { return ( ((ch>='a')&&(ch<='z')) || ((ch>='A')&&(ch<='Z')) ); };
    bool       IsAlphaNumeric(void)   const { return ( IsAlpha() || IsDecimalNumber() ); };
    bool       IsBracket(void)        const { return ( (ch=='(') || (ch==')') || (ch=='[') || (ch==']') || (ch=='{') || (ch=='}') ); };
    bool       IsComma(void)          const { return (ch == ','); };
    bool       IsDecimalNumber(void)  const { return ( (ch >= '0') && (ch <= '9') ); };
    bool       IsDecimalPoint(void)   const { return (ch == '.'); };
    bool       IsEOF(void)            const { return (ch == '\0'); };
    bool       IsFullstop(void)       const { return (ch == '.'); };
    bool       IsHexNumber(void)      const { return ( ((ch>='0')&&(ch<='9')) || ((ch>='a')&&(ch<='f')) || ((ch>='A')&&(ch<='F')) ); };
    bool       IsNewline(void)        const { return (ch == '\n'); };
    bool       IsEOL(void)            const { return (ch == '\n'); };
    bool       IsMinus(void)          const { return (ch == '-'); };
    bool       IsNonPrintable(void)   const { return (ch<32); };
    bool       IsNumeric(void)        const { return ( IsDecimalNumber() || IsFullstop() ); };
    bool       IsOperator(void)       const { return ( (ch=='=') || (ch=='+') || (ch=='-') || (ch=='*') || (ch=='/') || (ch=='<') || (ch=='>') ); };
    bool       IsPrintable(void)      const { return (ch>=32); };
    bool       IsQuote(void)          const { return ( (ch == '"') || (ch == '\'') ); };
    bool       IsSymbol(void)         const { return ( IsPrintable() && (!IsAlphaNumeric()) && (!IsQuote()) ); };
    bool       IsWhiteSpace(void)     const { return ( (ch == '\n') || (ch == ' ') || (ch == '\t') ); };

    // Assignment Operators
    void operator =(const int      newVal)  { Set(newVal); };
    void operator =(const char     newVal)  { Set(newVal); };
    void operator =(const RedDataChar& newVal)  { Set(newVal); };

private:

    char ch;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataChar& lhs, const RedDataChar& rhs);
bool operator!=(const RedDataChar& lhs, const RedDataChar& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedDataChar> RedDataCharSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
