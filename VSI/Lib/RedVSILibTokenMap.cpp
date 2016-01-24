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

#include "RedVSILibTokenMap.h"
#include "RedCoreNamespace.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibTokenMap::SetupTokenMap(void)
{
    if (cVSILibTokenMap.IsEmpty())
    {
        cVSILibTokenMap.Add(kVSIIOElementKeywordArray,   RedVSIIOElement::KeywordArray());
        cVSILibTokenMap.Add(kVSIIOElementKeywordAttrib,  RedVSIIOElement::KeywordAttribute());
        cVSILibTokenMap.Add(kVSIIOElementKeywordBool,    RedVSIIOElement::KeywordBool());
        cVSILibTokenMap.Add(kVSIIOElementKeywordChar,    RedVSIIOElement::KeywordChar());
        cVSILibTokenMap.Add(kVSIIOElementKeywordClass,   RedVSIIOElement::KeywordClass());
        cVSILibTokenMap.Add(kVSIIOElementKeywordCode,    RedVSIIOElement::KeywordCode());
        cVSILibTokenMap.Add(kVSIIOElementKeywordElse,    RedVSIIOElement::KeywordElse());
        cVSILibTokenMap.Add(kVSIIOElementKeywordEndif,   RedVSIIOElement::KeywordEndif());
        cVSILibTokenMap.Add(kVSIIOElementKeywordEndloop, RedVSIIOElement::KeywordEndloop());
        cVSILibTokenMap.Add(kVSIIOElementKeywordHeap,    RedVSIIOElement::KeywordHeap());
        cVSILibTokenMap.Add(kVSIIOElementKeywordIf,      RedVSIIOElement::KeywordIf());
        cVSILibTokenMap.Add(kVSIIOElementKeywordLet,     RedVSIIOElement::KeywordLet());
        cVSILibTokenMap.Add(kVSIIOElementKeywordLoop,    RedVSIIOElement::KeywordLoop());
        cVSILibTokenMap.Add(kVSIIOElementKeywordName,    RedVSIIOElement::KeywordName());
        cVSILibTokenMap.Add(kVSIIOElementKeywordNew,     RedVSIIOElement::KeywordNew());
        cVSILibTokenMap.Add(kVSIIOElementKeywordNumber,  RedVSIIOElement::KeywordNumber());
        cVSILibTokenMap.Add(kVSIIOElementKeywordParams,  RedVSIIOElement::KeywordParams());
        cVSILibTokenMap.Add(kVSIIOElementKeywordParent,  RedVSIIOElement::KeywordParent());
        cVSILibTokenMap.Add(kVSIIOElementKeywordReturn,  RedVSIIOElement::KeywordReturn());
        cVSILibTokenMap.Add(kVSIIOElementKeywordRoutine, RedVSIIOElement::KeywordRoutine());
        cVSILibTokenMap.Add(kVSIIOElementKeywordStack,   RedVSIIOElement::KeywordStack());
        cVSILibTokenMap.Add(kVSIIOElementKeywordString,  RedVSIIOElement::KeywordString());
        cVSILibTokenMap.Add(kVSIIOElementKeywordThen,    RedVSIIOElement::KeywordThen());
        cVSILibTokenMap.Add(kVSIIOElementKeywordWhile,   RedVSIIOElement::KeywordWhile());

        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignPlus,     RedVSIIOElement::SymbolAssignPlus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignMinus,    RedVSIIOElement::SymbolAssignMinus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignMultiply, RedVSIIOElement::SymbolAssignMultiply());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignDivide,   RedVSIIOElement::SymbolAssignDivide());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignEqual,    RedVSIIOElement::SymbolAssignEqual());
        cVSILibTokenMap.Add(kVSIIOElementSymbolPlus,           RedVSIIOElement::SymbolPlus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolMinus,          RedVSIIOElement::SymbolMinus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolMultiply,       RedVSIIOElement::SymbolMultiply());
        cVSILibTokenMap.Add(kVSIIOElementSymbolDivide,         RedVSIIOElement::SymbolDivide());
        cVSILibTokenMap.Add(kVSIIOElementSymbolPower,          RedVSIIOElement::SymbolPower());

        cVSILibTokenMap.Add(RedString("=="),      RedVSIIOElement::SymbolCompareEqual());
        cVSILibTokenMap.Add(RedString("!="),      RedVSIIOElement::SymbolCompareNotEqual());
        cVSILibTokenMap.Add(RedString("<"),       RedVSIIOElement::SymbolCompareLessThan());
        cVSILibTokenMap.Add(RedString(">"),       RedVSIIOElement::SymbolCompareGreaterThan());
        cVSILibTokenMap.Add(RedString("<="),      RedVSIIOElement::SymbolCompareGreaterThanOrEqual());
        cVSILibTokenMap.Add(RedString(">="),      RedVSIIOElement::SymbolCompareLessThanOrEqual());

        cVSILibTokenMap.Add(RedString("&&"),      RedVSIIOElement::SymbolLogicAnd());
        cVSILibTokenMap.Add(RedString("!!"),      RedVSIIOElement::SymbolLogicNot());
        cVSILibTokenMap.Add(RedString("||"),      RedVSIIOElement::SymbolLogicOr());

        cVSILibTokenMap.Add(RedString("("),       RedVSIIOElement::SymbolOpenBracket());
        cVSILibTokenMap.Add(RedString(")"),       RedVSIIOElement::SymbolCloseBracket());
        cVSILibTokenMap.Add(RedString("{"),       RedVSIIOElement::SymbolOpenBracket());
        cVSILibTokenMap.Add(RedString("}"),       RedVSIIOElement::SymbolCloseBracket());
        cVSILibTokenMap.Add(RedString(","),       RedVSIIOElement::SymbolComma());
        cVSILibTokenMap.Add(RedString("."),       RedVSIIOElement::SymbolPeriod());
        cVSILibTokenMap.Add(RedString("::"),      RedVSIIOElement::SymbolDoubleColon());
        cVSILibTokenMap.Add(RedString("'"),       RedVSIIOElement::SymbolStringContent());
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


