
#pragma once

// Include Namespaces

// Include Files
#include "RedDoubleLinkedList.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

template<class Element>
class RedDoubleLinkedListIterator
{
public:

    typedef RedDoubleLinkedList<Element> ListType;
    enum TESearchDir { eForwards, eBackwards };

    RedDoubleLinkedListIterator(ListType* pNewList);

    void    First(void);
    void    Next(void);
    int     IsDone(void);
    Element CurrentItem(void);

    void DeleteCurrentItem(void);
    void SetSearchDirection(TESearchDir eDir) { eSearchDir = eDir; };
    void SetSearchDirectionBackwards(void) { eSearchDir = eBackwards; First(); };
    int  GetListIndex(void) { return iCurrPos; };

private:

    int         iCurrPos;
    TESearchDir eSearchDir;
    ListType*   pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
RedDoubleLinkedListIterator<Element>::RedDoubleLinkedListIterator(ListType* pNewList)
{
    pList       = pNewList;
    eSearchDir  = eForwards;

    First();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedDoubleLinkedListIterator<Element>::First(void)
{
    if (eSearchDir == eForwards)
        iCurrPos = pList->FirstIndex();
    else
        iCurrPos = pList->LastIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedDoubleLinkedListIterator<Element>::Next(void)
{
    if (eSearchDir == eForwards)
        iCurrPos++;
    else
        iCurrPos--;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
int RedDoubleLinkedListIterator<Element>::IsDone(void)
{
    int iSearchDone = 0;

    if (pList->IsEmpty()) return 1;

    if (eSearchDir == eForwards)
    {
        if (iCurrPos > pList->LastIndex())
            iSearchDone = 1;
    }
    else
    {
        if (iCurrPos < pList->FirstIndex())
            iSearchDone = 1;
    }

    return iSearchDone;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
Element RedDoubleLinkedListIterator<Element>::CurrentItem(void) 
{
    Element Elem;
    
    pList->FindElementAtIndex(iCurrPos, Elem); 

    return Elem;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
void RedDoubleLinkedListIterator<Element>::DeleteCurrentItem(void)
{
    pList->Del(iCurrPos);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


