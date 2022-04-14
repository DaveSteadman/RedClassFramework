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

#include "RedData.h"

#include "RedDataRecord.h"
#include "RedDataBoolean.h"
#include "RedDataChar.h"
#include "RedDataNumber.h"
#include "RedDataString.h"
#include "RedDataVariant.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inhertied
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataRecord::Clone(void) const 
{
    RedDataRecord* pNewObj = new RedDataRecord();

    // delete the attrib list, replacing it with a cloned one.
    if (pNewObj->pAttribList)
    {
        delete pNewObj->pAttribList;
        pNewObj->pAttribList = NULL;
    }
    pNewObj->pAttribList = pAttribList->Clone();

    return (RedData*)pNewObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataRecord::CreateAddReturn(const RedDataString& cNewAttribName, const RedDataType& NewAttribType)
{
    RedData* retData = RedData::NewRedObj(NewAttribType);

    pAttribList->Add(cNewAttribName, retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataRecord::CreateAddReturn(const char* strNewAttribName, const RedDataType& NewAttribType)
{
    RedData* retData = RedData::NewRedObj(NewAttribType);

    pAttribList->Add(RedDataString(strNewAttribName), retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

///void RedDataRecord::Add(const RedDataString& cNewAttribName, int iVal)
///{ 
///    RedDataNumber* pNewNum = new RedDataNumber(iVal);
///    pAttribList->Add(cNewAttribName, (RedData* )pNewNum);
///};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedDataRecord::Add(const RedDataString& cNewAttribName, const RedDataNumber numVal)
//{
//    pAttribList->Add(cNewAttribName, (RedData*)numVal->Clone());
//}
//
/// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedDataRecord::Add(const RedDataString& cNewAttribName, const char* strVal)
//{
//    RedDataString* pNewStr = new RedDataString(strVal);
//    pAttribList->Add(cNewAttribName, (RedData*)pNewStr);
//}
//
/// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//void RedDataRecord::Add(const RedDataString& cNewAttribName, const bool bVal)
//{
//    RedDataBoolean* pNewBool = new RedDataBoolean(bVal);
//    pAttribList->Add(cNewAttribName, (RedData*)pNewBool);
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataType RedDataRecord::TypeForName(const RedDataString& cAttribName)
{
    RedData* pData = NULL;

    if (FindFieldPtr(cAttribName, pData))
        return pData->Type();
    else
        return kDataTypeInvalid;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataRecord::PtrForName(const RedDataString& cAttribName)
{
    RedData* pData = NULL;
    if (FindFieldPtr(cAttribName, pData))
        return pData;
    else
        return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataRecord::NameForIndex(const unsigned uIndex) const
{
    RedDataString cRetStr = "<NoName>";

    if (pAttribList->FindIdByIndex(uIndex, cRetStr))
        return cRetStr;
    else
        return "<NotFound>";
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


RedData* RedDataRecord::PtrForIndex(const unsigned uIndex) const
{
    RedData* retData = NULL;

    if (pAttribList->FindDataByIndex(uIndex, retData))
        return retData;
    else
        return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataRecord::operator =(const RedDataRecord& cNewVal)
{
    Init();

    delete pAttribList;
    pAttribList = cNewVal.pAttribList->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




