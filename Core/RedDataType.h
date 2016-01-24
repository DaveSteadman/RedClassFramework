
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "RedCoreConsts.h"

namespace Red {
namespace Core {

using namespace Red::Core;

class RedString;

/// Enumeration based class to encapsulate the possible RedType objects.
class RedDataType 
{
public:

    RedDataType(void)        { Init(); };

    void Init(void)          { eState=eDataTypeInvalid; };
    void SetBool(void)       { eState=eDataTypeBool; };
    void SetChar(void)       { eState=eDataTypeChar; };
    void SetList(void)       { eState=eDataTypeList; };
    void SetNum(void)        { eState=eDataTypeNum; };
    void SetRecord(void)     { eState=eDataTypeRecord; };
    void SetStr(void)        { eState=eDataTypeStr; };
    void SetVariant(void)    { eState=eDataTypeVariant; };

    const int IsValid(void)      const { return (eState!=eDataTypeInvalid); };
    const int IsBool(void)       const { return (eState==eDataTypeBool); };
    const int IsChar(void)       const { return (eState==eDataTypeChar); };
    const int IsList(void)       const { return (eState==eDataTypeList); };
    const int IsNum(void)        const { return (eState==eDataTypeNum); };
    const int IsRecord(void)     const { return (eState==eDataTypeRecord); };
    const int IsStr(void)        const { return (eState==eDataTypeStr); };
    const int IsVariant(void)    const { return (eState==eDataTypeVariant); };

    static const RedDataType Invalid(void)    { return RedDataType(eDataTypeInvalid); };
    static const RedDataType Bool(void)       { return RedDataType(eDataTypeBool); };
    static const RedDataType Char(void)       { return RedDataType(eDataTypeChar); };
    static const RedDataType List(void)       { return RedDataType(eDataTypeList); };
    static const RedDataType Num(void)        { return RedDataType(eDataTypeNum); };
    static const RedDataType Record(void)     { return RedDataType(eDataTypeRecord); };
    static const RedDataType Str(void)        { return RedDataType(eDataTypeStr); };
    static const RedDataType Variant(void)    { return RedDataType(eDataTypeVariant); };

    const int iState(void) const { return (int)eState; };

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



