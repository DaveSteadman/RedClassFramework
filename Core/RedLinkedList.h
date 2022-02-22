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

#include "RedCoreConsts.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
class RedLinkedList
{
public:

    // Construction/destruction
    RedLinkedList();
    ~RedLinkedList();

    // New Items
    void     AddLast(Element Elem);
    void     AddFirst(Element Elem);
    bool     InsertAfter(const unsigned iElemIndex, Element Elem);

    // Access counts and index values
    bool     IsEmpty(void)    const { return (iNumItems==0); };
    unsigned NumItems(void)   const { return iNumItems; };
    unsigned FirstIndex(void) const { if (iNumItems == 0) return 0; return 1; };
    unsigned LastIndex(void)  const { return iNumItems; };

    // Access Items
    bool     Find(const unsigned iElemIndex, Element& Elem) const;
    bool     FindFirst(Element& Elem) const;
    bool     FindLast(Element& Elem) const;

    // Delete Items
    bool     DelFirst(void);
    bool     DelLast(void);
    bool     Del(const unsigned iElemIndex);
    bool     DelAll(void);

    // complex operations
    RedLinkedList* Clone(void);
    
private:

    typedef struct TListElement
    {
        Element       Elem;
        TListElement* pNext;
    } TListElement;

    bool MakeListElement(TListElement** pNewElem);
    bool FindListElement(const unsigned ElemNum, TListElement** pFoundElem) const;

