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

#include "RedDataString.h"
#include "RedDataNumber.h"
#include "RedDataChar.h"
#include "RedDataNumber.h"
#include "RedTokenPredefType.h"
#include "RedTokenType.h"
#include "RedBufferPos.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedToken
{
public:

    RedToken(void) { Init(); };
    RedToken(RedTokenPredefType cNewPredef) { SetPredefined(cNewPredef); };

    void Init(void);

    // operations to construct specific tokens from a known input
    void SetNumber(const RedDataString& cNewStr, const RedDataNumber& cNewNum) { Init(); cType.SetNumber();        cText=cNewStr; cNumber=cNewNum; };
    void SetName(const RedDataString& cNewStr)                                 { Init(); cType.SetName();          cText=cNewStr; };
    void SetSymbol(const RedDataString& cNewStr)                               { Init(); cType.SetSymbol();        cText=cNewStr; };
    void SetStringLiteral(const RedDataString& cNewStr)                        { Init(); cType.SetStringLiteral(); cText=cNewStr; };
    void SetNonPrintable(const RedDataChar& cNewChar)                          { Init(); cType.SetNonPrintable();  cText=cNewChar; };
    void SetWhitespace(const RedDataString& cNewStr)                           { Init(); cType.SetWhitespace();    cText=cNewStr; };

    void SetPredefined(const RedTokenPredefType& cNewPredef)     { cPredef=cNewPredef; };
    
    void SetEOF(void) { Init(); cType.SetNonPrintable(); cText = "<EOF>";  cPredef = RedTokenPredefType::SymbolEOF(); };

    bool IsPotentiallyPredef(void) { return (cType.IsName() || cType.IsSymbol()); };

    // Setup
    static RedToken EOFToken(void)              { RedToken t; t.SetEOF(); return t; };

    void         SetPos(RedBufferPos cNewPos) { cCodePos = cNewPos; };
    RedBufferPos GetPos(void)                 { return cCodePos; };

    // Basic comparisons
    bool IsValid(void) const { return (cType.IsValid()); };
    bool IsEOF(void) const;

    // Data Access
    RedTokenType       Type(void) const     { return cType; };
    RedDataNumber      Number(void) const   { return cNumber; };
    RedDataString      Text(void) const     { return cText; }
    RedTokenPredefType Predef(void) const   { return cPredef; };
    RedDataString      DebugText(void);

    // Operators
    void operator =(const RedToken& cTok);

private:
    
    
    RedTokenType cType;      // Basic token type, number, string, etc.
    RedDataString cText;     // The text extracted from the buffer

    RedTokenPredefType cPredef;  // If the type is predefined, this is relevant, otherwise a basic-invalid value.
    RedDataNumber      cNumber;  // If the type is number, this is relevant, otherwise a zero value.
    RedBufferPos       cCodePos; // Buffer position the token was extracted from. Useful in debugging/logging.
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

