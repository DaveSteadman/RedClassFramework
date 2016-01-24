
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedDataType.h"
#include "RedChar.h"
#include "RedString.h"
#include "RedNumber.h"

namespace Red {
namespace Core {

/// Class to hold any of the predefined data types. Primarily of use in
/// expressions, to pass a common type between parse tree elements.
class RedVariant : public RedType
{
public:

    RedVariant(void):pData(0) { };
    RedVariant(const RedType& cDataItem):pData(0)    { cDataItem.Clone(); };
    RedVariant(const RedVariant& cDataItem):pData(0) { SetValue(cDataItem); };

    RedVariant(const RedNumber& cNewNum):pData(0)    { SetValue(cNewNum); };
    RedVariant(const RedChar& cNewCh):pData(0)       { SetValue(RedChar(cNewCh)); };
    RedVariant(const RedString& cNewStr):pData(0)    { SetValue(RedString(cNewStr)); };
    RedVariant(const int val):pData(0)               { SetValue(RedNumber(val)); };
    RedVariant(const double val):pData(0)            { SetValue(RedNumber(val)); };


    ~RedVariant(void);

    // Inherited: RedType
    void                Init(void);
    const RedDataType   Type(void) const;
    RedType*            Clone(void) const;

    const int           IsValid(void) const { return (pData!=REDNULL); };

    void                SetValue(const RedVariant& cDataItem);
    void                SetValue(const RedType* pNewData);
    void                SetValue(const RedNumber& cNewNum);
    void                SetValue(const RedChar& cNewCh);
    void                SetValue(const RedString& cNewStr);
    void                SetValue(const int val) { SetValue(RedNumber(val)); };
    void                SetValue(const double val) { SetValue(RedNumber(val)); };

    RedType*            Value(void);

    int                 ExportTo(RedType* pExportToData);
    
    const RedNumber     NumberValue(void) const;
    const RedString     StringValue(void) const;

    void operator =(const RedType* pData);
    void operator =(const RedVariant& n);
    void operator =(const RedChar cNewData)    { SetValue(&cNewData); };
    void operator =(const RedString cNewData)  { SetValue(&cNewData); };
    void operator =(const RedNumber cNewData)  { SetValue(&cNewData); };

    void operator =(const int val)             { SetValue(RedNumber(val));   };
    void operator =(const double val)          { SetValue(RedNumber(val)); };
    void operator =(const char val)            { SetValue(RedChar(val)); };
    void operator =(const char* val)           { SetValue(RedString(val)); };

    RedVariant operator+(const RedVariant& cVarData);
    RedVariant operator-(const RedVariant& cVarData);
    RedVariant operator*(const RedVariant& cVarData);
    RedVariant operator/(const RedVariant& cVarData);

private:
    RedType* pData;
};

typedef RedSmartPtr<RedVariant> RedVariantSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVariant& lhs, const RedVariant& rhs);
bool operator!=(const RedVariant& lhs, const RedVariant& rhs);
bool operator >(const RedVariant& lhs, const RedVariant& rhs);
bool operator <(const RedVariant& lhs, const RedVariant& rhs);
bool operator>=(const RedVariant& lhs, const RedVariant& rhs);
bool operator<=(const RedVariant& lhs, const RedVariant& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

