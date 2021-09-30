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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
class RedDoubleLinkedList
{
public:

    // Construction/destruction
    RedDoubleLinkedList();
    ~RedDoubleLinkedList();
    void Init(void);

    // New Items
    bool     AddLast(Element Elem);
    bool     AddFirst(Element Elem);
    bool     InsertAfter(const unsigned iElemIndex, Element Elem);

    // Access Items
    bool     FindFirst(Element& Elem) const;
    bool     FindLast(Element& Elem) const;
    bool     FindElementAtIndex(const unsigned iElemIndex, Element& Elem) const;
    unsigned NumItems(void)   const { return iNumItems; };
    bool     IsEmpty(void)    const { return (iNumItems==0); };
    unsigned FirstIndex(void) const;
    unsigned LastIndex(void)  const;

    // Delete Items
    bool     DelFirst(void);
    bool     DelLast(void);
    bool     Del(const unsigned iElemIndex);
    bool     DelAll(void);

    // complex operations
    RedDoubleLinkedList* Clone(void);
    
private:

    typedef struct TListElement
    {
        Element       Elem;
        TListElement* pPrev;
        TListElement* pNext;
    } TListElement;

    void MakeListElement(TListElement** pNewElem);
    bool FindListElement(unsigned iElemIndex, TListElement** pFoundElem) const;

