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

#include "RedFlexRecord.h"
#include "RedBoolean.h"
#include "RedChar.h"
#include "RedNumber.h"
#include "RedString.h"
#include "RedVariant.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedFlexRecord::RedFlexRecord(void) :
    list_head_ptr(NULL),
    list_tail_ptr(NULL),
    num_items(0)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedFlexRecord::~RedFlexRecord(void)
{
    DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inhertied
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedFlexRecord::Clone(void) const 
{
    RedFlexRecord* pNewObj = new RedFlexRecord();

    return pNewObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedFlexRecord::CloneAndAdd(const RedType* cNewAttriIndex, RedType* pNewAttrib)
{
    // Create the two new objects
    RedType* IndexValue = cNewAttriIndex->Clone();
    RedType* DataValue  = pNewAttrib->Clone();

    // Add the object to the collection
    AddElement(IndexValue, DataValue);

    // Return the new data value
    return DataValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedFlexRecord::Add(RedType* cNewAttriIndex, RedType* pNewAttrib)
{
    // Create the two new objects
    RedType* IndexValue = cNewAttriIndex;
    RedType* DataValue  = pNewAttrib;

    // Add the object to the collection
    AddElement(IndexValue, DataValue);

    // Return the new data value
    return DataValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedFlexRecord::CreateAndAdd(const RedType* cNewAttriIndex, const RedDataType& NewAttribType)
{
    // Create the two new objects
    RedType* IndexValue = cNewAttriIndex->Clone();
    RedType* DataValue  = CreateObjectOfType(NewAttribType);

    // Add the object to the collection
    AddElement(IndexValue, DataValue);

    // Return the new data value
    return DataValue;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedFlexRecord::Find(const RedType* cNewAttriIndex, RedType*& pData)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedFlexRecord::DelFirst(void)
{
    if ((list_head_ptr) && (num_items > 0))
    {
        if (num_items == 1)
        {
            // Delete the element
            delete list_head_ptr->index_ptr;
            delete list_head_ptr->data_ptr;
            delete list_head_ptr;

            list_head_ptr = NULL;
            list_tail_ptr = NULL;
            num_items = 0;
        }
        else
        {
            TListElement* del_element = list_head_ptr;

            // Take the head element out of the list
            list_head_ptr = list_head_ptr->next_ptr;
            num_items--;

            // Delete the element
            delete del_element->index_ptr;
            delete del_element->data_ptr;
            delete del_element;
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedFlexRecord::DelLast(void)
{
    if ((list_tail_ptr) && (num_items > 0))
    {
        if (num_items == 1)
        {
            // Delete the element
            delete list_tail_ptr->index_ptr;
            delete list_tail_ptr->data_ptr;
            delete list_tail_ptr;

            list_head_ptr = NULL;
            list_tail_ptr = NULL;
            num_items = 0;
        }
        else
        {
            TListElement* last_element = list_tail_ptr;
            TListElement* last_but_one_element = NULL;

            // Loop until we run out of valid elements
            TListElement* curr_element = list_head_ptr;
            while (curr_element)
            {
                if (curr_element->next_ptr == last_element)
                {
                    last_but_one_element = curr_element;
                    curr_element = NULL;
                }
                else
                {
                    curr_element = curr_element->next_ptr;
                }
            }

            if (last_but_one_element)
            {
                // Delete the element
                delete last_element->index_ptr;
                delete last_element->data_ptr;
                delete last_element;

                list_tail_ptr = last_but_one_element;
                num_items --;
            }
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedFlexRecord::DelAll(void)
{
    // Loop until we run out of valid elements
    while (num_items > 0)
        DelFirst();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void DelIndex(const RedType* cNewAttriIndex)
{
//    TListElement* curr_element = list_head_ptr;
//
//    // Loop until we run out of valid elements
//    while (curr_element)
//    {
//        // If the types match, then check further
//        if (RedTypeMatcher(curr_element->index_ptr, search_index))
//        {
//            *found_element = curr_element;
//            return true;
//        }
//
//        // Move along the list to the next element
//        curr_element = curr_element->next_ptr;
//    }
//
//    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedFlexRecord::CreateObjectOfType(const RedDataType& NewAttribType)
{
    RedType* retData = NULL;

    if      (NewAttribType.IsBool())    retData = new RedBoolean;
    else if (NewAttribType.IsChar())    retData = new RedChar;
    else if (NewAttribType.IsNum())     retData = new RedNumber;
    else if (NewAttribType.IsRecord())  retData = new RedFlexRecord;
    else if (NewAttribType.IsStr())     retData = new RedString;
    else if (NewAttribType.IsVariant()) retData = new RedVariant;

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedFlexRecord::MakeListElement(TListElement** NewElemPtr) const 
{
    TListElement* NewElem = new TListElement;

    NewElem->index_ptr = NULL;
    NewElem->data_ptr  = NULL;
    NewElem->next_ptr  = NULL;

    *NewElemPtr = NewElem;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Final keyword here indicates that any cloning/duplicating activities have taken place and
/// this routine is about putting these pointers into the object list.
void RedFlexRecord::AddElement(RedType* final_index_ptr, RedType* final_data_ptr)
{
    // Create the new element
    TListElement* NewElem  = NULL;
    MakeListElement(&NewElem);

    // Assign the contents
    NewElem->index_ptr = final_index_ptr;
    NewElem->data_ptr  = final_data_ptr;

    // Update the pointers
    switch(num_items)
    {
    case 0:
        // if list is empty, ensure head and tail are set to this element
        list_head_ptr = NewElem;
        list_tail_ptr = NewElem;
        break;

    default:
        // Adjust the last element of the list
        list_tail_ptr->next_ptr = NewElem;

        // Update the tail element
        list_tail_ptr = NewElem;
        break;
    }

    // Update the list population
    num_items++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedFlexRecord::FindElementForIndex(RedType* search_index, TListElement** found_element)
{
    TListElement* curr_element = list_head_ptr;

    // Loop until we run out of valid elements
    while (curr_element)
    {
        // If the types match, then check further
        if (RedTypeMatcher(curr_element->index_ptr, search_index))
        {
            *found_element = curr_element;
            return true;
        }

        // Move along the list to the next element
        curr_element = curr_element->next_ptr;
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedFlexRecord::RedTypeMatcher(RedType* lhs, RedType* rhs)
{
    // If the types match, then check further
    if (lhs->Type() == rhs->Type())
    {
        if (lhs->Type() == kDataTypeStr)
        {
            RedString* lhs_str = dynamic_cast<RedString*>(lhs);
            RedString* rhs_str = dynamic_cast<RedString*>(rhs);
            return (*lhs_str == *rhs_str);
        }
        if (lhs->Type() == kDataTypeNum)
        {
            RedNumber* lhs_str = dynamic_cast<RedNumber*>(lhs);
            RedNumber* rhs_str = dynamic_cast<RedNumber*>(rhs);
            return (*lhs_str == *rhs_str);
        }
        if (lhs->Type() == kDataTypeBool)
        {
            RedBoolean* lhs_str = dynamic_cast<RedBoolean*>(lhs);
            RedBoolean* rhs_str = dynamic_cast<RedBoolean*>(rhs);
            return (*lhs_str == *rhs_str);
        }
    }

    // No match, return a default false
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedFlexRecord::operator =(const RedFlexRecord& cNewVal)
{
    Init();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




