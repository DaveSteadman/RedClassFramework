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

#include "RedDataVariant.h"
#include "RedDataBoolean.h"
#include "RedDataChar.h"
#include "RedDataString.h"
#include "RedDataNumber.h"
#include "RedDataActions.h"

#include "RedTokenPredefMap.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataVariant::Init(void)
{
    if (pData)
    {
        delete pData;
        pData = NULL;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataType RedDataVariant::Type(void) const
{
    if (pData)
        return pData->Type();

    return kDataTypeInvalid;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataVariant::Clone(void) const
{
    RedDataVariant* pNewData = new RedDataVariant();

    if (pData)
        pNewData->SetValue(pData->Clone());

    return dynamic_cast<RedData*>(pNewData);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataVariant::Value(void)
{
    if (pData)
        return pData;
    
    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataVariant::ExportTo(RedData* pExportToData) const
{
    bool is_success = false;

    // first check both ethe data items are not null pointers, and they are not the same.
    if ( ((pData != NULL) && (pExportToData != NULL)) &&
         (pData != pExportToData) )
    {
        // check if the two types are the same
        if (pData->Type() == pExportToData->Type())
        {
            if (pExportToData->Type().IsBool())
            {
                RedDataBoolean* pSourceDataBool = dynamic_cast<RedDataBoolean*>(pData);
                RedDataBoolean* pExportToBool   = dynamic_cast<RedDataBoolean*>(pExportToData);
                *pExportToBool                  = *pSourceDataBool;
                is_success                      = true;
            }
            else if (pExportToData->Type().IsChar())
            {
                RedDataChar* pSourceDataChar    = dynamic_cast<RedDataChar*>(pData);
                RedDataChar* pExportToChar      = dynamic_cast<RedDataChar*>(pExportToData);
                *pExportToChar                  = *pSourceDataChar;
                is_success                      = true;
            }
            else if (pExportToData->Type().IsNum())
            {
                RedDataNumber* pSourceDataNum   = dynamic_cast<RedDataNumber*>(pData);
                RedDataNumber* pExportToNum     = dynamic_cast<RedDataNumber*>(pExportToData);
                *pExportToNum                   = *pSourceDataNum;
                is_success                      = true;
            }
            else if (pExportToData->Type().IsStr())
            {
                RedDataString* pSourceDataStr   = dynamic_cast<RedDataString*>(pData);
                RedDataString* pExportToStr     = dynamic_cast<RedDataString*>(pExportToData);
                *pExportToStr                   = *pSourceDataStr;
                is_success                      = true;
            }
            else if (pExportToData->Type().IsRecord())
            {
                RedDataRecord* pSourceDataRec   = dynamic_cast<RedDataRecord*>(pData);
                RedDataRecord* pExportToRec     = dynamic_cast<RedDataRecord*>(pExportToData);
                *pExportToRec                   = *pSourceDataRec;
                is_success                      = true;
            }
        }

        // Additional special cases

        // Exporting a one character string into a char type
        else if (pData->Type().IsStr() && pExportToData->Type().IsChar())
        {
            RedDataString* pSourceDataStr = dynamic_cast<RedDataString*>(pData);
            RedDataChar*   pExportToChr   = dynamic_cast<RedDataChar*>(pExportToData);

            if (pSourceDataStr->Length() == 1)
            {
                *pExportToChr = pSourceDataStr->FirstChar();
                is_success = true;
            }
        }
    }
    return is_success;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataBoolean RedDataVariant::BoolValue(void) const
{
    RedDataBoolean cBool;

    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsBool())
    {
        RedDataBoolean* pBoolData = dynamic_cast<RedDataBoolean*>(pData);
        cBool = *pBoolData;
    }
    else if (pData->Type().IsNum())
    {
        RedDataNumber* pNumData = dynamic_cast<RedDataNumber*>(pData);

        if (!pNumData->IsZero())
            cBool.SetTrue();
        else
            cBool.SetFalse();
    }
    else if (pData->Type().IsStr())
    {
        RedDataString* pStr = dynamic_cast<RedDataString*>(pData);

        if (*pStr == kIOStringKeywordTrue)
            cBool.SetTrue();
        if (*pStr == kIOStringKeywordFalse)
            cBool.SetFalse();
    }
    return cBool;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataVariant::NumberValue(void) const
{
    RedDataNumber cNum;

    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsNum())
    {
        RedDataNumber* pNumData = dynamic_cast<RedDataNumber*>(pData);
        cNum = *pNumData; 
    }
    return cNum;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataVariant::StringValue(void) const
{
    RedDataString cStr = "<No String Representation>";
    
    if (pData == NULL)
    {
        cStr = "<NULL PDATA>";
    }
    // Assign the data to the return type only if its numeric.
    else if (pData->Type().IsStr())
    {
        RedDataString* pStrData = dynamic_cast<RedDataString*>(pData);
        cStr = *pStrData;
    }
    else if (pData->Type().IsChar())
    {
        RedDataChar* pChrData = dynamic_cast<RedDataChar*>(pData);
        cStr = *pChrData;
    }
    else if (pData->Type().IsBool())
    {
        RedDataBoolean* pBoolData = dynamic_cast<RedDataBoolean*>(pData);
        if (pBoolData->IsTrue())
            cStr = kIOStringKeywordTrue;
        else
            cStr = kIOStringKeywordFalse;
    }
    else if (pData->Type().IsNum())
    {
        RedDataNumber* pNumData = dynamic_cast<RedDataNumber*>(pData);
        cStr = RedDataActions::StringFromNumber(*pNumData);
    }
    else if (pData->Type().IsList())
    {
        RedDataList* pListData = dynamic_cast<RedDataList*>(pData);

        cStr = "<list " + RedDataActions::StringFromInt(pListData->NumItems()) + " items>";
    }
    else if (pData->Type().IsRecord())
    {
        RedDataRecord* pRecData = dynamic_cast<RedDataRecord*>(pData);

        cStr = "<record >";
        cStr += RedDataActions::StringFromInt(pRecData->NumItems());
        cStr += " items>";
    }

    return cStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataChar RedDataVariant::CharValue(void) const
{
    RedDataChar cChr;

    if (pData->Type().IsStr())
    {
        RedDataString* pStrData = dynamic_cast<RedDataString*>(pData);
        cChr = pStrData->FirstCharObj();
    }
    else if (pData->Type().IsBool())
    {
        RedDataBoolean* pBoolData = dynamic_cast<RedDataBoolean*>(pData);
        if (pBoolData->IsTrue())
            cChr = '1';
        else
            cChr = '0';
    }
    else if (pData->Type().IsChar())
    {
        RedDataChar* pChrData = dynamic_cast<RedDataChar*>(pData);
        cChr = *pChrData;
    }

    return cChr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

double RedDataVariant::DoubleValue(void) const
{
    double retDbl = 0.0;

    if (pData->Type().IsNum())
    {
        RedDataNumber* pNumData = dynamic_cast<RedDataNumber*>(pData);
        retDbl = pNumData->DoubleValue();
    }
    else if (pData->Type().IsStr())
    {
        RedDataString* pStrData = dynamic_cast<RedDataString*>(pData);
        RedDataNumber tempNum = RedDataActions::NumberFromString(*pStrData);
        retDbl = tempNum.DoubleValue();
    }

    return retDbl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedDataVariant::IntegerValue(void) const
{
    int retInt = 0;

    if (pData->Type().IsNum())
    {
        RedDataNumber* pNumData = dynamic_cast<RedDataNumber*>(pData);
        retInt = pNumData->IntegerValue();
    }
    else if (pData->Type().IsBool())
    {
        RedDataBoolean* pBoolData = dynamic_cast<RedDataBoolean*>(pData);
        if (pBoolData->IsTrue())
            retInt = 1;
        else
            retInt = 0;
    }
    else if (pData->Type().IsStr())
    {
        RedDataString* pStrData = dynamic_cast<RedDataString*>(pData);
        RedDataNumber tempNum = RedDataActions::NumberFromString(*pStrData);
        retInt = tempNum.IntegerValue();
    }

    return retInt;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataList RedDataVariant::ListValue(void) const
{
    RedDataList cLst;

    return cLst;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataRecord RedDataVariant::RecordValue(void) const
{
    RedDataRecord cRec;

    return cRec;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataVariant::IsSuccessVal(void) const
{
    if (pData->Type().IsNum())
    {
        if (!NumberValue().IsZero())
            return true;
    }
    else if (pData->Type().IsBool())
    {
        if (BoolValue().IsTrue())
            return true;
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataVariant::operator =(const RedData* pNewData)
{
    Init();

    pData = pNewData->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataVariant::operator =(const RedDataVariant& cVarData)
{
    Init();

    if (cVarData.pData)
        pData = cVarData.pData->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedDataVariant::operator+(const RedDataVariant& cVarData)
{
    RedDataVariant cRetVal;
    
    // Number + Number
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedDataNumber cRes = NumberValue() + cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    // String + String
    if ( (pData->Type().IsStr()) && (cVarData.Type().IsStr()) )
    {
        RedDataString cRes = StringValue() + cVarData.StringValue();
        cRetVal.SetValue(&cRes);
    }
    
    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedDataVariant::operator-(const RedDataVariant& cVarData)
{
    RedDataVariant cRetVal;
    
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedDataNumber cRes = *((RedDataNumber*)pData) - cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedDataVariant::operator*(const RedDataVariant& cVarData)
{
    RedDataVariant cRetVal;
    
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedDataNumber cRes = *((RedDataNumber*)pData) * cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataVariant RedDataVariant::operator/(const RedDataVariant& cVarData)
{
    RedDataVariant cRetVal;

    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedDataNumber cRes = *((RedDataNumber*)pData) / cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if (!lhs.IsValid() &&  rhs.IsValid()) return false;
    if ( lhs.IsValid() && !rhs.IsValid()) return false;
    if (!lhs.IsValid() && !rhs.IsValid()) return true;

    if (lhs.IsValid() && rhs.IsValid())
    {
        // check the types are the same
        if (lhs.Type() != rhs.Type())
            return false;

        // Number == Number
        if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
        {
            if (lhs.NumberValue() == rhs.NumberValue())
                return true;
        }

        // String + String
        if ( (lhs.Type().IsStr()) && (rhs.Type().IsStr()) )
        {
            if (lhs.StringValue() == rhs.StringValue())
                return true;
        }
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if (!lhs.IsValid() &&  rhs.IsValid()) return true;
    if ( lhs.IsValid() && !rhs.IsValid()) return true;
    if (!lhs.IsValid() && !rhs.IsValid()) return false;

    if (lhs.IsValid() && rhs.IsValid())
    {
        // check the types are the same
        if (lhs.Type() != rhs.Type())
            return true;

        // Bool + Bool
        if ( (lhs.Type().IsBool()) && (rhs.Type().IsBool()) )
        {
            if (lhs.BoolValue() != rhs.BoolValue())
                return true;
            else
                return false;
        }

        // Number == Number
        else if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
        {
            if (lhs.NumberValue() != rhs.NumberValue())
                return true;
            else
                return false;
        }

        // String + String
        else if ( (lhs.Type().IsStr()) && (rhs.Type().IsStr()) )
        {
            if (lhs.StringValue() != rhs.StringValue())
                return true;
            else
                return false;
        }
    }

    // We've left every IF statement without performing a decent comparison. Returning false at this
    // point doesn't convey that lack of validity, so throwing is a better alternative.
    throw;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator >(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() > rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() < rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator>=(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() >= rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator<=(const RedDataVariant& lhs, const RedDataVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() <= rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

