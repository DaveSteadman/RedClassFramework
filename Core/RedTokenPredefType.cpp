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

#include "RedTokenPredefType.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTokenPredefType::Init(void) 
{
    eType = TEPredef::eDefaultInvalid; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsLocationKeyword(void) const
{
    if (IsKeywordAttribute()) return true;
    if (IsKeywordStack())     return true;
    if (IsKeywordHeap())      return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsTypeKeyword(void) const
{
    if (IsKeywordBool())    return true;
    if (IsKeywordChar())    return true;
    if (IsKeywordList())    return true;
    if (IsKeywordNumber())  return true;
    if (IsKeywordRecord())  return true;
    if (IsKeywordString())  return true;
    if (IsKeywordVariant()) return true;
    if (IsKeywordVoid())    return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsCommandKeyword(void) const
{  
    if (IsKeywordNew())     return true;
    if (IsKeywordLet())     return true;
    if (IsKeywordIf())      return true;
    if (IsKeywordElse())    return true;
    if (IsKeywordEndif())   return true;
    if (IsKeywordWhile())   return true;
    if (IsKeywordLoop())    return true;
    if (IsKeywordEndloop()) return true;
    if (IsKeywordLog())     return true;
    if (IsKeywordReturn())  return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsBoolKeyword(void) const
{
    if (IsKeywordTrue())  return true;
    if (IsKeywordFalse()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsLibraryKeyword(void) const
{
    if (IsKeywordName())    return true;
    if (IsKeywordClass())   return true;
    if (IsKeywordRoutine()) return true;
    if (IsKeywordParams())  return true;
    if (IsKeywordParent())  return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsShellAreaKeyword(void) const
{
    if (IsKeywordData())  return true;
    if (IsKeywordHelp())  return true;
    if (IsKeywordLib())   return true;
    if (IsKeywordLog())   return true;
    if (IsKeywordRun())   return true;
    if (IsKeywordExit())  return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsShellActionKeyword(void) const
{
    if (IsKeywordAdd())  return true;
    if (IsKeywordInit()) return true;
    if (IsKeywordList()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsOperatorSymbol(void) const
{
    if (IsAssignOpSymbol())      return true;
    if (IsLogicOpSymbol())       return true;
    if (IsBinaryLogicOpSymbol()) return true;
    if (IsCompareOpSymbol())     return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsAssignOpSymbol(void) const
{
    if (IsSymbolAssignDivide())   return true;
    if (IsSymbolAssignEqual())    return true;
    if (IsSymbolAssignMinus())    return true;
    if (IsSymbolAssignMultiply()) return true;
    if (IsSymbolAssignPlus())     return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsLogicOpSymbol(void) const
{
    if (IsSymbolLogicAnd()) return true;
    if (IsSymbolLogicOr())  return true;
    if (IsSymbolLogicNot()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsBinaryLogicOpSymbol(void) const
{
    if (IsSymbolLogicAnd()) return true;
    if (IsSymbolLogicOr())  return true;

    return false;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsCompareOpSymbol(void) const
{
    if (IsSymbolCompareEqual())       return true;
    if (IsSymbolCompareNotEqual())    return true;
    if (IsSymbolCompareLessThan())    return true;
    if (IsSymbolCompareGreaterThan()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsBinaryOpSymbol(void) const
{
    if (IsSymbolAssignDivide())       return true;
    if (IsSymbolAssignEqual())        return true;
    if (IsSymbolAssignMinus())        return true;
    if (IsSymbolAssignMultiply())     return true;
    if (IsSymbolAssignPlus())         return true;

    if (IsSymbolCompareEqual())       return true;
    if (IsSymbolCompareNotEqual())    return true;
    if (IsSymbolCompareLessThan())    return true;
    if (IsSymbolCompareGreaterThan()) return true;

    if (IsSymbolLogicAnd())           return true;
    if (IsSymbolLogicOr())            return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefType::IsSeparatorSymbol(void) const
{
    if (IsSymbolStringContent()) return true;
    if (IsSymbolBracketOpen())   return true;
    if (IsSymbolBracketClose())  return true;
    if (IsSymbolComma())         return true;
    if (IsSymbolPeriod())        return true;
    if (IsSymbolDoubleColon())   return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs)
{
    if (lhs.iElem() == rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs)
{
    if (lhs.iElem() != rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
