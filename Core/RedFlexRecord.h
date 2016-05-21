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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedString.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedFlexRecord : public RedType
{
public:

    // Construction
    RedFlexRecord(void);
    ~RedFlexRecord(void);

    // Inherited: RedType
    RedDataType Type(void) const { return RedDataType::Record(); };
    RedType*    Clone(void) const;
    void        Init(void) { DelAll(); };

    // Create And Add
    RedType*    CreateAndAdd(const RedType* cNewAttriIndex, const RedDataType& NewAttribType);
    RedType*    CloneAndAdd (const RedType* cNewAttriIndex, RedType* pNewAttrib);
    RedType*    Add         (RedType* cNewAttriIndex, RedType* pNewAttrib);

    // Locate
    bool        Find(RedType* cNewAttriIndex, RedType*& pData);
    unsigned    NumItems(void) const { return num_items; };

    // Remove
    void        DelFirst(void);
    void        DelLast(void);
    void        DelAll(void);
    void        DelIndex(const RedType* cNewAttriIndex);

    // Operators
    void operator =(const RedFlexRecord& cNewVal);

private:

    typedef struct TListElement
    {
        RedType*      index_ptr;
        RedType*      data_ptr;
        TListElement* next_ptr;
    } TListElement;

    void            MakeListElement(TListElement** NewElemPtr) const;
    static RedType* CreateObjectOfType(const RedDataType& NewAttribType);
    void            AddElement(RedType* final_index_ptr, RedType* final_data_ptr);

    bool            FindElementForIndex(RedType* search_index, TListElement** found_element);

    bool            RedTypeMatcher(RedType* lhs, RedType* rhs);

    TListElement* list_head_ptr;
    TListElement* list_tail_ptr;
    unsigned      num_items;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


