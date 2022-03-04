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

#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Complex Query routines
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsCommand(void) const
{
    if (IsCommandNew())    return true;
    if (IsCommandLet())    return true;
    if (IsCommandIf())     return true;
    if (IsCommandWhile())  return true;
    if (IsCommandPrint())  return true;
    if (IsCommandReturn()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsParse(void) const
{
    if (IsParseFuncCall()) return true;
    if (IsParseValue())    return true;
    if (IsParseVariable()) return true;
    if (IsParseBinaryOp()) return true;
    if (IsParseUnaryOp())  return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsLocation(void) const
{
    if (IsLocationHeap())      return true;
    if (IsLocationStack())     return true;
    if (IsLocationAttribute()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsType(void) const
{
    if (IsTypeBool())   return true;
    if (IsTypeChar())   return true;
    if (IsTypeList())   return true;
    if (IsTypeNumber()) return true;
    if (IsTypeRecord()) return true;
    if (IsTypeString()) return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsAssignOp(void) const
{
    if (IsBinaryOpAssignDivide())   return true;
    if (IsBinaryOpAssignEqual())    return true;
    if (IsBinaryOpAssignMinus())    return true;
    if (IsBinaryOpAssignMultiply()) return true;
    if (IsBinaryOpAssignPlus())     return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsLogicOp(void) const
{
    if (IsBinaryOpLogicAnd()) return true;
    if (IsBinaryOpLogicOr())  return true;
    if (IsUnaryOpLogicNot())  return true;

    return false;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsCompareOp(void) const
{
    if (IsBinaryOpCompareEqual())       return true;
    if (IsBinaryOpCompareNotEqual())    return true;
    if (IsBinaryOpCompareLessThan())    return true;
    if (IsBinaryOpCompareGreaterThan()) return true;

    return false;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsBinaryOp(void) const
{
    if (IsBinaryOpAssignDivide())       return true;
    if (IsBinaryOpAssignEqual())        return true;
    if (IsBinaryOpAssignMinus())        return true;
    if (IsBinaryOpAssignMultiply())     return true;
    if (IsBinaryOpAssignPlus())         return true;
    if (IsBinaryOpCompareEqual())       return true;
    if (IsBinaryOpCompareNotEqual())    return true;
    if (IsBinaryOpCompareLessThan())    return true;
    if (IsBinaryOpCompareGreaterThan()) return true;
    if (IsBinaryOpDivide())             return true;
    if (IsBinaryOpLogicAnd())           return true;
    if (IsBinaryOpLogicOr())            return true;
    if (IsBinaryOpMinus())              return true;
    if (IsBinaryOpMultiply())           return true;
    if (IsBinaryOpPlus())               return true;
    if (IsBinaryOpPower())              return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILangElement::IsUnaryOp(void) const
{
    if (IsUnaryOpMinus())    return true;
    if (IsUnaryOpLogicNot()) return true;

    return false;
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
// Data Type conversions, between the Core type, and the enumerations here for types
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataType RedVSILangElement::DataTypeForLangElemType(const RedVSILangElement& LangType)
{
    // Initialises to invalid
    RedDataType retType;

    if      (!LangType.IsType())       retType.SetInvalid();
    else if ( LangType.IsTypeBool())   retType.SetBool();
    else if ( LangType.IsTypeChar())   retType.SetChar();
    else if ( LangType.IsTypeList())   retType.SetList();
    else if ( LangType.IsTypeNumber()) retType.SetNum();
    else if ( LangType.IsTypeRecord()) retType.SetRecord();
    else if ( LangType.IsTypeString()) retType.SetStr();

    return retType;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILangElement RedVSILangElement::LangElemTypeForDataType(const RedDataType& CoreType)
{
    // Initialises to invalid
    RedVSILangElement retType;

    if      (CoreType.IsBool())    retType = kLangElementTypeBool;
    else if (CoreType.IsChar())    retType = kLangElementTypeChar;
    else if (CoreType.IsList())    retType = kLangElementTypeList;
    else if (CoreType.IsNum())     retType = kLangElementTypeNumber;
    else if (CoreType.IsRecord())  retType = kLangElementTypeRecord;
    else if (CoreType.IsStr())     retType = kLangElementTypeString;

    return retType;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
