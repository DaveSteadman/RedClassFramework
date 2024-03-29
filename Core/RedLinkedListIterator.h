// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

#include "RedLinkedList.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
class RedLinkedListIterator
{
public:

    typedef RedLinkedList<Element>         ListType;
    typedef RedLinkedListIterator<Element> ListItType;

    RedLinkedListIterator(const ListType* pNewList);

    void     First(void);
    void     Next(void);
    bool     IsDone(void) const;
    Element  CurrentItem(void) const;

    //void           DeleteCurrentItem(void);
    unsigned CollectionIndex(void) const { return iCurrPos; };

private:

    unsigned          iCurrPos;
    const ListType*   pList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
RedLinkedListIterator<Element>::RedLinkedListIterator(const ListType* pNewList)
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
bool RedLinkedListIterator<Element>::IsDone(void) const
{
    bool SearchDone = false;

    if (iCurrPos > pList->NumItems())
        SearchDone = true;

    return SearchDone;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<class Element>
Element RedLinkedListIterator<Element>::CurrentItem(void) const
{
    Element Elem;
    
    pList->Find(iCurrPos, Elem); 

    return Elem;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//template<class Element>
//void RedLinkedListIterator<Element>::DeleteCurrentItem(void)
//{
//    pList->Del(iCurrPos);
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


