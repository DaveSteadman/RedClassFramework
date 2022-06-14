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

#include "RedData.h"

#include "RedDataList.h"

#include "RedDataBoolean.h"
#include "RedDataChar.h"
#include "RedDataNumber.h"
#include "RedDataString.h"
#include "RedDataVariant.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inhertied
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataList::Clone(void) const 
{
    RedDataList* pNewList = new RedDataList();

    RedTypeListIterator cIt(&cList);
    cIt.First();

    while (!cIt.IsDone())
    {
        RedData* pCurrItem = cIt.CurrentItem();

        if (pCurrItem != NULL)
            pNewList->AddByPtr(pCurrItem->Clone());

        cIt.Next();
    }

    return (RedData*)pNewList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::InitToSize(unsigned uNumItems, RedDataType cItemType)
{
    // Clear any existing list
    DeleteAllListEntries();

    // Loop addinh new entities
    for (unsigned i = 0; i < uNumItems; i++)
        cList.AddLast(RedData::NewRedObj(cItemType));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataList::CreateAddReturn(const RedDataType& NewAttribType)
{
    RedData* retData = RedData::NewRedObj(NewAttribType);

    cList.AddLast(retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedData* RedDataList::PtrForIndex(const unsigned uIndex) const
{
    RedData* retData = NULL;

    if (cList.FindElementAtIndex(uIndex, retData))
        return retData;
    else
        return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::DelAtIndex(const unsigned uIndex)
{ 
    // Delete the DataType entity within the linked list. The linked list will only delete the list-container sturcture.
    RedData* pCurrItem = NULL;

    // Get the last item (shouldn't fail)
    if (cList.FindElementAtIndex(uIndex, pCurrItem))
    {
        // Delete the object (as this list is focussed on pointers to DataType objects we've previously created)
        // The delete the linked list entry.
        delete pCurrItem;
        cList.Del(uIndex);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::DeleteAllListEntries(void)
{
    // Loop while the list is not empty
    while (!cList.IsEmpty())
    {
        RedData* pCurrItem = NULL;

        // Get the last item (shouldn't fail)
        if (cList.FindLast(pCurrItem))
        {
            // Delete the object (as this list is focussed on pointers to DataType objects we've previously created)
            // The delete the linked list entry.
            delete pCurrItem;
            cList.DelLast();
        }
        else
            throw;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataList::operator =(const RedDataList& cNewVal)
{
    Init();

    DeleteAllListEntries();

    unsigned iFirst = cNewVal.cList.FirstIndex();
    unsigned iLast  = cNewVal.cList.LastIndex();

    for (unsigned i=iFirst; i<=iLast; i++ )
    {
        RedData* pCurrItem = cNewVal.PtrForIndex(i);

        if (pCurrItem != NULL)
            cList.AddLast( pCurrItem->Clone() );
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
