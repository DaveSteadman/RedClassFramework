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
        cVSILibTokenMap.Add(kIOStringKeywordAttrib,                   RedTokenPredefType::KeywordAttribute());
        cVSILibTokenMap.Add(kIOStringKeywordBool,                     RedTokenPredefType::KeywordBool());
        cVSILibTokenMap.Add(kIOStringKeywordChar,                     RedTokenPredefType::KeywordChar());
        cVSILibTokenMap.Add(kIOStringKeywordClass,                    RedTokenPredefType::KeywordClass());
        cVSILibTokenMap.Add(kIOStringKeywordCode,                     RedTokenPredefType::KeywordCode());
        cVSILibTokenMap.Add(kIOStringKeywordElse,                     RedTokenPredefType::KeywordElse());
        cVSILibTokenMap.Add(kIOStringKeywordEndif,                    RedTokenPredefType::KeywordEndif());
        cVSILibTokenMap.Add(kIOStringKeywordEndloop,                  RedTokenPredefType::KeywordEndloop());
        cVSILibTokenMap.Add(kIOStringKeywordFalse,                    RedTokenPredefType::KeywordFalse());
        cVSILibTokenMap.Add(kIOStringKeywordHeap,                     RedTokenPredefType::KeywordHeap());
        cVSILibTokenMap.Add(kIOStringKeywordIf,                       RedTokenPredefType::KeywordIf());
        cVSILibTokenMap.Add(kIOStringKeywordLet,                      RedTokenPredefType::KeywordLet());
        cVSILibTokenMap.Add(kIOStringKeywordList,                     RedTokenPredefType::KeywordList());
        cVSILibTokenMap.Add(kIOStringKeywordLog,                      RedTokenPredefType::KeywordLog());
        cVSILibTokenMap.Add(kIOStringKeywordLoop,                     RedTokenPredefType::KeywordLoop());
        cVSILibTokenMap.Add(kIOStringKeywordName,                     RedTokenPredefType::KeywordName());
        cVSILibTokenMap.Add(kIOStringKeywordNew,                      RedTokenPredefType::KeywordNew());
        cVSILibTokenMap.Add(kIOStringKeywordNumber,                   RedTokenPredefType::KeywordNumber());
        cVSILibTokenMap.Add(kIOStringKeywordParams,                   RedTokenPredefType::KeywordParams());
        cVSILibTokenMap.Add(kIOStringKeywordParent,                   RedTokenPredefType::KeywordParent());
        cVSILibTokenMap.Add(kIOStringKeywordRecord,                   RedTokenPredefType::KeywordRecord());
        cVSILibTokenMap.Add(kIOStringKeywordReturn,                   RedTokenPredefType::KeywordReturn());
        cVSILibTokenMap.Add(kIOStringKeywordRoutine,                  RedTokenPredefType::KeywordRoutine());
        cVSILibTokenMap.Add(kIOStringKeywordStack,                    RedTokenPredefType::KeywordStack());
        cVSILibTokenMap.Add(kIOStringKeywordString,                   RedTokenPredefType::KeywordString());
        cVSILibTokenMap.Add(kIOStringKeywordThen,                     RedTokenPredefType::KeywordThen());
        cVSILibTokenMap.Add(kIOStringKeywordTrue,                     RedTokenPredefType::KeywordTrue());
        cVSILibTokenMap.Add(kIOStringKeywordWhile,                    RedTokenPredefType::KeywordWhile());

        cVSILibTokenMap.Add(kIOStringKeywordAdd,                      RedTokenPredefType::KeywordShellAdd());
        cVSILibTokenMap.Add(kIOStringKeywordData,                     RedTokenPredefType::KeywordShellData());
        cVSILibTokenMap.Add(kIOStringKeywordExit,                     RedTokenPredefType::KeywordShellExit());
        cVSILibTokenMap.Add(kIOStringKeywordLib,                      RedTokenPredefType::KeywordShellLib());
        cVSILibTokenMap.Add(kIOStringKeywordLog,                      RedTokenPredefType::KeywordShellLog());
        cVSILibTokenMap.Add(kIOStringKeywordRun,                      RedTokenPredefType::KeywordShellRun());
        cVSILibTokenMap.Add(kIOStringKeywordInit,                     RedTokenPredefType::KeywordShellInit());
        cVSILibTokenMap.Add(kIOStringKeywordList,                     RedTokenPredefType::KeywordShellList());

        cVSILibTokenMap.Add(kIOStringSymbolAssignPlus,                RedTokenPredefType::SymbolAssignPlus());
        cVSILibTokenMap.Add(kIOStringSymbolAssignMinus,               RedTokenPredefType::SymbolAssignMinus());
        cVSILibTokenMap.Add(kIOStringSymbolAssignMultiply,            RedTokenPredefType::SymbolAssignMultiply());
        cVSILibTokenMap.Add(kIOStringSymbolAssignDivide,              RedTokenPredefType::SymbolAssignDivide());
        cVSILibTokenMap.Add(RedDataString("="),                           RedTokenPredefType::SymbolAssignEqual());

        cVSILibTokenMap.Add(kIOStringSymbolBracketOpen,               RedTokenPredefType::SymbolBracketOpen());
        cVSILibTokenMap.Add(kIOStringSymbolBracketClose,              RedTokenPredefType::SymbolBracketClose());
        cVSILibTokenMap.Add(kIOStringSymbolBracketOpenCurly,          RedTokenPredefType::SymbolBracketOpen());
        cVSILibTokenMap.Add(kIOStringSymbolBracketCloseCurly,         RedTokenPredefType::SymbolBracketClose());
        cVSILibTokenMap.Add(kIOStringSymbolBracketOpenSquare,         RedTokenPredefType::SymbolBracketOpenSquare());
        cVSILibTokenMap.Add(kIOStringSymbolBracketCloseSquare,        RedTokenPredefType::SymbolBracketCloseSquare());

        cVSILibTokenMap.Add(kIOStringSymbolCompareEqual,              RedTokenPredefType::SymbolCompareEqual());
        cVSILibTokenMap.Add(kIOStringSymbolCompareNotEqual,           RedTokenPredefType::SymbolCompareNotEqual());
        cVSILibTokenMap.Add(kIOStringSymbolCompareLessThan,           RedTokenPredefType::SymbolCompareLessThan());
        cVSILibTokenMap.Add(kIOStringSymbolCompareGreaterThan,        RedTokenPredefType::SymbolCompareGreaterThan());
        cVSILibTokenMap.Add(kIOStringSymbolCompareGreaterThanOrEqual, RedTokenPredefType::SymbolCompareGreaterThanOrEqual());
        cVSILibTokenMap.Add(kIOStringSymbolCompareLessThanOrEqual,    RedTokenPredefType::SymbolCompareLessThanOrEqual());

        cVSILibTokenMap.Add(kIOStringSymbolLogicAnd,                  RedTokenPredefType::SymbolLogicAnd());
        cVSILibTokenMap.Add(kIOStringSymbolLogicNot,                  RedTokenPredefType::SymbolLogicNot());
        cVSILibTokenMap.Add(kIOStringSymbolLogicOr,                   RedTokenPredefType::SymbolLogicOr());

        cVSILibTokenMap.Add(kIOStringSymbolOperatorPlus,              RedTokenPredefType::SymbolOperatorPlus());
        cVSILibTokenMap.Add(kIOStringSymbolOperatorMinus,             RedTokenPredefType::SymbolOperatorMinus());
        cVSILibTokenMap.Add(kIOStringSymbolOperatorMultiply,          RedTokenPredefType::SymbolOperatorMultiply());
        cVSILibTokenMap.Add(kIOStringSymbolOperatorDivide,            RedTokenPredefType::SymbolOperatorDivide());
        cVSILibTokenMap.Add(kIOStringSymbolOperatorPower,             RedTokenPredefType::SymbolOperatorPower());

        cVSILibTokenMap.Add(kIOStringSymbolComma,                     RedTokenPredefType::SymbolComma());
        cVSILibTokenMap.Add(kIOStringSymbolPeriod,                    RedTokenPredefType::SymbolPeriod());
        cVSILibTokenMap.Add(kIOStringSymbolDoubleColon,               RedTokenPredefType::SymbolDoubleColon());
    }}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


