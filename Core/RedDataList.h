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

#include "RedData.h"
#include "RedDataBoolean.h"
#include "RedDataNumber.h"
#include "RedDataString.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// A List data type, parented on RedData, so we can create collections of them and use them as VSI variables.
// All items stored as pointers, either adding from externally created objects, or by value that creates the object on the fly.
// All objects are explicitly deleted when they are deleted from the collection - This is the value this class adds beyond the linked-list type.

class RedDataList : public RedData
{
public:

    RedDataList(void) {  };
    RedDataList(unsigned uNumItems, RedDataType eItemType) { InitToSize(uNumItems, eItemType); };
    ~RedDataList(void) { DeleteAllListEntries(); };

    // Inherited: RedData
    RedDataType Type(void) const { return RedDataType::List(); };
    RedData*    Clone(void) const;
    void        Init(void) { DeleteAllListEntries(); };

    void        InitToSize(unsigned uNumItems, RedDataType eItemType);
    void        CloneAndAdd(const RedData* pNewAttrib) { cList.AddLast(pNewAttrib->Clone()); };
    void        AddByPtr(RedData* pNewAttrib)          { cList.AddLast(pNewAttrib); };

    // Generic add operations
    RedData*    CreateAddReturn(const RedDataType& NewAttribType);

    // Shortcut add operations
    void        AddLastByValue(const int iVal)     { cList.AddLast(new RedDataNumber(iVal));   };
    void        AddLastByValue(const char* strVal) { cList.AddLast(new RedDataString(strVal)); };
    void        AddLastByValue(const bool bVal)    { cList.AddLast(new RedDataBoolean(bVal));  };

    // Index based contents lookup
    unsigned    NumItems(void)   const { return cList.NumItems(); };
    unsigned    FirstIndex(void) const { return cList.FirstIndex(); };
    unsigned    LastIndex(void)  const { return cList.LastIndex(); };
    RedData*    PtrForIndex(const unsigned uIndex) const;

    // Remove
    void        DelAll(void) { DeleteAllListEntries(); };
    void        DelAtIndex(const unsigned uIndex);

    // Operators
    void operator =(const RedDataList& cNewVal);
    RedData* operator [](const unsigned Index) const { return PtrForIndex(Index); };

private:

    void DeleteAllListEntries(void);

    typedef RedDoubleLinkedList<RedData*>         RedTypeList;
    typedef RedDoubleLinkedListIterator<RedData*> RedTypeListIterator;

    // Attributes
    RedTypeList cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
