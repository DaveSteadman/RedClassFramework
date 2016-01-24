
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Purpose: A simple LIFO(Last In First Out) Stack class, adding a few push
// and pop operations sitting on top of a CCoreLinkedList class which does 
// all the real work.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

template<class DataClass>
class RedStackLIFO
{
public:

    // Construction/destruction
    RedStackLIFO();
    ~RedStackLIFO();

    void Init(void);

    // Access Items
    void      Push(const DataClass Data) { cList.AddFirst(Data); };
    DataClass Pop(void);
    DataClass NextPopItem(void);

    // Overall collection routines
    int NumItems(void) const { return cList.NumItems(); };
    int IsEmpty(void) const  { return cList.IsEmpty(); };
    int DelAll(void)         { return cList.DelAll(); };

    // Complex
    RedStackLIFO* Clone(void); 

private:

    typedef RedLinkedList<DataClass> ListType;
    typedef RedLinkedListIterator<DataClass> ListItType;

    ListType cList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction/destruction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>::RedStackLIFO()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>::~RedStackLIFO()
{
    cList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Access Items
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
DataClass RedStackLIFO<DataClass>::Pop(void)
{
    // check the list has at least one element
    if (cList.IsEmpty()) throw;
    
    // Get the top element
    DataClass cRetCal;
    if (!cList.FindFirst(cRetCal))
        throw;
        
    // delete the top element
    if (!cList.DelFirst())
        throw;

    return cRetCal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
DataClass RedStackLIFO<DataClass>::NextPopItem(void)
{
    // check the list has at least one element
    if (cList.IsEmpty()) throw;
    
    // Get the top element
    DataClass cRetCal;
    if (!cList.FindFirst(cRetCal))
        throw;

    return cRetCal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Complex
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class DataClass>
RedStackLIFO<DataClass>* RedStackLIFO<DataClass>::Clone(void)
{
    // create the new list
    RedStackLIFO<DataClass>* pNewStack = new RedStackLIFO<DataClass>;
    
    ListItType cIt(&cList);
    cIt.First();
    
    while(!cIt.IsDone())
    {
        DataClass cListVal = cIt.CurrentItem();
        pNewStack->cList.AddLast(cListVal);
        
        cIt.Next();
    }

    return pNewStack;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


} // Core
} // Red

