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
#include "RedMapList.h"
#include "RedMapListIterator.h"

#include "RedTokenPredefType.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// A singleton class to maintain the mapping between an enum-type of predefined keyword/symbols and the 
// string we would see in any IO.
// Ref: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTokenPredefMap
{

// - Singleton Specific content - - - - - - - - - - - - - - - - - - - - - 
public:
    static RedTokenPredefMap* getInstance() {
        return (!m_instanceSingleton) ?
            m_instanceSingleton = new RedTokenPredefMap 
            : m_instanceSingleton;
    }

private:

    void SetupTokenMap(void);

    // private constructor and destructor
    RedTokenPredefMap() { SetupTokenMap(); };
    ~RedTokenPredefMap() { cTokenMap.DelAll(); };

    // private copy constructor and assignment operator
    RedTokenPredefMap(const RedTokenPredefMap&);
    RedTokenPredefMap& operator=(const RedTokenPredefMap&);

// - Token Map functionality - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
public:


    bool      FindPredefFromString(RedDataString cCheckStr, RedTokenPredefType cElem);
    bool      FindStringFromPredef(RedTokenPredefType& cCheckElem, RedDataString& cStr);
    unsigned  CountMatchCandidates(RedDataString& cCheckStr);

private:

    //void    Add(const RedDataString& cStr, const RedTokenPredefType& cElem);

    typedef RedMapList<RedDataString, RedTokenPredefType>         MapListType;
    typedef RedMapListIterator<RedDataString, RedTokenPredefType> MapListItType;

    MapListType cTokenMap;

    static RedTokenPredefMap* m_instanceSingleton;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDataString kIOStringKeywordBool                     = RedDataString("bool");
static const RedDataString kIOStringKeywordChar                     = RedDataString("char");
static const RedDataString kIOStringKeywordList                     = RedDataString("list");
static const RedDataString kIOStringKeywordNumber                   = RedDataString("number");
static const RedDataString kIOStringKeywordRecord                   = RedDataString("record");
static const RedDataString kIOStringKeywordString                   = RedDataString("string");
static const RedDataString kIOStringKeywordVariant                  = RedDataString("variant");

static const RedDataString kIOStringKeywordAttrib                   = RedDataString("attrib");
static const RedDataString kIOStringKeywordHeap                     = RedDataString("heap");
static const RedDataString kIOStringKeywordStack                    = RedDataString("stack");

static const RedDataString kIOStringKeywordAdd                      = RedDataString("add");
static const RedDataString kIOStringKeywordClass                    = RedDataString("class");
static const RedDataString kIOStringKeywordCode                     = RedDataString("code");
static const RedDataString kIOStringKeywordData                     = RedDataString("data");
static const RedDataString kIOStringKeywordElse                     = RedDataString("else");
static const RedDataString kIOStringKeywordEndif                    = RedDataString("endif");
static const RedDataString kIOStringKeywordEndloop                  = RedDataString("endloop");
static const RedDataString kIOStringKeywordExit                     = RedDataString("exit");
static const RedDataString kIOStringKeywordFalse                    = RedDataString("false");
static const RedDataString kIOStringKeywordIf                       = RedDataString("if");
static const RedDataString kIOStringKeywordInit                     = RedDataString("init");
static const RedDataString kIOStringKeywordLet                      = RedDataString("let");
static const RedDataString kIOStringKeywordLib                      = RedDataString("lib");
static const RedDataString kIOStringKeywordLog                      = RedDataString("log");
static const RedDataString kIOStringKeywordLoop                     = RedDataString("loop");
static const RedDataString kIOStringKeywordName                     = RedDataString("name");
static const RedDataString kIOStringKeywordNew                      = RedDataString("new");
static const RedDataString kIOStringKeywordParams                   = RedDataString("params");
static const RedDataString kIOStringKeywordParent                   = RedDataString("parent");
static const RedDataString kIOStringKeywordReturn                   = RedDataString("return");
static const RedDataString kIOStringKeywordRoutine                  = RedDataString("routine");
static const RedDataString kIOStringKeywordRun                      = RedDataString("run");
static const RedDataString kIOStringKeywordThen                     = RedDataString("then");
static const RedDataString kIOStringKeywordTrue                     = RedDataString("true");
static const RedDataString kIOStringKeywordWhile                    = RedDataString("while");

static const RedDataString kIOStringSymbolAssignPlus                = RedDataString("+=");
static const RedDataString kIOStringSymbolAssignMinus               = RedDataString("-=");
static const RedDataString kIOStringSymbolAssignMultiply            = RedDataString("*=");
static const RedDataString kIOStringSymbolAssignDivide              = RedDataString("/=");
static const RedDataString kIOStringSymbolAssignEqual               = RedDataString("=");

static const RedDataString kIOStringSymbolBracketOpen               = RedDataString("(");
static const RedDataString kIOStringSymbolBracketClose              = RedDataString(")");
static const RedDataString kIOStringSymbolBracketOpenCurly          = RedDataString("{");
static const RedDataString kIOStringSymbolBracketCloseCurly         = RedDataString("}");
static const RedDataString kIOStringSymbolBracketOpenSquare         = RedDataString("[");
static const RedDataString kIOStringSymbolBracketCloseSquare        = RedDataString("]");

static const RedDataString kIOStringSymbolCompareEqual              = RedDataString("==");
static const RedDataString kIOStringSymbolCompareNotEqual           = RedDataString("!=");
static const RedDataString kIOStringSymbolCompareLessThan           = RedDataString("<");
static const RedDataString kIOStringSymbolCompareGreaterThan        = RedDataString(">");
static const RedDataString kIOStringSymbolCompareGreaterThanOrEqual = RedDataString("<=");
static const RedDataString kIOStringSymbolCompareLessThanOrEqual    = RedDataString(">=");

static const RedDataString kIOStringSymbolOperatorPlus              = RedDataString("+");
static const RedDataString kIOStringSymbolOperatorMinus             = RedDataString("-");
static const RedDataString kIOStringSymbolOperatorMultiply          = RedDataString("*");
static const RedDataString kIOStringSymbolOperatorDivide            = RedDataString("/");
static const RedDataString kIOStringSymbolOperatorPower             = RedDataString("^");

static const RedDataString kIOStringSymbolLogicAnd                  = RedDataString("&&");
static const RedDataString kIOStringSymbolLogicNot                  = RedDataString("!!");
static const RedDataString kIOStringSymbolLogicOr                   = RedDataString("||");

static const RedDataString kIOStringSymbolComma                     = RedDataString(",");
static const RedDataString kIOStringSymbolPeriod                    = RedDataString(".");
static const RedDataString kIOStringSymbolDoubleColon               = RedDataString("::");
static const RedDataString kIOStringSymbolStringContent             = RedDataString("'");

static const RedDataString kIOStringWhitespaceSpace                 = RedDataString(" ");

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
