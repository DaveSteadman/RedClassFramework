
#pragma once

namespace Red {
namespace Core {

template<class Element>
class RedLinkedList
{
public:

    // Construction/destruction
    RedLinkedList();
    ~RedLinkedList();

    // New Items
    void AddLast(Element Elem);
    void AddFirst(Element Elem);
    int  InsertAfter(int iElemIndex, Element Elem);

    // Access counts and index values
    int IsEmpty(void)     const { return (iNumItems==0); };
    int NumItems(void) const { return iNumItems; };
    int FirstIndex(void);
    int LastIndex(void);

    // Access Items
    int FindFirst(Element& Elem);
    int FindLast(Element& Elem);
    int Find(int iElemIndex, Element& Elem);

    // Delete Items
    int DelFirst(void);
    int DelLast(void);
    int Del(int iElemIndex);
    int DelAll(void);

    // complex operations
    RedLinkedList* Clone(void);
    
private:

    typedef struct TListElement
    {
        Element       Elem;
        TListElement* pNext;
    } TListElement;

    int MakeListElement(TListElement** pNewElem);
    int FindListElement(int iElemNum, TListElement** pFoundElem);

    TListElement* pListHead;
    TListElement* pListTail;
    int           iNumItems;
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
int RedLinkedList<Element>::InsertAfter(int iElemIndex, Element Elem)
{
    TListElement* pInsertAfterElem = 0;
    TListElement* pNewElem         = 0;

    // Start by identifying special cases.
    if (iNumItems==0)               AddFirst(Elem);
    if (iElemIndex  < FirstIndex()) AddFirst(Elem);
    if (iElemIndex >= LastIndex())  AddLast(Elem); 
   
    // Return failed if the location is after the end of the list
    if ( !GetListElement(iElemIndex, &pInsertAfterElem) )
        return 0;

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
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access counts and index values
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::FirstIndex(void)
{
    if (iNumItems == 0) 
        return 0;
    
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::LastIndex(void)
{
    return iNumItems;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::Find(int iElemIndex, Element& Elem)
{
    TListElement* pGetElem = 0;

    // Return failed if we can find the item
    if ( !FindListElement(iElemIndex, &pGetElem) )
        return 0;

    Elem = pGetElem->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::FindFirst(Element& Elem)
{
    if (pListHead == 0)
        return 0;
    
    Elem = pListHead->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::FindLast(Element& Elem)
{
    if (pListTail == 0)
        return 0;
    
    Elem = pListTail->Elem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DELETE
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::DelFirst(void)
{
    // Fail if we have nothing to delete
    if ( (iNumItems == 0) || (!pListHead) )
        return 0;

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

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::DelLast(void)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;

    // Fail if we have nothing to delete
    if ( (iNumItems == 0) || (!pListTail) )
        return 0;

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

    return 1;        
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::Del(int iElemIndex)
{
    TListElement* pRemoveElem = 0;
    TListElement* pPrevElem   = 0;
    TListElement* pNextElem   = 0;

    // Fail if we have nothing to delete
    if ( iNumItems == 0 )
        return 0;

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
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::DelAll(void)
{
    // Fail if the list has no Items
    if (IsEmpty())
        return 0;

    // Loop, deleting the last until we have no more, returning fail if required.
    while ( !IsEmpty() )
    {
        if (!DelFirst())
            return 0;
    }
    
    // Return success.
    return 1;
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
int RedLinkedList<Element>::MakeListElement(TListElement** pNewElem)
{
    // Create the new element
    TListElement* pElem = new TListElement;

    // Initialise the data
    pElem->pNext = 0;

    // Assign the output value and return success
    *pNewElem = pElem;
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class Element>
int RedLinkedList<Element>::FindListElement(
    int            iElemIndex, 
    TListElement** pFoundElem)
{
    // Initialise the return value
    *pFoundElem             = 0;
    TListElement* pCurrElem = 0;

    // Fail if we have nothing (or not enough) to search.
    if (iNumItems == 0)            return 0;
    if (iElemIndex > LastIndex())  return 0;
    if (iElemIndex < FirstIndex()) return 0;

    // Don't search if we want the head or tail.
    if (iElemIndex == FirstIndex()) { *pFoundElem = pListHead; return 1; }
    if (iElemIndex == LastIndex())  { *pFoundElem = pListTail; return 1; }

    // Set reference to element zero
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


