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

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedDataString.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// A List data type, parented on RedType, so we can create collections of them and use them as VSI variables.

class RedDataList : public RedType
{
public:

    RedDataList(void) { pList = NULL; };
    RedDataList(unsigned uNumItems, RedDataType eItemType) { InitToSize(uNumItems, eItemType); };

    ~RedDataList(void) { pList->DelAll(); };

    // Inherited: RedType
    RedDataType Type(void) const { return RedDataType::List(); };
    RedType*          Clone(void) const;
    void              Init(void) { pList->DelAll(); };

    void              InitToSize(unsigned uNumItems, RedDataType eItemType);

    // Create And Add
    // void        CloneAndAdd (const RedDataString& cNewAttribName, const RedType* pNewAttrib) { pAttribList->Add(cNewAttribName,              pNewAttrib->Clone()); };
    // void        CloneAndAdd (const char* strNewAttribName,    const RedType* pNewAttrib) { pAttribList->Add(RedDataString(strNewAttribName), pNewAttrib->Clone()); };
    // void        Add         (const RedDataString& cNewAttribName, RedType* pNewAttrib)       { pAttribList->Add(cNewAttribName,              pNewAttrib); };
    // void        Add         (const char* strNewAttribName,    RedType* pNewAttrib)       { pAttribList->Add(RedDataString(strNewAttribName), pNewAttrib); };
    // RedType*    CreateAndAdd(const RedDataString& cNewAttribName, const RedDataType& NewAttribType);
    // RedType*    CreateAndAdd(const char* strNewAttribName,    const RedDataType& NewAttribType);


    // Remove
    void        DelAll(void) { pList->DelAll(); };

    unsigned    NumItems(void) const { return pList->NumItems(); };

    // Operators
    void operator =(const RedDataList& cNewVal);

private:

    RedType* CreateObjectOfType(const RedDataType& NewAttribType);

    typedef RedDoubleLinkedList<RedType*>   RedTypeList;
    typedef RedDoubleLinkedList<RedType*>   RedTypeListIterator;

    // Attributes
    RedTypeList* pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