    TListElement* pListHead;
    TListElement* pListTail;
    unsigned      iNumItems;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedDoubleLinkedList<Element>::RedDoubleLinkedList()
{
    Init();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedDoubleLinkedList<Element>::~RedDoubleLinkedList()
{
    while( iNumItems>0 )
        DelFirst();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
void RedDoubleLinkedList<Element>::Init(void)
{
    pListHead = 0;
    pListTail = 0;
    iNumItems = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::AddLast(Element Elem)
{
    // First create the new element
    TListElement* pNewElem  = 0;
    TListElement* pPrevElem = 0;

    // Make the new object and assign the contents
    MakeListElement(&pNewElem);
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
        pPrevElem        = pListTail;
        pPrevElem->pNext = pNewElem;

        // setup the new element
        pNewElem->pPrev  = pListTail;
        pListTail        = pNewElem;
        break;
    }

    iNumItems++;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::AddFirst(Element Elem)
{
    // first create the new element
    TListElement* pNewElem  = 0;
    TListElement* pNextElem = 0;

    // Make the new object and assign the contents
    MakeListElement(&pNewElem);
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
        pNextElem        = pListHead;
        pNextElem->pNext = pNewElem;

        // setup the new element
        pNewElem->pNext  = pListHead;
        pListHead        = pNewElem;
        break;
    }

    iNumItems++;

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::InsertAfter(const unsigned iElemIndex, Element Elem)
{
    TListElement* pInsertAfterElem = 0;
    TListElement* pNewElem         = 0;
   
    // return failed if the location is after the end of the list
    if ( !GetListElement(iElemIndex, &pInsertAfterElem) )
        return false;

    // Make the new object and assign the contents
    MakeListElement(&pNewElem);
    pNewElem->Elem = Elem;

    // reassign the pointers to insert the new object
    if (pInsertAfterElem->pNext != 0)
    {
        pNewElem->pNext = pInsertAfterElem->pNext;
    }
    else
    {
        // if pNext is null, we'll need to update the list tail
        pListTail = pNewElem;
    }

    pInsertAfterElem->pNext = pNewElem;

    // return success
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GET
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::FindElementAtIndex(const unsigned iElemIndex, Element& Elem) const
{
    TListElement* pGetElem = 0;

    // return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pGetElem) )
        return false;

    Elem = pGetElem->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::FindFirst(Element& Elem) const
{
    if (pListHead == 0)
        return false;
    
    Elem = pListHead->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::FindLast(Element& Elem) const
{
    if (pListTail == 0)
        return false;
    
    Elem = pListTail->Elem;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
unsigned RedDoubleLinkedList<Element>::FirstIndex(void) const
{
    if (iNumItems==0) 
        return 0;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
unsigned RedDoubleLinkedList<Element>::LastIndex(void) const
{
    return iNumItems;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DELETE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::DelFirst(void)
{
    TListElement* pRemoveElem  = 0;

    // backup the pointer to element to delete
    pRemoveElem = pListHead;

    // fail if we have nothing to delete
    if ( (pRemoveElem==0) || (iNumItems==0) )
        return false;

    // re-route the pointers around the object to remove
    if (iNumItems==1)
        pListHead = pListTail = 0;
    else
        pListHead = pListHead->pNext;

    // If the new list head is not null, remove its reference to the old head element
    if (pListHead != 0)
        pListHead->pPrev = 0;

    // finally delete the item and return success
    delete pRemoveElem;
    iNumItems--;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::DelLast(void)
{
    TListElement* pRemoveElem = 0;
    //TListElement* pPrevElem   = 0;

    // fail if we have nothing to delete
    if ( iNumItems == 0 )
        return false;

    // backup the pointer to element to delete
    pRemoveElem = pListTail;

    // re-route the pointers around the object to remove
    pListTail = pListTail->pPrev;

    // If the new tail is not null, remove its reference to the old tail.
    if (pListTail != 0)
        pListTail->pNext = 0;

    // finally delete the item and return success
    delete pRemoveElem;
    iNumItems--;
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::Del(unsigned iElemIndex)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;
    TListElement* pNextElem   = 0;

    // fail if we have nothing to delete
    if ( iNumItems == 0 )
        return false;

    // return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pRemoveElem) )
        return false;

    // if the element is in the middle of a list
    if ((pRemoveElem->pPrev != 0) && (pRemoveElem->pNext != 0))
    {
        // get the pointers, for readability
        pPrevElem = pRemoveElem->pPrev;
        pNextElem = pRemoveElem->pNext;

        // re-route pointers around the item to be deleted
        pPrevElem->pNext = pNextElem;
        pNextElem->pPrev = pPrevElem;

        // finally delete the item and return success
        delete pRemoveElem;
        iNumItems--;
        return true;
    }
    
    // else, if we are dealing with the tail of the list
    else if (pRemoveElem->pNext == 0)
    {
        return DelLast();
    }

    // else, if we are dealing with the head of the list
    else if (pRemoveElem->pPrev == 0)
    {
        return DelFirst();
    }

    // else, we don't know whats happening, so fail.
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::DelAll(void)
{
    // fail if the list has no Items
    if (IsEmpty()) return false;

    // loop, deleting the last until we have no more, returning fail if required.
    while ( !IsEmpty() )
        if (!DelFirst()) return false;
    
    // return success.
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// COMPLEX
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
RedDoubleLinkedList<Element>* RedDoubleLinkedList<Element>::Clone(void)
{   
    // create the new list
    RedDoubleLinkedList* pNewList = new RedDoubleLinkedList<Element>();

    // Get the next element until we're at the requested one, or we run out of list
    Element cCurrElem;
    for (unsigned i=0; i<iNumItems; i++)
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
void RedDoubleLinkedList<Element>::MakeListElement(TListElement** pNewElem)
{
    //create the new element
    TListElement* pElem = new TListElement;

    // initialise the data
    pElem->pPrev = 0;
    pElem->pNext = 0;

    // assign the output value and return success
    *pNewElem = pElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
bool RedDoubleLinkedList<Element>::FindListElement(
    unsigned       iElemIndex,
    TListElement** pFoundElem) const 
{
    // Initialise the return value
    *pFoundElem             = 0;
    TListElement* pCurrElem = 0;

    // fail if we have nothing (or not enough) to search.
    if (iNumItems == 0)            return false;
    if (iElemIndex > LastIndex())  return false;
    if (iElemIndex < FirstIndex()) return false;

    // Don't search if we want the head or tail.
    if (iElemIndex == FirstIndex()) { *pFoundElem = pListHead; return true; }
    if (iElemIndex == LastIndex())  { *pFoundElem = pListTail; return true; }

    // set reference to element zero
    pCurrElem = pListHead;

    // Get the next element until we're at the requested one, or we run out of list
    for (unsigned i=1; i<iElemIndex; i++)
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
