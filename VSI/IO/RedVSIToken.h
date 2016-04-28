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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSITokenType.h"
#include "RedVSITokenElementMap.h"
#include "RedBufferPos.h"

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIToken
{
public:

    RedVSIToken(void) { Init(); };
    RedVSIToken(RedVSIIOElement cNewPredef) { SetPredefined(cNewPredef); };

    void Init(void);

    // operations to construct specific tokens from a known input
    void SetNumber(const RedNumber& cNewNum)              { Init(); cType.SetNumber();        cNumber=cNewNum; };
    void SetName(const RedString& cNewStr)                { Init(); cType.SetName();          cText=cNewStr; };
    void SetStringLiteral(const RedString& cNewStr)       { Init(); cType.SetStringLiteral(); cText=cNewStr; };
    void SetNonPrintable(const RedChar& cNewChar)         { Init(); cType.SetNonPrintable();  cText=cNewChar; };
    void SetWhitespace(const RedString& cNewStr)          { Init(); cType.SetWhitespace();    cText=cNewStr; };
    void SetPredefined(const RedVSIIOElement& cNewPredef) { Init(); cType.SetPredefined();    cPredef=cNewPredef; };

    // Setup
    static RedVSIToken WhitespaceSpaceToken(void)  { RedVSIToken t; t.SetWhitespace(RedString(" "));               return t; };
    static RedVSIToken EOFToken(void)              { RedVSIToken t; t.SetPredefined(RedVSIIOElement::SymbolEOF()); return t; };

    void         SetPos(RedBufferPos cNewPos) { cCodePos = cNewPos; };
    RedBufferPos GetPos(void)                 { return cCodePos; };

    // Basic comparisons
    bool IsValid(void) const { return (cType.IsValid()); };
    bool IsEOF(void) const;

    // Data Access
    RedVSITokenType Type(void) const        { return cType; };
    RedNumber       GetNumber(void) const   { return cNumber; };
    RedString       GetText(void) const     { return cText; }
    RedVSIIOElement GetPredef(void) const   { return cPredef; };
    RedString       GetDebugText(RedVSITokenElementMap& RedVSITokenMap);

    // Operators
    void operator =(const RedVSIToken& cTok);

private:
    
    // overall type, stating number, string, predefined etc.
    RedVSITokenType cType;
    
    // The text extracted from the buffer
    RedString cText;

    // If the type is predefined, this is relevant
    RedVSIIOElement cPredef;

    // If the type is number, this is relevant
    RedNumber cNumber;

    // Buffer position the token was extracted from. Useful in debugging/logging functionality
    RedBufferPos cCodePos;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedVSIToken kTokenWhitespaceSpace  = RedVSIToken::WhitespaceSpaceToken();
static const RedVSIToken kTokenEOF              = RedVSIToken::EOFToken();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

