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

#include "RedType.h"
#include "RedDataType.h"
#include "RedBoolean.h"
#include "RedChar.h"
#include "RedRecord.h"
#include "RedString.h"
#include "RedNumber.h"
#include "RedCoreConsts.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class to hold any of the predefined data types. Primarily of use in
/// expressions, to pass a common type between parse tree elements.
class RedVariant : public RedType
{
public:

    RedVariant(void):pData(NULL) { };
    RedVariant(const RedType& cDataItem):pData(NULL)    { cDataItem.Clone(); };
    RedVariant(const RedVariant& cDataItem):pData(NULL) { SetValue(cDataItem); };
    RedVariant(const RedBoolean& cNewBool):pData(NULL)  { SetValue(cNewBool); };
    RedVariant(const RedChar& cNewCh):pData(NULL)       { SetValue(RedChar(cNewCh)); };
    RedVariant(const RedNumber& cNewNum):pData(NULL)    { SetValue(cNewNum); };
    RedVariant(const RedRecord& cNewRec):pData(NULL)    { SetValue(RedRecord(cNewRec)); };
    RedVariant(const RedString& cNewStr):pData(NULL)    { SetValue(RedString(cNewStr)); };
    RedVariant(const int val):pData(NULL)               { SetValue(RedNumber(val)); };
    RedVariant(const double val):pData(NULL)            { SetValue(RedNumber(val)); };
    RedVariant(const char* val):pData(NULL)             { SetValue(RedString(val)); };
    RedVariant(const bool val):pData(NULL)              { SetValue(RedBoolean(val)); };
    ~RedVariant(void)                                   { Init(); };

    // Inherited: RedType
    void                Init(void);
    RedDataType         Type(void) const;
    RedType*            Clone(void) const;

    bool                IsValid(void) const { return (pData!=NULL); };

    void                SetValue(const RedVariant& cDataItem);
    void                SetValue(const RedType*    pNewData);
    void                SetValue(const RedBoolean& cNewBool);
    void                SetValue(const RedChar&    cNewCh);
    void                SetValue(const RedNumber&  cNewNum);
    void                SetValue(const RedRecord&  cNewRec);
    void                SetValue(const RedString&  cNewStr);
    void                SetValue(const int         val) { SetValue(RedNumber(val)); };
    void                SetValue(const unsigned    val) { SetValue(RedNumber((int)val)); };
    void                SetValue(const double      val) { SetValue(RedNumber(val)); };
    void                SetValue(const bool        val) { SetValue(RedBoolean(val)); };

    RedType*            Value(void);
    bool                ExportTo(RedType* pExportToData) const;
    RedBoolean          BoolValue(void) const;
    RedNumber           NumberValue(void) const;
    RedString           StringValue(void) const;

    bool                IsSuccessVal(void) const;

    void operator =(const RedType* pData);
    void operator =(const RedVariant& n);
    void operator =(const RedBoolean& cNewData) { SetValue(&cNewData); };
    void operator =(const RedChar&    cNewData) { SetValue(&cNewData); };
    void operator =(const RedString&  cNewData) { SetValue(&cNewData); };
    void operator =(const RedNumber&  cNewData) { SetValue(&cNewData); };
    void operator =(const bool        val)      { SetValue(RedBoolean(val)); };
    void operator =(const char        val)      { SetValue(RedChar(val)); };
    void operator =(const char*       val)      { SetValue(RedString(val)); };
    void operator =(const int         val)      { SetValue(RedNumber(val)); };
    void operator =(const unsigned    val)      { SetValue(RedNumber((int)val)); };
    void operator =(const double      val)      { SetValue(RedNumber(val)); };

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

