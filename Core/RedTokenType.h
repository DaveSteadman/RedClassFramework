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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTokenType
{
public:
    RedTokenType(void)                         { Init(); };
    
    void Init(void)                            { eState = TETokenType::eDefaultInvalid; };

    void SetNumber(void)                       { eState = TETokenType::eNumber; };
    void SetName(void)                         { eState = TETokenType::eName; };
    void SetStringLiteral(void)                { eState = TETokenType::eStringLiteral; };
    void SetSymbol(void)                       { eState = TETokenType::eSymbol; };
    void SetNonPrintable(void)                 { eState = TETokenType::eNonPrintable; };
    void SetWhitespace(void)                   { eState = TETokenType::eWhitespace; };
    
    bool IsValid(void) const                   { return (eState != TETokenType::eDefaultInvalid); };
    bool IsNumber(void) const                  { return (eState == TETokenType::eNumber); };
    bool IsName(void) const                    { return (eState == TETokenType::eName); };
    bool IsStringLiteral(void) const           { return (eState == TETokenType::eStringLiteral); };
    bool IsSymbol(void) const                  { return (eState == TETokenType::eSymbol); };
    bool IsNonPrintable(void) const            { return (eState == TETokenType::eNonPrintable); };
    bool IsWhitespace(void) const              { return (eState == TETokenType::eWhitespace); };

    static RedTokenType DefaultInvalid(void)   { return RedTokenType(TETokenType::eDefaultInvalid); };
    static RedTokenType Number(void)           { return RedTokenType(TETokenType::eNumber); };
    static RedTokenType Name(void)             { return RedTokenType(TETokenType::eName); };
    static RedTokenType StringLiteral(void)    { return RedTokenType(TETokenType::eStringLiteral); };
    static RedTokenType Symbol(void)           { return RedTokenType(TETokenType::eSymbol); };
    static RedTokenType NonPrintable(void)     { return RedTokenType(TETokenType::eNonPrintable); };
    static RedTokenType Whitespace(void)       { return RedTokenType(TETokenType::eWhitespace); };

protected:

    enum class TETokenType
    {
        eDefaultInvalid,
        eNumber, 
        eName,
        eStringLiteral,
        eSymbol,
        eNonPrintable,
        eWhitespace
    };

    RedTokenType(TETokenType eNewState) { eState = eNewState; };

private:
    TETokenType eState = TETokenType::eDefaultInvalid;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

