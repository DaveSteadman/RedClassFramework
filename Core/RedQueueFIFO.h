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

#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

namespace Red {
namespace Core {        

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Template queue class with First-In-First-Out Push() and Pop() operations.
template<class ElementType>
class RedQueueFIFO
{
public:

    // Construction/destruction
    RedQueueFIFO();
    ~RedQueueFIFO();

    void        Init(void);

    // Access Items
    void        Push(ElementType Data);
    ElementType Pop(void);
    ElementType NextPopItem(void);

    // Overall collection routines
    unsigned    NumItems(void) const { return cList.NumItems(); };
    bool        IsEmpty(void)  const { return cList.IsEmpty(); };
    bool        DelAll(void)         { cList.DelAll(); };

private:

    typedef RedDoubleLinkedList<ElementType> ListType;
    typedef RedDoubleLinkedListIterator<ElementType> ListItType;

    ListType cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction/destruction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
RedQueueFIFO<ElementType>::RedQueueFIFO()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
RedQueueFIFO<ElementType>::~RedQueueFIFO()
{
    while( cList.NumItems() > 0 )
        cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
void RedQueueFIFO<ElementType>::Push(ElementType Data)
{
    cList.AddLast(Data);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
ElementType RedQueueFIFO<ElementType>::Pop(void)
{
    ElementType retval;
    
    cList.FindLast(retval);
    cList.DelLast();

    return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
ElementType RedQueueFIFO<ElementType>::NextPopItem(void)
{
    ElementType retval;
    
    cList.FindLast(retval);

    return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

