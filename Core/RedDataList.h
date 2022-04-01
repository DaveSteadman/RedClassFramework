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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedDataBoolean.h"
#include "RedDataNumber.h"
#include "RedDataString.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// A List data type, parented on RedType, so we can create collections of them and use them as VSI variables.
// All items stored as pointers, either addig from externally created objects, or by value that creates the object on the fly.
// All objects deleted when deleted from the collection.

class RedDataList : public RedType
{
public:

    RedDataList(void) { pList = NULL; pList = new RedTypeList; };
    RedDataList(unsigned uNumItems, RedDataType eItemType) { InitToSize(uNumItems, eItemType); };

    ~RedDataList(void) { pList->DelAll(); delete pList; };

    // Inherited: RedType
    RedDataType       Type(void) const { return RedDataType::List(); };
    RedType*          Clone(void) const;
    void              Init(void) { pList->DelAll(); };

    void              InitToSize(unsigned uNumItems, RedDataType eItemType);

    void        CloneAndAdd(const RedType* pNewAttrib) { pList->AddLast(pNewAttrib->Clone()); };
    void        AddByPtr(RedType* pNewAttrib)          { pList->AddLast(pNewAttrib); };

    // Generic add operations
    RedType*    CreateAddReturn(const RedDataType& NewAttribType);

    // Shortcut add operations
    void        AddByValue(const int iVal)     { pList->AddLast(new RedDataNumber(iVal));   };
    void        AddByValue(const char* strVal) { pList->AddLast(new RedDataString(strVal)); };
    void        AddByValue(const bool bVal)    { pList->AddLast(new RedDataBoolean(bVal));  };

    // Remove
    void        DelAll(void) { pList->DelAll(); };
    void        DelAtIndex(const unsigned uIndex);

    unsigned    NumItems(void) const { return pList->NumItems(); };

    RedType*    PtrForIndex(const unsigned uIndex) const;

    // Operators
    void operator =(const RedDataList& cNewVal);
    RedType* operator [](const unsigned Index) const { return PtrForIndex(Index); };

private:

    typedef RedDoubleLinkedList<RedType*>   RedTypeList;
    typedef RedDoubleLinkedList<RedType*>   RedTypeListIterator;

    // Attributes
    RedTypeList* pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
