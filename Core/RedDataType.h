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

class RedDataString;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Enumeration based class to encapsulate the possible RedData objects.
class RedDataType 
{
public:

    RedDataType(void)        { Init(); };
    void Init(void)          { eState = TEDataType::eDataTypeInvalid; };
    RedDataType* Clone(void) const { RedDataType* newT = new RedDataType(); newT->eState = eState;  return newT; };

    void SetInvalid(void)    { eState = TEDataType::eDataTypeInvalid; };
    void SetVoid(void)       { eState = TEDataType::eDataTypeVoid; };
    void SetBool(void)       { eState = TEDataType::eDataTypeBool; };
    void SetNum(void)        { eState = TEDataType::eDataTypeNum; };
    void SetChar(void)       { eState = TEDataType::eDataTypeChar; };
    void SetStr(void)        { eState = TEDataType::eDataTypeStr; };
    void SetList(void)       { eState = TEDataType::eDataTypeList; };
    void SetRecord(void)     { eState = TEDataType::eDataTypeRecord; };
    void SetVariant(void)    { eState = TEDataType::eDataTypeVariant; };

    bool IsValid(void)      const { return (eState != TEDataType::eDataTypeInvalid); };
    bool IsVoid(void)       const { return (eState == TEDataType::eDataTypeVoid); };
    bool IsBool(void)       const { return (eState == TEDataType::eDataTypeBool); };
    bool IsNum(void)        const { return (eState == TEDataType::eDataTypeNum); };
    bool IsChar(void)       const { return (eState == TEDataType::eDataTypeChar); };
    bool IsStr(void)        const { return (eState == TEDataType::eDataTypeStr); };
    bool IsList(void)       const { return (eState == TEDataType::eDataTypeList); };
    bool IsRecord(void)     const { return (eState == TEDataType::eDataTypeRecord); };
    bool IsVariant(void)    const { return (eState == TEDataType::eDataTypeVariant); };

    static RedDataType Invalid(void)    { return RedDataType(TEDataType::eDataTypeInvalid); };
    static RedDataType Void(void)       { return RedDataType(TEDataType::eDataTypeVoid); };
    static RedDataType Bool(void)       { return RedDataType(TEDataType::eDataTypeBool); };
    static RedDataType Num(void)        { return RedDataType(TEDataType::eDataTypeNum); };
    static RedDataType Char(void)       { return RedDataType(TEDataType::eDataTypeChar); };
    static RedDataType Str(void)        { return RedDataType(TEDataType::eDataTypeStr); };
    static RedDataType List(void)       { return RedDataType(TEDataType::eDataTypeList); };
    static RedDataType Record(void)     { return RedDataType(TEDataType::eDataTypeRecord); };
    static RedDataType Variant(void)    { return RedDataType(TEDataType::eDataTypeVariant); };

    int iState(void) const { return (int)eState; };

    RedDataString Name(void) const;

    void operator =(const RedDataType sourceT) { eState = sourceT.eState; };

protected:

    enum class TEDataType
    {
        eDataTypeInvalid = 0,
        eDataTypeVoid,
        eDataTypeBool,
        eDataTypeNum,
        eDataTypeChar,
        eDataTypeStr,
        eDataTypeList,
        eDataTypeRecord,
        eDataTypeVariant
    };

    RedDataType(TEDataType eNewState) : eState(eNewState) { };

private:
    TEDataType  eState;
};

static const RedDataType kDataTypeInvalid    = RedDataType::Invalid();
static const RedDataType kDataTypeVoid       = RedDataType::Void();
static const RedDataType kDataTypeBool       = RedDataType::Bool();
static const RedDataType kDataTypeNum        = RedDataType::Num();
static const RedDataType kDataTypeChar       = RedDataType::Char();
static const RedDataType kDataTypeStr        = RedDataType::Str();
static const RedDataType kDataTypeList       = RedDataType::List();
static const RedDataType kDataTypeRecord     = RedDataType::Record();
static const RedDataType kDataTypeVariant    = RedDataType::Variant();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataType& lhs, const RedDataType& rhs);
bool operator!=(const RedDataType& lhs, const RedDataType& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



