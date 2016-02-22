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
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
#include <cassert>
#include <iostream>
#include <typeinfo>
 
#include "RedType.h"
 
namespace Red {
namespace Core {
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
class RedRefCount
{
public:
    RedRefCount(void) : count(0) {};
    void       IncRef(void)    { count++; };
    void       DecRef(void)    { count--; };
    const int  Count(void)     { return count; };
    const bool IsRefZero(void) { return (count==0); };
private:
    int count;
};
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
class RedRefCountContainer
{
public:
    RedRefCountContainer() : pData(0), reference(0)
    {
        // Create a new reference
        reference = new RedRefCount();
    };
 
    RedRefCountContainer(RedType* pValue) : pData(pValue), reference(0)
    {
        // Create a new reference
        reference = new RedRefCount();
 
        // Increment the reference count
        reference->IncRef();
    };
 
    RedRefCountContainer(const RedRefCountContainer& SmartPtr) : pData(SmartPtr.pData), reference(SmartPtr.reference)
    {
        // Copy constructor
        // Copy the data and reference pointer
        // and increment the reference count
        reference->IncRef();
    };
 
    ~RedRefCountContainer()
    {
        // Destructor
        // Decrement the reference count
        // if reference become zero delete the data
        reference->DecRef();
        if (reference->Count() == 0)
        {
            if (pData != 0)
                delete pData;
            delete reference;
        }
    };
 
    RedType* Data(void)    const { return pData; };
    RedType* operator-> () const { return pData; };
 
    const int RefCount(void) const { return reference->Count(); }
 
    RedRefCountContainer& operator = (const RedRefCountContainer& SmartPtr)
    {
        // Assignment operator
        if (this != &SmartPtr) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            reference->DecRef();
            if (reference->IsRefZero())
            {
                if (pData != 0)
                    delete pData;
                delete reference;
            }
           
            // Copy the data and reference pointer
            // and increment the reference count
            pData     = SmartPtr.pData;
            reference = SmartPtr.reference;
            reference->IncRef();
        }
        return *this;
    };
 
private:
    RedType*     pData;     // pointer
    RedRefCount* reference; // Reference count
};
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
} // Core
} // Red

