// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedDataList.h"

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

RedType* RedDataList::Clone(void) const 
{
    RedDataList* pNewObj = new RedDataList();

    // delete the attrib list, replacing it with a cloned one.
    if (pNewObj->pList)
    {
        delete pNewObj->pList;
        pNewObj->pList = NULL;
    }
    pNewObj->pList = pList->Clone();

    return (RedType*)pNewObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::InitToSize(unsigned uNumItems, RedDataType cItemType)
{
    // Clear any existing list
    if (pList) { delete pList; pList = NULL; }

    pList = new RedTypeList;

    RedType* pNewListObj = NULL;
    for (unsigned i = 0; i < uNumItems; i++)
    {
        if (cItemType.IsBool())    pNewListObj = new RedDataBoolean();
        if (cItemType.IsChar())    pNewListObj = new RedDataChar();
        if (cItemType.IsList())    pNewListObj = new RedDataList();
        if (cItemType.IsNum())     pNewListObj = new RedDataNumber();
        if (cItemType.IsRecord())  pNewListObj = new RedDataRecord();
        if (cItemType.IsStr())     pNewListObj = new RedDataString();
        if (cItemType.IsNum())     pNewListObj = new RedDataNumber();
        if (cItemType.IsVariant()) pNewListObj = new RedDataVariant();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*

RedType* RedDataList::CreateAndAdd(const RedDataString& cNewAttribName, const RedDataType& NewAttribType)
{
    RedType* retData = CreateObjectOfType(NewAttribType);

    pAttribList->Add(cNewAttribName, retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedDataList::CreateAndAdd(const char* strNewAttribName, const RedDataType& NewAttribType)
{
    RedType* retData = CreateObjectOfType(NewAttribType);

    pAttribList->Add(RedDataString(strNewAttribName), retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedDataList::CreateObjectOfType(const RedDataType& NewAttribType)
{
    RedType* retData = NULL;

    if      (NewAttribType.IsBool())    retData = new RedDataBoolean;
    else if (NewAttribType.IsChar())    retData = new RedDataChar;
    //else if (NewAttribType.IsList())    retData = new RedL;
    else if (NewAttribType.IsNum())     retData = new RedDataNumber;
    else if (NewAttribType.IsRecord())  retData = new RedDataList;
    else if (NewAttribType.IsStr())     retData = new RedDataString;
    else if (NewAttribType.IsVariant()) retData = new RedDataVariant;

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::operator =(const RedDataList& cNewVal)
{
    Init();

    delete pAttribList;
    pAttribList = cNewVal.pAttribList->Clone();
}


*/ 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




