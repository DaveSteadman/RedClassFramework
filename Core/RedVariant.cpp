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

#include "RedVariant.h"
#include "RedBoolean.h"

#include "RedChar.h"
#include "RedString.h"
#include "RedNumber.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::Init(void)
{
    if (pData)
    {
        delete pData;
        pData = REDNULL;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedDataType RedVariant::Type(void) const
{
    if (pData)
        return pData->Type();

    return kDataTypeInvalid;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVariant::Clone(void) const
{
    RedVariant* pNewData = new RedVariant();
    
    if (pData)
        pNewData->SetValue(pData->Clone());

    return (RedType*)pNewData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Set a new value to the object. It maintains its own data, so any existing
// data is deleted and the input is cloned.
void RedVariant::SetValue(const RedType* pNewData)
{
    Init();
    if (pNewData)
        pData = pNewData->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::SetValue(const RedVariant& cDataItem)
{ 
    Init();
    if (cDataItem.IsValid())
        pData = cDataItem.pData->Clone(); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::SetValue(const RedBoolean& cNewBool)
{
    Init();
    pData = new RedBoolean(cNewBool);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::SetValue(const RedNumber& cNewNum)
{
    Init();
    pData = new RedNumber(cNewNum);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::SetValue(const RedChar& cNewCh)
{
    Init();
    pData = new RedChar(cNewCh);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::SetValue(const RedString& cNewStr)
{
    Init();
    pData = new RedString(cNewStr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedVariant::Value(void)
{
    if (pData)
        return pData;
    
    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVariant::ExportTo(RedType* pExportToData) const
{
    bool is_success = false;

    // first check both ethe data items are not null pointers
    if ((pData) && (pExportToData)) 
    {
        // check if the two types are the same
        if (pData->Type() == pExportToData->Type())
        {
            if (pExportToData->Type().IsBool())
            {
                RedBoolean* pSourceDataBool = dynamic_cast<RedBoolean*>(pData);
                RedBoolean* pExportToBool   = dynamic_cast<RedBoolean*>(pExportToData);
                *pExportToBool              = *pSourceDataBool;
                is_success                  = true;
            }
            else if (pExportToData->Type().IsChar())
            {
                RedChar* pSourceDataChar    = dynamic_cast<RedChar*>(pData);
                RedChar* pExportToChar      = dynamic_cast<RedChar*>(pExportToData);
                *pExportToChar              = *pSourceDataChar;
                is_success                  = true;
            }
            else if (pExportToData->Type().IsNum())
            {
                RedNumber* pSourceDataNum   = dynamic_cast<RedNumber*>(pData);
                RedNumber* pExportToNum     = dynamic_cast<RedNumber*>(pExportToData);
                *pExportToNum               = *pSourceDataNum;
                is_success                  = true;
            }
            else if (pExportToData->Type().IsStr())
            {
                RedString* pSourceDataStr   = dynamic_cast<RedString*>(pData);
                RedString* pExportToStr     = dynamic_cast<RedString*>(pExportToData);
                *pExportToStr               = *pSourceDataStr;
                is_success                  = true;
            }
        }

        // Additional special cases

        // Exporting a one character string into a char type
        else if (pData->Type().IsStr() && pExportToData->Type().IsChar())
        {
            RedString* pSourceDataStr = dynamic_cast<RedString*>(pData);
            RedChar*   pExportToChr   = dynamic_cast<RedChar*>(pExportToData);

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

const RedBoolean RedVariant::BoolValue(void) const
{
    RedBoolean cBool;
    
    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsBool())
    {
        RedBoolean* pBoolData = dynamic_cast<RedBoolean*>(pData);
        cBool = *pBoolData;
    }
    return cBool;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedVariant::NumberValue(void) const
{
    RedNumber cNum;
    
    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsNum())
    {
        RedNumber* pNumData = dynamic_cast<RedNumber*>(pData);
        cNum = *pNumData; 
    }
    return cNum;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedVariant::StringValue(void) const
{
    RedString cStr;
    
    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsStr())
    {
        RedString* pStrData = (RedString*)pData;
        cStr = *pStrData;
    }
    if (pData->Type().IsBool())
    {
        RedBoolean b;
        ExportTo(&b);
        if (b.IsYes())
            cStr = "yes";
        if (b.IsNo())
            cStr = "no";
    }
    if (pData->Type().IsNum())
    {
        RedNumber* pNumData = dynamic_cast<RedNumber*>(pData);
        cStr = pNumData->DecimalString();
    }

    return cStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::operator =(const RedType* pNewData)
{
    Init();

    pData = pNewData->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVariant::operator =(const RedVariant& cVarData)
{
    Init();

    if (cVarData.pData)
        pData = cVarData.pData->Clone();        
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVariant::operator+(const RedVariant& cVarData)
{
    RedVariant cRetVal;
    
    // Number + Number
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedNumber cRes = NumberValue() + cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    // String + String
    if ( (pData->Type().IsStr()) && (cVarData.Type().IsStr()) )
    {
        RedString cRes = StringValue() + cVarData.StringValue();
        cRetVal.SetValue(&cRes);
    }
    
    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVariant::operator-(const RedVariant& cVarData)
{
    RedVariant cRetVal;
    
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedNumber cRes = *((RedNumber*)pData) - cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }
    
    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVariant::operator*(const RedVariant& cVarData)
{
    RedVariant cRetVal;
    
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedNumber cRes = *((RedNumber*)pData) * cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }
    
    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVariant RedVariant::operator/(const RedVariant& cVarData)
{
    RedVariant cRetVal;
    
    if ( (pData->Type().IsNum()) && (cVarData.Type().IsNum()) )
    {
        RedNumber cRes = *((RedNumber*)pData) / cVarData.NumberValue();
        cRetVal.SetValue(&cRes);
    }

    return cRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVariant& lhs, const RedVariant& rhs)
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

bool operator!=(const RedVariant& lhs, const RedVariant& rhs)
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

bool operator >(const RedVariant& lhs, const RedVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() > rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <(const RedVariant& lhs, const RedVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() < rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator>=(const RedVariant& lhs, const RedVariant& rhs)
{
    if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
    {
        return ( lhs.NumberValue() >= rhs.NumberValue() );
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator<=(const RedVariant& lhs, const RedVariant& rhs)
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

