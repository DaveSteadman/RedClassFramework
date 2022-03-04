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

#include "RedVSILibTokenMap.h"
#include "RedCoreNamespace.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibTokenMap::SetupTokenMap(void)
{
    if (cVSILibTokenMap.IsEmpty())
    {
        cVSILibTokenMap.Add(kVSIIOElementKeywordAttrib,                   RedVSIIOElement::KeywordAttribute());
        cVSILibTokenMap.Add(kVSIIOElementKeywordBool,                     RedVSIIOElement::KeywordBool());
        cVSILibTokenMap.Add(kVSIIOElementKeywordChar,                     RedVSIIOElement::KeywordChar());
        cVSILibTokenMap.Add(kVSIIOElementKeywordClass,                    RedVSIIOElement::KeywordClass());
        cVSILibTokenMap.Add(kVSIIOElementKeywordCode,                     RedVSIIOElement::KeywordCode());
        cVSILibTokenMap.Add(kVSIIOElementKeywordElse,                     RedVSIIOElement::KeywordElse());
        cVSILibTokenMap.Add(kVSIIOElementKeywordEndif,                    RedVSIIOElement::KeywordEndif());
        cVSILibTokenMap.Add(kVSIIOElementKeywordEndloop,                  RedVSIIOElement::KeywordEndloop());
        cVSILibTokenMap.Add(kVSIIOElementKeywordFalse,                    RedVSIIOElement::KeywordFalse());
        cVSILibTokenMap.Add(kVSIIOElementKeywordHeap,                     RedVSIIOElement::KeywordHeap());
        cVSILibTokenMap.Add(kVSIIOElementKeywordIf,                       RedVSIIOElement::KeywordIf());
        cVSILibTokenMap.Add(kVSIIOElementKeywordLet,                      RedVSIIOElement::KeywordLet());
        cVSILibTokenMap.Add(kVSIIOElementKeywordList,                     RedVSIIOElement::KeywordList());
        cVSILibTokenMap.Add(kVSIIOElementKeywordLog,                      RedVSIIOElement::KeywordLog());
        cVSILibTokenMap.Add(kVSIIOElementKeywordLoop,                     RedVSIIOElement::KeywordLoop());
        cVSILibTokenMap.Add(kVSIIOElementKeywordName,                     RedVSIIOElement::KeywordName());
        cVSILibTokenMap.Add(kVSIIOElementKeywordNew,                      RedVSIIOElement::KeywordNew());
        cVSILibTokenMap.Add(kVSIIOElementKeywordNumber,                   RedVSIIOElement::KeywordNumber());
        cVSILibTokenMap.Add(kVSIIOElementKeywordParams,                   RedVSIIOElement::KeywordParams());
        cVSILibTokenMap.Add(kVSIIOElementKeywordParent,                   RedVSIIOElement::KeywordParent());
        cVSILibTokenMap.Add(kVSIIOElementKeywordRecord,                   RedVSIIOElement::KeywordRecord());
        cVSILibTokenMap.Add(kVSIIOElementKeywordReturn,                   RedVSIIOElement::KeywordReturn());
        cVSILibTokenMap.Add(kVSIIOElementKeywordRoutine,                  RedVSIIOElement::KeywordRoutine());
        cVSILibTokenMap.Add(kVSIIOElementKeywordStack,                    RedVSIIOElement::KeywordStack());
        cVSILibTokenMap.Add(kVSIIOElementKeywordString,                   RedVSIIOElement::KeywordString());
        cVSILibTokenMap.Add(kVSIIOElementKeywordThen,                     RedVSIIOElement::KeywordThen());
        cVSILibTokenMap.Add(kVSIIOElementKeywordTrue,                     RedVSIIOElement::KeywordTrue());
        cVSILibTokenMap.Add(kVSIIOElementKeywordWhile,                    RedVSIIOElement::KeywordWhile());

        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignPlus,                RedVSIIOElement::SymbolAssignPlus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignMinus,               RedVSIIOElement::SymbolAssignMinus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignMultiply,            RedVSIIOElement::SymbolAssignMultiply());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignDivide,              RedVSIIOElement::SymbolAssignDivide());
        cVSILibTokenMap.Add(kVSIIOElementSymbolAssignEqual,               RedVSIIOElement::SymbolAssignEqual());

        cVSILibTokenMap.Add(kVSIIOElementSymbolOpenBracket,               RedVSIIOElement::SymbolBracketOpen());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCloseBracket,              RedVSIIOElement::SymbolBracketClose());
        cVSILibTokenMap.Add(kVSIIOElementSymbolOpenCurlyBracket,          RedVSIIOElement::SymbolBracketOpen());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCloseCurlyBracket,         RedVSIIOElement::SymbolBracketClose());
        cVSILibTokenMap.Add(kVSIIOElementSymbolOpenSquareBracket,         RedVSIIOElement::SymbolBracketOpenSquare());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCloseSquareBracket,        RedVSIIOElement::SymbolBracketCloseSquare());

        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareEqual,              RedVSIIOElement::SymbolCompareEqual());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareNotEqual,           RedVSIIOElement::SymbolCompareNotEqual());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareLessThan,           RedVSIIOElement::SymbolCompareLessThan());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareGreaterThan,        RedVSIIOElement::SymbolCompareGreaterThan());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareGreaterThanOrEqual, RedVSIIOElement::SymbolCompareGreaterThanOrEqual());
        cVSILibTokenMap.Add(kVSIIOElementSymbolCompareLessThanOrEqual,    RedVSIIOElement::SymbolCompareLessThanOrEqual());

        cVSILibTokenMap.Add(kVSIIOElementSymbolLogicAnd,                  RedVSIIOElement::SymbolLogicAnd());
        cVSILibTokenMap.Add(kVSIIOElementSymbolLogicNot,                  RedVSIIOElement::SymbolLogicNot());
        cVSILibTokenMap.Add(kVSIIOElementSymbolLogicOr,                   RedVSIIOElement::SymbolLogicOr());

        cVSILibTokenMap.Add(kVSIIOElementSymbolPlus,                      RedVSIIOElement::SymbolOperatorPlus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolMinus,                     RedVSIIOElement::SymbolOperatorMinus());
        cVSILibTokenMap.Add(kVSIIOElementSymbolMultiply,                  RedVSIIOElement::SymbolOperatorMultiply());
        cVSILibTokenMap.Add(kVSIIOElementSymbolDivide,                    RedVSIIOElement::SymbolOperatorDivide());
        cVSILibTokenMap.Add(kVSIIOElementSymbolPower,                     RedVSIIOElement::SymbolOperatorPower());

        cVSILibTokenMap.Add(kVSIIOElementSymbolComma,                     RedVSIIOElement::SymbolComma());
        cVSILibTokenMap.Add(kVSIIOElementSymbolPeriod,                    RedVSIIOElement::SymbolPeriod());
        cVSILibTokenMap.Add(kVSIIOElementSymbolDoubleColon,               RedVSIIOElement::SymbolDoubleColon());
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


