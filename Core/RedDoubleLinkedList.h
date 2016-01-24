
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

template<class Element>
class RedDoubleLinkedList
{
public:

    // Construction/destruction
    RedDoubleLinkedList();
    ~RedDoubleLinkedList();
    void Init(void);

    // New Items
    const int AddLast(Element Elem);
    const int AddFirst(Element Elem);
    const int InsertAfter(int iElemIndex, Element Elem);

    // Access Items
    const int FindFirst(Element& Elem) const;
    const int FindLast(Element& Elem) const;
    const int FindElementAtIndex(int iElemIndex, Element& Elem) const;
    const int NumItems(void) const { return iNumItems; };
    const int IsEmpty(void) const { return (iNumItems==0); };
    const int FirstIndex(void) const;
    const int LastIndex(void) const;

    // Delete Items
    const int DelFirst(void);
    const int DelLast(void);
    const int Del(int iElemIndex);
    const int DelAll(void);

    // complex operations
    RedDoubleLinkedList* Clone(void);
    
private:

    typedef struct TListElement
    {
        Element       Elem;
        TListElement* pPrev;
        TListElement* pNext;
    } TListElement;

    const int MakeListElement(TListElement** pNewElem);
    const int FindListElement(int iElemIndex, TListElement** pFoundElem) const;

    TListElement* pListHead;
    TListElement* pListTail;
    int           iNumItems;
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
const int RedDoubleLinkedList<Element>::AddLast(Element Elem)
{
    // first create the new element
    TListElement* pNewElem  = 0;
    TListElement* pPrevElem = 0;

    // return failed if we didn't make the new object
    if ( !MakeListElement(&pNewElem) )
        return 0;
    
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
        pPrevElem        = pListTail;
        pPrevElem->pNext = pNewElem;

        // setup the new element
        pNewElem->pPrev  = pListTail;
        pListTail        = pNewElem;
        break;
    }

    iNumItems++;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::AddFirst(Element Elem)
{
    // first create the new element
    TListElement* pNewElem  = 0;
    TListElement* pNextElem = 0;

    // return failed if we didn't make the new object
    if ( !MakeListElement(&pNewElem) )
        return 0;
    
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
        pNextElem        = pListHead;
        pNextElem->pNext = pNewElem;

        // setup the new element
        pNewElem->pNext  = pListHead;
        pListHead        = pNewElem;
        break;
    }

    iNumItems++;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::InsertAfter(int iElemIndex, Element Elem)
{
    TListElement* pInsertAfterElem = 0;
    TListElement* pNewElem         = 0;
   
    // return failed if the location is after the end of the list
    if ( !GetListElement(iElemIndex, &pInsertAfterElem) )
        return 0;

    // return failed if we didn't make the new object
    if ( !MakeListElement(&pNewElem) )
        return 0;
    
    // assign the contents
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
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GET
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::FindElementAtIndex(int iElemIndex, Element& Elem) const
{
    TListElement* pGetElem = 0;

    // return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pGetElem) )
        return 0;

    Elem = pGetElem->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::FindFirst(Element& Elem) const
{
    if(pListHead == 0)
        return 0;
    
    Elem = pListHead->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::FindLast(Element& Elem) const
{
    if(pListTail == 0)
        return 0;
    
    Elem = pListTail->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::FirstIndex(void) const
{
    if (iNumItems==0) 
        return 0;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::LastIndex(void) const
{
    return iNumItems;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DELETE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::DelFirst(void)
{
    TListElement* pRemoveElem  = 0;

    // backup the pointer to element to delete
    pRemoveElem = pListHead;

    // fail if we have nothing to delete
    if ( (pRemoveElem==0) || (iNumItems==0) )
        return 0;

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
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::DelLast(void)
{
    TListElement* pRemoveElem = 0;
    //TListElement* pPrevElem   = 0;

    // fail if we have nothing to delete
    if ( iNumItems == 0 )
        return 0;

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
    return 1;        
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::Del(int iElemIndex)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;
    TListElement* pNextElem   = 0;

    // fail if we have nothing to delete
    if ( iNumItems == 0 )
        return 0;

    // return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pRemoveElem) )
        return 0;

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
        return 1;
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
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::DelAll(void)
{
    // fail if the list has no Items
    if (IsEmpty()) return 0;

    // loop, deleting the last until we have no more, returning fail if required.
    while ( !IsEmpty() )
        if (!DelFirst()) return 0;
    
    // return success.
    return 1;
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
    for (int i=0; i<iNumItems; i++)
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
const int RedDoubleLinkedList<Element>::MakeListElement(TListElement** pNewElem)
{
    //create the new element
    TListElement* pElem = new TListElement;

    // initialise the data
    pElem->pPrev = 0;
    pElem->pNext = 0;

    // assign the output value and return success
    *pNewElem = pElem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
const int RedDoubleLinkedList<Element>::FindListElement(
    int            iElemIndex, 
    TListElement** pFoundElem) const 
{
    // Initialise the return value
    *pFoundElem             = 0;
    TListElement* pCurrElem = 0;

    // fail if we have nothing (or not enough) to search.
    if (iNumItems == 0) return 0;
    if (iElemIndex > LastIndex()) return 0;
    if (iElemIndex < FirstIndex()) return 0;

    // Don't search if we want the head or tail.
    if (iElemIndex == FirstIndex()) { *pFoundElem = pListHead; return 1; }
    if (iElemIndex == LastIndex())  { *pFoundElem = pListTail; return 1; }

    // set reference to element zero
    pCurrElem = pListHead;

    // Get the next element until we're at the requested one, or we run out of list
    for (int i=1; i<iElemIndex; i++)
    {
        // if we're out of list, fail
        if (pCurrElem->pNext == 0)
            return 0;

        // else move onto next element
        pCurrElem = pCurrElem->pNext;
    }

    // Moved along enough, so we return the current element and success.
    *pFoundElem = pCurrElem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


