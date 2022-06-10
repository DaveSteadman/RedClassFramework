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

#include "RedData.h"
#include "RedDataType.h"
#include "RedDataBoolean.h"
#include "RedDataChar.h"
#include "RedDataList.h"
#include "RedDataRecord.h"
#include "RedDataString.h"
#include "RedDataNumber.h"
#include "RedCoreConsts.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class to hold any of the predefined data types.
// Used in expressions, to pass a common type between parse tree elements.

class RedDataVariant : public RedData
{
public:

    RedDataVariant(void):pData(NULL) { };
    RedDataVariant(const RedData& cDataItem)        { pData = cDataItem.Clone(); };
    RedDataVariant(const RedDataVariant& cDataItem) { SetValue(cDataItem); };
    RedDataVariant(const RedDataBoolean& cNewBool)  { SetValue(cNewBool); };
    RedDataVariant(const RedDataChar& cNewCh)       { SetValue(RedDataChar(cNewCh)); };
    RedDataVariant(const RedDataNumber& cNewNum)    { SetValue(cNewNum); };
    RedDataVariant(const RedDataRecord& cNewRec)    { SetValue(RedDataRecord(cNewRec)); };
    RedDataVariant(const RedDataString& cNewStr)    { SetValue(RedDataString(cNewStr)); };
    RedDataVariant(const int val)                   { SetValue(RedDataNumber(val)); };
    RedDataVariant(const double val)                { SetValue(RedDataNumber(val)); };
    RedDataVariant(const char* val)                 { SetValue(RedDataString(val)); };
    RedDataVariant(const bool val)                  { SetValue(RedDataBoolean(val)); };
    ~RedDataVariant(void)                           { Init(); };

    // Inherited: RedData
    void                Init(void);
    RedDataType         Type(void) const;
    RedData*            Clone(void) const;

    bool                IsValid(void) const  { return (pData!=NULL); };
    RedDataType         DataType(void) const { return (pData==NULL) ? kDataTypeInvalid : pData->Type(); };

    // Set a new value to the object. Any existing data is deleted and the input is cloned.
    void                SetValue(const RedData* pNewData)         { Init(); if (pNewData) pData = pNewData->Clone(); };
    void                SetValue(const RedDataBoolean& cNewBool)  { Init(); pData = new RedDataBoolean(cNewBool); };
    void                SetValue(const RedDataNumber&  cNewNum)   { Init(); pData = new RedDataNumber(cNewNum); };
    void                SetValue(const RedDataChar&    cNewCh)    { Init(); pData = new RedDataChar(cNewCh); };
    void                SetValue(const RedDataString&  cNewStr)   { Init(); pData = new RedDataString(cNewStr); };
    void                SetValue(const RedDataList&    cNewLst)   { Init(); pData = new RedDataList(cNewLst); };
    void                SetValue(const RedDataRecord&  cNewRec)   { Init(); pData = new RedDataRecord(cNewRec); };
    void                SetValue(const RedDataVariant& cDataItem) { Init(); if (cDataItem.IsValid()) pData = cDataItem.pData->Clone(); };

    void                SetValue(const int      val) { SetValue(RedDataNumber(val));      };
    void                SetValue(const unsigned val) { SetValue(RedDataNumber((int)val)); };
    void                SetValue(const double   val) { SetValue(RedDataNumber(val));      };
    void                SetValue(const bool     val) { SetValue(RedDataBoolean(val));     };
    void                SetValue(const char*    val) { SetValue(RedDataString(val));      };

    RedData*            Value(void);
    bool                ExportTo(RedData* pExportToData) const;
    RedDataBoolean      BoolValue(void) const;
    RedDataNumber       NumberValue(void) const;
    RedDataString       StringValue(void) const;
    RedDataChar         CharValue(void) const;
    RedDataList         ListValue(void) const;
    RedDataRecord       RecordValue(void) const;
    double              DoubleValue(void) const;
    int                 IntegerValue(void) const;

    bool                IsSuccessVal(void) const;

    void operator =(const RedData* pData);
    void operator =(const RedDataVariant& n);

    void operator =(const RedDataBoolean& cNewData) { SetValue(&cNewData); };
    void operator =(const RedDataChar&    cNewData) { SetValue(&cNewData); };
    void operator =(const RedDataString&  cNewData) { SetValue(&cNewData); };
    void operator =(const RedDataNumber&  cNewData) { SetValue(&cNewData); };
    void operator =(const bool            val)      { SetValue(RedDataBoolean(val)); };
    void operator =(const char            val)      { SetValue(RedDataChar(val)); };
    void operator =(const char*           val)      { SetValue(RedDataString(val)); };
    void operator =(const int             val)      { SetValue(RedDataNumber(val)); };
    void operator =(const double          val)      { SetValue(RedDataNumber(val)); };

    RedDataVariant operator+(const RedDataVariant& cVarData);
    RedDataVariant operator-(const RedDataVariant& cVarData);
    RedDataVariant operator*(const RedDataVariant& cVarData);
    RedDataVariant operator/(const RedDataVariant& cVarData);

private:
    RedData* pData = NULL;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataVariant& lhs, const RedDataVariant& rhs);
bool operator!=(const RedDataVariant& lhs, const RedDataVariant& rhs);
bool operator >(const RedDataVariant& lhs, const RedDataVariant& rhs);
bool operator <(const RedDataVariant& lhs, const RedDataVariant& rhs);
bool operator>=(const RedDataVariant& lhs, const RedDataVariant& rhs);
bool operator<=(const RedDataVariant& lhs, const RedDataVariant& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