    TListElement* pListHead;
    TListElement* pListTail;
    unsigned      iNumItems;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedLinkedList<Element>::RedLinkedList()
{
    pListHead = 0;
    pListTail = 0;
    iNumItems = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedLinkedList<Element>::~RedLinkedList()
{
    while( iNumItems>0 )
        DelFirst();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// New Items
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
void RedLinkedList<Element>::AddLast(Element Elem)
{
    // first create the new element
    // return failed if we didn't make the new object
    TListElement* pNewElem  = 0;
    MakeListElement(&pNewElem);
    
    // assign the contents
    pNewElem->Elem = Elem;

    // Update the pointers
    switch(iNumItems)
    {
    case 0:
        // if list is empty, ensure head and tail are set to this element
        pListHead        = pNewElem;
        pListTail        = pNewElem;
        break;

    default:
        // adjust the last element of the list
        pListTail->pNext = pNewElem;

        // Update the tail element
        pListTail        = pNewElem;
        break;
    }

    iNumItems++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
void RedLinkedList<Element>::AddFirst(Element Elem)
{
    // first create the new element
    TListElement* pNewElem  = 0;

    // return failed if we didn't make the new object
    MakeListElement(&pNewElem);
    
    // assign the contents
    pNewElem->Elem = Elem;

    // Update the pointers
    switch(iNumItems)
    {
    case 0:
        // if list is empty, ensure head and tail are set to this element
        pListHead        = pNewElem;
        pListTail        = pNewElem;
        break;

    default:
        // setup the new element
        // adjust the head element of the list
        pNewElem->pNext  = pListHead;
        pListHead        = pNewElem;
        break;
    }

    iNumItems++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::InsertAfter(const unsigned iElemIndex, Element Elem)
{
    TListElement* pInsertAfterElem = 0;
    TListElement* pNewElem         = 0;

    // Start by identifying special cases.
    if (iNumItems==0)               AddFirst(Elem);
    if (iElemIndex  < FirstIndex()) AddFirst(Elem);
    if (iElemIndex >= LastIndex())  AddLast(Elem); 
   
    // Return failed if the location is after the end of the list
    if ( !GetListElement(iElemIndex, &pInsertAfterElem) )
        return false;

    // return failed if we didn't make the new object
    MakeListElement(&pNewElem);
    
    // assign the contents
    pNewElem->Elem = Elem;

    // Fix pointers to add object. First assign the new object to the next in the list.
    // If the new item isn't going on the tail, we have a new item, else we need to 
    // update the tail pointer.
    if (pInsertAfterElem->pNext != 0)
    {
        pNewElem->pNext = pInsertAfterElem->pNext;
    }
    else
    {
        // if pNext is null, we'll need to update the list tail
        pListTail = pNewElem;
    }

    // Now add the new object to the next pointer of the "insertafter" element
    pInsertAfterElem->pNext = pNewElem;

    // return success
    return true;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::Find(const unsigned iElemIndex, Element& Elem) const
{
    TListElement* pGetElem = 0;

    // Return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pGetElem) )
        return false;

    Elem = pGetElem->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::FindFirst(Element& Elem) const
{
    if (pListHead == 0)
        return false;
    
    Elem = pListHead->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::FindLast(Element& Elem) const
{
    if (pListTail == 0)
        return false;
    
    Elem = pListTail->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DELETE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::DelFirst(void)
{
    // Fail if we have nothing to delete
    if ( (iNumItems == 0) || (!pListHead) )
        return false;

    // Mark the item to delete
    TListElement* pRemoveElem = pListHead;

    // If we had one element prior to the delete, we need to clear the
    // head/tail pointers too.
    if (iNumItems == 1)
    {
        pListHead = 0;
        pListTail = 0;
        iNumItems = 0;
    }

    // Else, if we have a pointer to redirect
    else if (pRemoveElem->pNext)
    {
        pListHead = pRemoveElem->pNext;
        iNumItems--;
    }
    
    // Finally delete the item and return success
    delete pRemoveElem;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::DelLast(void)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;

    // Fail if we have nothing to delete
    if ( (iNumItems == 0) || (!pListTail) )
        return false;

    // If we have just one element, reset the list
    if (iNumItems == 1)
    {
        pListHead = 0;
        pListTail = 0;
        iNumItems = 0;
        delete pRemoveElem;
    }
    // Else, perform the more complex opertation on the penultimate entry
    else    
    {
        TListElement* pPenultimateElem  = 0;

        // Find the penultimate entry
        if ( !FindListElement(LastIndex()-1, &pPenultimateElem) )
            return 0;
        
        // Check the penultimate points to the delete entry
        if (pPenultimateElem->pNext != pRemoveElem)
            return 0;
            
        // Change the penultimate element to the tail and delete the last entry 
        pPenultimateElem->pNext = 0;
        pListTail = pPenultimateElem;
        delete pRemoveElem;
        
        iNumItems--;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::Del(const unsigned iElemIndex)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;
    TListElement* pNextElem   = 0;

    // Fail if we have nothing to delete
    if ( iNumItems == 0 )
        return false;

    // Cater for special cases
    if (iNumItems  == 1)            { return DelFirst(); }
    if (iElemIndex == FirstIndex()) { return DelFirst(); }
    if (iElemIndex == LastIndex())  { return DelLast();  }

    // Proceed, knowing we have at least two elements and we're not in an end
    // of list special case
    int           iPreviousIndex = iNumItems-1;
    TListElement* pPreviousElem  = 0;

    // Return failed if we can't find the item or its predecessor
    if ( !FindListElement(iElemIndex, &pRemoveElem) ) return 0;
    if ( !FindListElement(iPreviousIndex, &pPreviousElem) ) return 0;
        
    // Cut out the element from the list
    pPreviousElem->pNext = pRemoveElem->pNext;
    
    // Delete the item and return success
    delete pRemoveElem;
    iNumItems--;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::DelAll(void)
{
    // Fail if the list has no Items
    if (IsEmpty())
        return false;

    // Loop, deleting the last until we have no more, returning fail if required.
    while ( !IsEmpty() )
    {
        if (!DelFirst())
            return false;
    }
    
    // Return success.
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// COMPLEX
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedLinkedList<Element>* RedLinkedList<Element>::Clone(void)
{   
    // create the new list
    RedLinkedList* pNewList = new RedLinkedList<Element>();

    // Get the next element until we're at the requested one, or we run out of list
    Element cCurrElem;
    for (int i=FirstIndex(); i<LastIndex(); i++)
    {
        if (Find(i, &cCurrElem))
            pNewList->AddLast(cCurrElem);
    }

    return pNewList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PRIVATE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::MakeListElement(TListElement** pNewElem)
{
    // Create the new element
    TListElement* pElem = new TListElement;

    // Initialise the data
    pElem->pNext = NULL;

    // Assign the output value and return success
    *pNewElem = pElem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedLinkedList<Element>::FindListElement(
    const unsigned ElemIndex,
    TListElement** pFoundElem) const
{
    // Initialise the return value
    *pFoundElem             = 0;
    TListElement* pCurrElem = 0;

    // Fail if we have nothing (or not enough) to search.
    if (iNumItems == 0)           return false;
    if (ElemIndex > LastIndex())  return false;
    if (ElemIndex < FirstIndex()) return false;

    // Don't search if we want the head or tail.
    if (ElemIndex == FirstIndex()) { *pFoundElem = pListHead; return 1; }
    if (ElemIndex == LastIndex())  { *pFoundElem = pListTail; return 1; }

    // Set reference to element zero
    pCurrElem = pListHead;

    // Get the next element until we're at the requested one, or we run out of list
    for (unsigned i=1; i<ElemIndex; i++)
    {
        // if we're out of list, fail
        if (pCurrElem->pNext == 0)
            return false;

        // else move onto next element
        pCurrElem = pCurrElem->pNext;
    }

    // Moved along enough, so we return the current element and success.
    *pFoundElem = pCurrElem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


