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

//void RedVariant::SetType(const RedDataType& t)
//{
//    // If we want to change to a boolean type
//    if (t.IsBool())
//    {
//        // If we have data, and its boolean, we don't want to change anything.
//        // Any other course of action is change.
//        if ((pData) && (pData->Type() == kDataTypeBool)) return;
//
//        // Delete any existing data
//        if (pData) delete pData;
//
//        // New data
//        pData = new RedBoolean();
//    }
//    else if (t.IsChar())
//    {
//        // If we have data, and its boolean, we don't want to change anything.
//        // Any other course of action is change.
//        if ((pData) && (pData->Type() == kDataTypeChar)) return;
//
//        // Delete any existing data
//        if (pData) delete pData;
//
//        // New data
//        pData = new RedChar();
//    }
//    else if (t.IsNum())
//    {
//        // If we have data, and its boolean, we don't want to change anything.
//        // Any other course of action is change.
//        if ((pData) && (pData->Type() == kDataTypeNum)) return;
//
//        // Delete any existing data
//        if (pData) delete pData;
//
//        // New data
//        pData = new RedNumber();
//    }
//    else if (t.IsStr())
//    {
//        // If we have data, and its boolean, we don't want to change anything.
//        // Any other course of action is change.
//        if ((pData) && (pData->Type() == kDataTypeStr)) return;
//
//        // Delete any existing data
//        if (pData) delete pData;
//
//        // New data
//        pData = new RedString();
//    }
//}

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

bool RedVariant::ExportTo(RedType* pExportToData)
{
    // first check both ethe data items are not null pointers
    if ((pData) && (pExportToData)) 
    {
        // check if the two types are the same
        if (pData->Type() == pExportToData->Type())
        {
            if (pExportToData->Type().IsNum())
            {
                RedNumber* pExportToNum = (RedNumber*)pExportToData;
                RedNumber* pDataNum     = (RedNumber*)pData;
                *pExportToNum = *pDataNum;
            }
            else if (pExportToData->Type().IsChar())
            {
                RedChar* pExportToChar = (RedChar*)pExportToData;
                RedChar* pDataChar     = (RedChar*)pData;
                *pExportToChar = *pDataChar;
            }
            else if (pExportToData->Type().IsStr())
            {
                RedString* pExportToStr = (RedString*)pExportToData;
                RedString* pDataStr     = (RedString*)pData;
                *pExportToStr = *pDataStr;
            }        

            return true;
        }
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedVariant::NumberValue(void) const
{
    RedNumber cNum;
    
    // Assign the data to the return type only if its numeric.
    if (pData->Type().IsNum())
    {
        RedNumber* pNumData = (RedNumber*)pData;
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
    
    return cStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma mark - Operators
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
#pragma mark - Comparison Operators
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

        // Number == Number
        if ( (lhs.Type().IsNum()) && (rhs.Type().IsNum()) )
        {
            if (lhs.NumberValue() != rhs.NumberValue())
                return true;
        }

        // String + String
        if ( (lhs.Type().IsStr()) && (rhs.Type().IsStr()) )
        {
            if (lhs.StringValue() != rhs.StringValue())
                return true;
        }
    }

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

