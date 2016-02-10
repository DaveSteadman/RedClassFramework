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

    void           First(void);
    void           Next(void);
    int            IsDone(void) const;
    Element        CurrentItem(void);

    void           DeleteCurrentItem(void);
    void           SetSearchDirection(TESearchDir eDir) { eSearchDir = eDir; };
    void           SetSearchDirectionBackwards(void)    { eSearchDir = eBackwards; First(); };
    const unsigned GetListIndex(void) const             { return iCurrPos; };

private:

    unsigned    iCurrPos;
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
int RedDoubleLinkedListIterator<Element>::IsDone(void) const
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


