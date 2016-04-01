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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
class RedDoubleLinkedListIterator
{
public:

    typedef RedDoubleLinkedList<Element> ListType;
    enum TESearchDir { eForwards, eBackwards };

    RedDoubleLinkedListIterator(const ListType* pNewList);

    void           First(void);
    void           Next(void);
    bool           IsDone(void) const;
    Element        CurrentItem(void) const;

    //void           DeleteCurrentItem(void);
    void           SetSearchDirection(TESearchDir eDir) { eSearchDir = eDir; };
    void           SetSearchDirectionBackwards(void)    { eSearchDir = eBackwards; First(); };
    const unsigned CollectionIndex(void) const          { return iCurrPos; };

private:

    unsigned          iCurrPos;
    TESearchDir       eSearchDir;
    const ListType*   pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
RedDoubleLinkedListIterator<Element>::RedDoubleLinkedListIterator(const ListType* pNewList)
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
bool RedDoubleLinkedListIterator<Element>::IsDone(void) const
{
    bool iSearchDone = false;

    if (pList->IsEmpty()) return true;

    if (eSearchDir == eForwards)
    {
        if (iCurrPos > pList->LastIndex())
            iSearchDone = true;
    }
    else
    {
        if (iCurrPos < pList->FirstIndex())
            iSearchDone = true;
    }

    return iSearchDone;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
Element RedDoubleLinkedListIterator<Element>::CurrentItem(void) const
{
    Element Elem;
    
    pList->FindElementAtIndex(iCurrPos, Elem); 

    return Elem;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//template<class Element>
//void RedDoubleLinkedListIterator<Element>::DeleteCurrentItem(void)
//{
//    pList->Del(iCurrPos);
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


