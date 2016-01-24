
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSITokenElementMap.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


class RedVSILibTokenMap
{
public:

    RedVSILibTokenMap(void) { SetupTokenMap(); };

    void SetupTokenMap(void);

    RedVSITokenElementMap cVSILibTokenMap;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedString kVSIIOElementKeywordArray   = RedString("array");
static const RedString kVSIIOElementKeywordAttrib  = RedString("attrib");
static const RedString kVSIIOElementKeywordBool    = RedString("bool");
static const RedString kVSIIOElementKeywordChar    = RedString("char");
static const RedString kVSIIOElementKeywordClass   = RedString("class");
static const RedString kVSIIOElementKeywordCode    = RedString("code");
static const RedString kVSIIOElementKeywordElse    = RedString("else");
static const RedString kVSIIOElementKeywordEndif   = RedString("endif");
static const RedString kVSIIOElementKeywordEndloop = RedString("endloop");
static const RedString kVSIIOElementKeywordHeap    = RedString("heap");
static const RedString kVSIIOElementKeywordIf      = RedString("if");
static const RedString kVSIIOElementKeywordLet     = RedString("let");
static const RedString kVSIIOElementKeywordLoop    = RedString("loop");
static const RedString kVSIIOElementKeywordName    = RedString("name");
static const RedString kVSIIOElementKeywordNew     = RedString("new");
static const RedString kVSIIOElementKeywordNumber  = RedString("number");
static const RedString kVSIIOElementKeywordParams  = RedString("params");
static const RedString kVSIIOElementKeywordParent  = RedString("parent");
static const RedString kVSIIOElementKeywordReturn  = RedString("return");
static const RedString kVSIIOElementKeywordRoutine = RedString("routine");
static const RedString kVSIIOElementKeywordStack   = RedString("local");
static const RedString kVSIIOElementKeywordString  = RedString("string");
static const RedString kVSIIOElementKeywordThen    = RedString("then");
static const RedString kVSIIOElementKeywordWhile   = RedString("while");

static const RedString kVSIIOElementSymbolAssignPlus     = RedString("+=");
static const RedString kVSIIOElementSymbolAssignMinus    = RedString("-=");
static const RedString kVSIIOElementSymbolAssignMultiply = RedString("*=");
static const RedString kVSIIOElementSymbolAssignDivide   = RedString("/=");
static const RedString kVSIIOElementSymbolAssignEqual    = RedString("=");
static const RedString kVSIIOElementSymbolPlus           = RedString("+");
static const RedString kVSIIOElementSymbolMinus          = RedString("-");
static const RedString kVSIIOElementSymbolMultiply       = RedString("*");
static const RedString kVSIIOElementSymbolDivide         = RedString("/");
static const RedString kVSIIOElementSymbolPower          = RedString("^");

//
//        cVSILibTokenMap.Add(RedString("=="),      RedVSIIOElement::SymbolCompareEqual());
//        cVSILibTokenMap.Add(RedString("!="),      RedVSIIOElement::SymbolCompareNotEqual());
//        cVSILibTokenMap.Add(RedString("<"),       RedVSIIOElement::SymbolCompareLessThan());
//        cVSILibTokenMap.Add(RedString(">"),       RedVSIIOElement::SymbolCompareGreaterThan());
//        cVSILibTokenMap.Add(RedString("<="),      RedVSIIOElement::SymbolCompareGreaterThanOrEqual());
//        cVSILibTokenMap.Add(RedString(">="),      RedVSIIOElement::SymbolCompareLessThanOrEqual());
//
//        cVSILibTokenMap.Add(RedString("&&"),      RedVSIIOElement::SymbolLogicAnd());
//        cVSILibTokenMap.Add(RedString("!!"),      RedVSIIOElement::SymbolLogicNot());
//        cVSILibTokenMap.Add(RedString("||"),      RedVSIIOElement::SymbolLogicOr());
//
//        cVSILibTokenMap.Add(RedString("("),       RedVSIIOElement::SymbolOpenBracket());
//        cVSILibTokenMap.Add(RedString(")"),       RedVSIIOElement::SymbolCloseBracket());
//        cVSILibTokenMap.Add(RedString("{"),       RedVSIIOElement::SymbolOpenBracket());
//        cVSILibTokenMap.Add(RedString("}"),       RedVSIIOElement::SymbolCloseBracket());
//        cVSILibTokenMap.Add(RedString(","),       RedVSIIOElement::SymbolComma());
//        cVSILibTokenMap.Add(RedString("."),       RedVSIIOElement::SymbolPeriod());
//        cVSILibTokenMap.Add(RedString("::"),      RedVSIIOElement::SymbolDoubleColon());
//        cVSILibTokenMap.Add(RedString("'"),       RedVSIIOElement::SymbolStringContent());

} // VSI
} // Red

