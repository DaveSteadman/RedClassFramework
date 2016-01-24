
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Purpose: An unsorted, indexed list template.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {        

template<class ElementType>
class RedQueueFIFO
{
public:

    // Construction/destruction
    RedQueueFIFO();
    ~RedQueueFIFO();

    void Init(void);

    // Access Items
    int       Push(ElementType Data);
    ElementType Pop(void);
    ElementType NextPopItem(void);

    // Overall collection routines
    int NumItems(void) const { return cList.NumItems(); };
    int IsEmpty(void) const { return cList.IsEmpty(); };
    int DelAll(void);

private:

    typedef RedDoubleLinkedList<ElementType> ListType;
    typedef RedDoubleLinkedListIterator<ElementType> ListItType;

    ListType cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction/destruction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
RedQueueFIFO<ElementType>::RedQueueFIFO()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
RedQueueFIFO<ElementType>::~RedQueueFIFO()
{
    while( cList.NumItems() > 0 )
        cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
int RedQueueFIFO<ElementType>::Push(ElementType Data)
{
    cList.AddLast(Data);

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
ElementType RedQueueFIFO<ElementType>::Pop(void)
{
    ElementType retval;
    
    cList.FindLast(retval);
    cList.DelLast();

    return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class ElementType>
ElementType RedQueueFIFO<ElementType>::NextPopItem(void)
{
    ElementType retval;
    
    cList.FindLast(retval);

    return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

