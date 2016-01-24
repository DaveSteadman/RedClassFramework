//
//  RedRefCountContainer.h
//
//  Created by Dave Steadman on 08/07/2014.
//  Copyright (c) 2014 Dave Steadman. All rights reserved.
//

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
    void      IncRef(void)    { count++; };
    void      DecRef(void)    { count--; };
    const int Count(void)     { return count; };
    const int IsRefZero(void) { if (count==0) return 1; return 0; };
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

