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

#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Complex Query routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsCommand(void) const
{
    if (IsCommandNew())    return 1;
    if (IsCommandLet())    return 1;
    if (IsCommandIf())     return 1;
    if (IsCommandWhile())  return 1;
    if (IsCommandReturn()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsParse(void) const
{
    if (IsParseFuncCall()) return 1;
    if (IsParseValue())    return 1;
    if (IsParseVariable()) return 1;
    if (IsParseBinaryOp()) return 1;
    if (IsParseUnaryOp())  return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsLocation(void) const
{
    if (IsLocationHeap())      return 1;
    if (IsLocationStack())     return 1;
    if (IsLocationAttribute()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsType(void) const
{
    if (IsTypeArray())  return 1;
    if (IsTypeBool())   return 1;
    if (IsTypeChar())   return 1;
    if (IsTypeNumber()) return 1;
    if (IsTypeString()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsAssignOp(void) const
{
    if (IsBinaryOpAssignDivide())   return 1;
    if (IsBinaryOpAssignEqual())    return 1;
    if (IsBinaryOpAssignMinus())    return 1;
    if (IsBinaryOpAssignMultiply()) return 1;
    if (IsBinaryOpAssignPlus())     return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsLogicOp(void) const
{
    if (IsBinaryOpLogicAnd()) return 1;
    if (IsBinaryOpLogicOr())  return 1;
    if (IsUnaryOpLogicNot())  return 1;

    return 0;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsCompareOp(void) const
{
    if (IsBinaryOpCompareEqual())       return 1;
    if (IsBinaryOpCompareNotEqual())    return 1;
    if (IsBinaryOpCompareLessThan())    return 1;
    if (IsBinaryOpCompareGreaterThan()) return 1;

    return 0;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsBinaryOp(void) const
{
    if (IsBinaryOpAssignDivide())       return 1;
    if (IsBinaryOpAssignEqual())        return 1;
    if (IsBinaryOpAssignMinus())        return 1;
    if (IsBinaryOpAssignMultiply())     return 1;
    if (IsBinaryOpAssignPlus())         return 1;
    if (IsBinaryOpCompareEqual())       return 1;
    if (IsBinaryOpCompareNotEqual())    return 1;
    if (IsBinaryOpCompareLessThan())    return 1;
    if (IsBinaryOpCompareGreaterThan()) return 1;
    if (IsBinaryOpDivide())             return 1;
    if (IsBinaryOpLogicAnd())           return 1;
    if (IsBinaryOpLogicOr())            return 1;
    if (IsBinaryOpMinus())              return 1;
    if (IsBinaryOpMultiply())           return 1;
    if (IsBinaryOpPlus())               return 1;
    if (IsBinaryOpPower())              return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILangElement::IsUnaryOp(void) const
{
    if (IsUnaryOpMinus())    return 1;
    if (IsUnaryOpLogicNot()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVSILangElement& lhs, const RedVSILangElement& rhs)
{
    if (lhs.iElem() == rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedVSILangElement& lhs, const RedVSILangElement& rhs)
{
    if (lhs.iElem() != rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
