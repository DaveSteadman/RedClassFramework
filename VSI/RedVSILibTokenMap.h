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

#include "RedCoreNamespace.h"
#include "RedVSITokenElementMap.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSILibTokenMap
{
public:

    RedVSILibTokenMap(void) { SetupTokenMap(); };

    void SetupTokenMap(void);

    RedVSITokenElementMap cVSILibTokenMap;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDataString kVSIIOElementKeywordAttrib        = RedDataString("attrib");
static const RedDataString kVSIIOElementKeywordBool          = RedDataString("bool");
static const RedDataString kVSIIOElementKeywordChar          = RedDataString("char");
static const RedDataString kVSIIOElementKeywordClass         = RedDataString("class");
static const RedDataString kVSIIOElementKeywordCode          = RedDataString("code");
static const RedDataString kVSIIOElementKeywordElse          = RedDataString("else");
static const RedDataString kVSIIOElementKeywordEndif         = RedDataString("endif");
static const RedDataString kVSIIOElementKeywordEndloop       = RedDataString("endloop");
static const RedDataString kVSIIOElementKeywordFalse         = RedDataString("false");
static const RedDataString kVSIIOElementKeywordHeap          = RedDataString("heap");
static const RedDataString kVSIIOElementKeywordIf            = RedDataString("if");
static const RedDataString kVSIIOElementKeywordLet           = RedDataString("let");
static const RedDataString kVSIIOElementKeywordList          = RedDataString("list");
static const RedDataString kVSIIOElementKeywordLog           = RedDataString("log");
static const RedDataString kVSIIOElementKeywordLoop          = RedDataString("loop");
static const RedDataString kVSIIOElementKeywordName          = RedDataString("name");
static const RedDataString kVSIIOElementKeywordNew           = RedDataString("new");
static const RedDataString kVSIIOElementKeywordNo            = RedDataString("no");
static const RedDataString kVSIIOElementKeywordNumber        = RedDataString("number");
static const RedDataString kVSIIOElementKeywordParams        = RedDataString("params");
static const RedDataString kVSIIOElementKeywordParent        = RedDataString("parent");
static const RedDataString kVSIIOElementKeywordReturn        = RedDataString("return");
static const RedDataString kVSIIOElementKeywordRoutine       = RedDataString("routine");
static const RedDataString kVSIIOElementKeywordStack         = RedDataString("local");
static const RedDataString kVSIIOElementKeywordRecord        = RedDataString("record");
static const RedDataString kVSIIOElementKeywordString        = RedDataString("string");
static const RedDataString kVSIIOElementKeywordThen          = RedDataString("then");
static const RedDataString kVSIIOElementKeywordTrue          = RedDataString("true");
static const RedDataString kVSIIOElementKeywordWhile         = RedDataString("while");
static const RedDataString kVSIIOElementKeywordYes           = RedDataString("yes");

static const RedDataString kVSIIOElementSymbolAssignPlus     = RedDataString("+=");
static const RedDataString kVSIIOElementSymbolAssignMinus    = RedDataString("-=");
static const RedDataString kVSIIOElementSymbolAssignMultiply = RedDataString("*=");
static const RedDataString kVSIIOElementSymbolAssignDivide   = RedDataString("/=");
static const RedDataString kVSIIOElementSymbolAssignEqual    = RedDataString("=");
static const RedDataString kVSIIOElementSymbolPlus           = RedDataString("+");
static const RedDataString kVSIIOElementSymbolMinus          = RedDataString("-");
static const RedDataString kVSIIOElementSymbolMultiply       = RedDataString("*");
static const RedDataString kVSIIOElementSymbolDivide         = RedDataString("/");
static const RedDataString kVSIIOElementSymbolPower          = RedDataString("^");

//
//        cVSILibTokenMap.Add(RedDataString("=="),      RedVSIIOElement::SymbolCompareEqual());
//        cVSILibTokenMap.Add(RedDataString("!="),      RedVSIIOElement::SymbolCompareNotEqual());
//        cVSILibTokenMap.Add(RedDataString("<"),       RedVSIIOElement::SymbolCompareLessThan());
//        cVSILibTokenMap.Add(RedDataString(">"),       RedVSIIOElement::SymbolCompareGreaterThan());
//        cVSILibTokenMap.Add(RedDataString("<="),      RedVSIIOElement::SymbolCompareGreaterThanOrEqual());
//        cVSILibTokenMap.Add(RedDataString(">="),      RedVSIIOElement::SymbolCompareLessThanOrEqual());
//
//        cVSILibTokenMap.Add(RedDataString("&&"),      RedVSIIOElement::SymbolLogicAnd());
//        cVSILibTokenMap.Add(RedDataString("!!"),      RedVSIIOElement::SymbolLogicNot());
//        cVSILibTokenMap.Add(RedDataString("||"),      RedVSIIOElement::SymbolLogicOr());
//
//        cVSILibTokenMap.Add(RedDataString("("),       RedVSIIOElement::SymbolOpenBracket());
//        cVSILibTokenMap.Add(RedDataString(")"),       RedVSIIOElement::SymbolCloseBracket());
//        cVSILibTokenMap.Add(RedDataString("{"),       RedVSIIOElement::SymbolOpenBracket());
//        cVSILibTokenMap.Add(RedDataString("}"),       RedVSIIOElement::SymbolCloseBracket());
//        cVSILibTokenMap.Add(RedDataString(","),       RedVSIIOElement::SymbolComma());
//        cVSILibTokenMap.Add(RedDataString("."),       RedVSIIOElement::SymbolPeriod());
//        cVSILibTokenMap.Add(RedDataString("::"),      RedVSIIOElement::SymbolDoubleColon());
//        cVSILibTokenMap.Add(RedDataString("'"),       RedVSIIOElement::SymbolStringContent());

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

