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

#include "RedCoreNamespace.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSITokenType
{
public:
    RedVSITokenType(void)                      { Init(); };
    
    void Init(void)                            { eState = TETokenType::eDefaultInvalid; };

    void SetNumber(void)                       { eState = TETokenType::eNumber; };
    void SetName(void)                         { eState = TETokenType::eName; };
    void SetStringLiteral(void)                { eState = TETokenType::eStringLiteral; };
    void SetSymbol(void)                       { eState = TETokenType::eSymbol; };
    void SetNonPrintable(void)                 { eState = TETokenType::eNonPrintable; };
    void SetWhitespace(void)                   { eState = TETokenType::eWhitespace; };
    void SetPredefined(void)                   { eState = TETokenType::ePredefined; };
    
    bool IsValid(void) const                   { return (eState != TETokenType::eDefaultInvalid); };
    bool IsNumber(void) const                  { return (eState == TETokenType::eNumber); };
    bool IsName(void) const                    { return (eState == TETokenType::eName); };
    bool IsStringLiteral(void) const           { return (eState == TETokenType::eStringLiteral); };
    bool IsSymbol(void) const                  { return (eState == TETokenType::eSymbol); };
    bool IsNonPrintable(void) const            { return (eState == TETokenType::eNonPrintable); };
    bool IsWhitespace(void) const              { return (eState == TETokenType::eWhitespace); };
    bool IsPredefined(void) const              { return (eState == TETokenType::ePredefined); };

    bool IsPotentiallyPredef(void) const       { return ((IsName()) || (IsSymbol())); };

    static RedVSITokenType Number(void)        { return RedVSITokenType(TETokenType::eNumber); };
    static RedVSITokenType Name(void)          { return RedVSITokenType(TETokenType::eName); };
    static RedVSITokenType StringLiteral(void) { return RedVSITokenType(TETokenType::eStringLiteral); };
    static RedVSITokenType Symbol(void)        { return RedVSITokenType(TETokenType::eSymbol); };
    static RedVSITokenType NonPrintable(void)  { return RedVSITokenType(TETokenType::eNonPrintable); };
    static RedVSITokenType Whitespace(void)    { return RedVSITokenType(TETokenType::eWhitespace); };
    static RedVSITokenType Predefined(void)    { return RedVSITokenType(TETokenType::ePredefined); };

protected:

    enum class TETokenType
    {
        eDefaultInvalid,

        eNumber, 
        eName,
        eStringLiteral,
        eSymbol,

        eNonPrintable,
        eWhitespace,
        ePredefined
    };

    RedVSITokenType(TETokenType eNewState) { eState = eNewState; };

private:
    TETokenType eState = TETokenType::eDefaultInvalid;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
