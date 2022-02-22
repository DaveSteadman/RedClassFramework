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

#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Purpose: A simple LIFO(Last In First Out) Stack class, adding a few push
// and pop operations sitting on top of a CCoreLinkedList class which does 
// all the real work.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

template<class DataClass>
class RedStackLIFO
{
public:

    // Construction/destruction
    RedStackLIFO();
    ~RedStackLIFO();

    void Init(void);

    // Access Items
    void      Push(const DataClass Data) { cList.AddFirst(Data); };
    DataClass Pop(void);
    DataClass NextPopItem(void);

    // Overall collection routines
    unsigned NumItems(void) const { return cList.NumItems(); };
    bool     IsEmpty(void) const  { return cList.IsEmpty(); };
    bool     DelAll(void)         { return cList.DelAll(); };

    // Complex
    RedStackLIFO* Clone(void); 

private:

    typedef RedLinkedList<DataClass> ListType;
    typedef RedLinkedListIterator<DataClass> ListItType;

    ListType cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction/destruction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>::RedStackLIFO()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>::~RedStackLIFO()
{
    cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access Items
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
DataClass RedStackLIFO<DataClass>::Pop(void)
{
    // check the list has at least one element
    if (cList.IsEmpty()) throw;
    
    // Get the top element
    DataClass cRetCal;
    if (!cList.FindFirst(cRetCal))
        throw;
        
    // delete the top element
    if (!cList.DelFirst())
        throw;

    return cRetCal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
DataClass RedStackLIFO<DataClass>::NextPopItem(void)
{
    // check the list has at least one element
    if (cList.IsEmpty()) throw;
    
    // Get the top element
    DataClass cRetCal;
    if (!cList.FindFirst(cRetCal))
        throw;

    return cRetCal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Complex
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>* RedStackLIFO<DataClass>::Clone(void)
{
    // create the new list
    RedStackLIFO<DataClass>* pNewStack = new RedStackLIFO<DataClass>;
    
    ListItType cIt(&cList);
    cIt.First();
    
    while(!cIt.IsDone())
    {
        DataClass cListVal = cIt.CurrentItem();
        pNewStack->cList.AddLast(cListVal);
        
        cIt.Next();
    }

    return pNewStack;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

