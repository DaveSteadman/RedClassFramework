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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Enumeration based class to encapsulate the possible RedType objects.
class RedDataType 
{
public:

    RedDataType(void)        { Init(); };
    void Init(void)          { eState=eDataTypeInvalid; };

    void SetInvalid(void)    { eState=eDataTypeInvalid; };
    void SetBool(void)       { eState=eDataTypeBool; };
    void SetChar(void)       { eState=eDataTypeChar; };
    void SetList(void)       { eState=eDataTypeList; };
    void SetNum(void)        { eState=eDataTypeNum; };
    void SetRecord(void)     { eState=eDataTypeRecord; };
    void SetStr(void)        { eState=eDataTypeStr; };
    void SetVariant(void)    { eState=eDataTypeVariant; };

    bool IsValid(void)      const { return (eState!=eDataTypeInvalid); };
    bool IsBool(void)       const { return (eState==eDataTypeBool); };
    bool IsChar(void)       const { return (eState==eDataTypeChar); };
    bool IsList(void)       const { return (eState==eDataTypeList); };
    bool IsNum(void)        const { return (eState==eDataTypeNum); };
    bool IsRecord(void)     const { return (eState==eDataTypeRecord); };
    bool IsStr(void)        const { return (eState==eDataTypeStr); };
    bool IsVariant(void)    const { return (eState==eDataTypeVariant); };

    static RedDataType Invalid(void)    { return RedDataType(eDataTypeInvalid); };
    static RedDataType Bool(void)       { return RedDataType(eDataTypeBool); };
    static RedDataType Char(void)       { return RedDataType(eDataTypeChar); };
    static RedDataType List(void)       { return RedDataType(eDataTypeList); };
    static RedDataType Num(void)        { return RedDataType(eDataTypeNum); };
    static RedDataType Record(void)     { return RedDataType(eDataTypeRecord); };
    static RedDataType Str(void)        { return RedDataType(eDataTypeStr); };
    static RedDataType Variant(void)    { return RedDataType(eDataTypeVariant); };

    int iState(void) const { return (int)eState; };

protected:

    enum TEDataType
    {
        eDataTypeInvalid = 0,
        eDataTypeBool,
        eDataTypeChar,
        eDataTypeList,
        eDataTypeNum,
        eDataTypeRecord,
        eDataTypeStr,
        eDataTypeVariant
    };

    void ClearOtherTypeStr(void);

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataType& lhs, const RedDataType& rhs);
bool operator!=(const RedDataType& lhs, const RedDataType& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



