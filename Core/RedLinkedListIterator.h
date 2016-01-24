
#pragma once

#include "RedLinkedList.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {


template<class Element>
class RedLinkedListIterator
{
public:

    typedef RedLinkedList<Element> ListType;
    typedef RedLinkedListIterator<Element> ListItType;

    RedLinkedListIterator(ListType* pNewList);

    void    First(void);
    void    Next(void);
    int     IsDone(void);
    Element CurrentItem(void);

    void    DeleteCurrentItem(void);
    int     GetListIndex(void) { return iCurrPos; };

private:

    int         iCurrPos;
    ListType*   pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
RedLinkedListIterator<Element>::RedLinkedListIterator(ListType* pNewList)
{
    pList = pNewList;
    First();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedLinkedListIterator<Element>::First(void)
{
    iCurrPos = 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedLinkedListIterator<Element>::Next(void)
{
    iCurrPos++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
int RedLinkedListIterator<Element>::IsDone(void)
{
    int iSearchDone = 0;

    if (iCurrPos > pList->NumItems())
        iSearchDone = 1;

    return iSearchDone;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
Element RedLinkedListIterator<Element>::CurrentItem(void) 
{
    Element Elem;
    
    pList->Find(iCurrPos, Elem); 

    return Elem;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedLinkedListIterator<Element>::DeleteCurrentItem(void)
{
    pList->Del(iCurrPos);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


