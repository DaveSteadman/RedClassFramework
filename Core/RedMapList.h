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

// Include Files
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Purpose: An unsorted, indexed list template.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

template<class IdClass, class DataClass>
class RedMapList
{
public:

    // Construction/destruction
    RedMapList() {};
    ~RedMapList();

    // Access Items
    const int       Add(IdClass Id, DataClass Data);
    const int       Find(IdClass Id, DataClass& Data);
    void            Del(IdClass Id);
    const int       DelAll(void);
    
    const int       FindIdByIndex    (unsigned iElemIndex, IdClass& Id);
    const int       FindDataByIndex  (unsigned iElemIndex, DataClass& Data);
    const int       AssignDataByIndex(unsigned iElemIndex, DataClass Data);
    const unsigned  FirstIndex       (void) const;
    const unsigned  LastIndex        (void) const;
    
    // Overall collection routines
    const unsigned  NumItems(void) const { return cList.NumItems(); };
    const bool      IsEmpty(void)  const { return cList.IsEmpty();  };

    // Complex
    RedMapList* Clone(void); 
    
private:

    typedef struct TMapElement
    {
        IdClass       cId;
        DataClass     cData;
    } TMapElement;

    typedef RedDoubleLinkedList<TMapElement>         ListType;
    typedef RedDoubleLinkedListIterator<TMapElement> ListItType;

    const int MakeListElement(TMapElement** pNewElem);

    /// The FindElement operation is not const because it creates an iterator, which has the
    /// capability to delete an element from the list.
    const int FindElement(IdClass Id, TMapElement& Elem, unsigned& iElemIndex);

    ListType cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction/destruction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
RedMapList<IdClass, DataClass>::~RedMapList()
{
    while( cList.NumItems() > 0 )
        cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access Items
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::Add(IdClass Id, DataClass Data)
{
    unsigned iElemIndex;
    TMapElement Elem;

    // clear out any pre-existing value under the Id.
    if (FindElement(Id, Elem, iElemIndex))
        cList.Del(iElemIndex);

    // create the new item for the list
    TMapElement cNewElem;
    cNewElem.cId   = Id;
    cNewElem.cData = Data;

    // Add the item to the end of the list
    cList.AddLast(cNewElem);

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::Find(IdClass Id, DataClass& Data) 
{
    unsigned iElemIndex;
    TMapElement Elem;

    if (!FindElement(Id, Elem, iElemIndex))
        return 0;
    
    Data = Elem.cData;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
void RedMapList<IdClass, DataClass>::Del(IdClass Id)
{
    unsigned iElemIndex;
    TMapElement Elem;

    if (FindElement(Id, Elem, iElemIndex))
        cList.Del(iElemIndex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::DelAll(void)
{
    return cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::FindIdByIndex(unsigned iElemIndex, IdClass& Id)
{
    if ( (iElemIndex<cList.FirstIndex()) || (iElemIndex>cList.LastIndex()) )
        return 0;

    TMapElement cElem;
    if ( !cList.FindElementAtIndex(iElemIndex, cElem) )
        return 0;

    Id = cElem.cId;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::FindDataByIndex(unsigned iElemIndex, DataClass& Data)
{
    if ( (iElemIndex<cList.FirstIndex()) || (iElemIndex>cList.LastIndex()) )
        return 0;

    TMapElement cElem;
    if ( !cList.FindElementAtIndex(iElemIndex, cElem) )
        return 0;

    Data = cElem.cData;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::AssignDataByIndex(unsigned iElemIndex, DataClass Data)
{
    if ( (iElemIndex<0) || (iElemIndex>cList.NumItems()) )
        return 0;

    TMapElement cElem;
    if ( !cList.Find(iElemIndex, cElem) )
        return 0;

    cElem.cData = Data;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const unsigned RedMapList<IdClass, DataClass>::FirstIndex(void) const
{
    return cList.FirstIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const unsigned RedMapList<IdClass, DataClass>::LastIndex(void) const
{
    return cList.LastIndex();
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Complex
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
RedMapList<IdClass, DataClass>* RedMapList<IdClass, DataClass>::Clone(void)
{
    // create the new list
    RedMapList<IdClass, DataClass>* pNewMap = new RedMapList<IdClass, DataClass>();

    // Get the next element until we're at the requested one, or we run out of list
    IdClass   cCurrId;
    DataClass cCurrData;
    
    for (int i=0; i<NumItems(); i++)
    {
        FindIdByIndex(i, cCurrId);
        FindDataByIndex(i, cCurrData);
        
        pNewMap->Add(cCurrId, cCurrData);
    }

    return pNewMap;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::MakeListElement(TMapElement** pNewElem)
{
    pNewElem = new TMapElement;
    
    pNewElem->cId   = 0;
    pNewElem->cData = 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapList<IdClass, DataClass>::FindElement(IdClass cId, TMapElement& Elem, unsigned& iElemIndex)
{
    ListItType cIt(&cList);

    cIt.First();
    while (!cIt.IsDone())
    {
        TMapElement cElem = cIt.CurrentItem();

        if (cElem.cId == cId)
        {
            Elem = cElem;
            iElemIndex = cIt.GetListIndex();
            return 1;
        }
        cIt.Next();
    }

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

