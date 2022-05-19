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

    void SetInvalid(void)    { eState = TEDataType::eDataTypeInvalid; };
    void SetBool(void)       { eState = TEDataType::eDataTypeBool; };
    void SetChar(void)       { eState = TEDataType::eDataTypeChar; };
    void SetList(void)       { eState = TEDataType::eDataTypeList; };
    void SetNum(void)        { eState = TEDataType::eDataTypeNum; };
    void SetRecord(void)     { eState = TEDataType::eDataTypeRecord; };
    void SetStr(void)        { eState = TEDataType::eDataTypeStr; };
    void SetVariant(void)    { eState = TEDataType::eDataTypeVariant; };
    void SetVoid(void)       { eState = TEDataType::eDataTypeVoid; };

    bool IsValid(void)      const { return (eState != TEDataType::eDataTypeInvalid); };
    bool IsBool(void)       const { return (eState == TEDataType::eDataTypeBool); };
    bool IsChar(void)       const { return (eState == TEDataType::eDataTypeChar); };
    bool IsList(void)       const { return (eState == TEDataType::eDataTypeList); };
    bool IsNum(void)        const { return (eState == TEDataType::eDataTypeNum); };
    bool IsRecord(void)     const { return (eState == TEDataType::eDataTypeRecord); };
    bool IsStr(void)        const { return (eState == TEDataType::eDataTypeStr); };
    bool IsVariant(void)    const { return (eState == TEDataType::eDataTypeVariant); };
    bool IsVoid(void)       const { return (eState == TEDataType::eDataTypeVoid); };

    static RedDataType Invalid(void)    { return RedDataType(TEDataType::eDataTypeInvalid); };
    static RedDataType Bool(void)       { return RedDataType(TEDataType::eDataTypeBool); };
    static RedDataType Char(void)       { return RedDataType(TEDataType::eDataTypeChar); };
    static RedDataType List(void)       { return RedDataType(TEDataType::eDataTypeList); };
    static RedDataType Num(void)        { return RedDataType(TEDataType::eDataTypeNum); };
    static RedDataType Record(void)     { return RedDataType(TEDataType::eDataTypeRecord); };
    static RedDataType Str(void)        { return RedDataType(TEDataType::eDataTypeStr); };
    static RedDataType Variant(void)    { return RedDataType(TEDataType::eDataTypeVariant); };
    static RedDataType Void(void)       { return RedDataType(TEDataType::eDataTypeVoid); };

    int iState(void) const { return (int)eState; };

    RedDataString Name(void);

protected:

    enum class TEDataType
    {
        eDataTypeInvalid = 0,
        eDataTypeBool,
        eDataTypeChar,
        eDataTypeList,
        eDataTypeNum,
        eDataTypeRecord,
        eDataTypeStr,
        eDataTypeVariant,
        eDataTypeVoid
    };

    RedDataType(TEDataType eNewState) : eState(eNewState) { };

private:
    TEDataType  eState;
};

static const RedDataType kDataTypeInvalid    = RedDataType::Invalid();
static const RedDataType kDataTypeBool       = RedDataType::Bool();
static const RedDataType kDataTypeChar       = RedDataType::Char();
static const RedDataType kDataTypeList       = RedDataType::List();
static const RedDataType kDataTypeNum        = RedDataType::Num();
static const RedDataType kDataTypeRecord     = RedDataType::Record();
static const RedDataType kDataTypeStr        = RedDataType::Str();
static const RedDataType kDataTypeVariant    = RedDataType::Variant();
static const RedDataType kDataTypeVoid       = RedDataType::Void();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataType& lhs, const RedDataType& rhs);
bool operator!=(const RedDataType& lhs, const RedDataType& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



