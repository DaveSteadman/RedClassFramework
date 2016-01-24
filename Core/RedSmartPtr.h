
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include <cassert>
#include <iostream>
#include <typeinfo>

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

template < typename T > class RedSmartPtr
{
public:
    RedSmartPtr() : pData(0), reference(0)
    {
        // Create a new reference
        reference = new RedRefCount();

        // Increment the reference count
        reference->IncRef();
    };

    RedSmartPtr(T* pValue) : pData(pValue), reference(0)
    {
        // Create a new reference
        reference = new RedRefCount();

        // Increment the reference count
        reference->IncRef();
    };

    RedSmartPtr(const RedSmartPtr<T>& SmartPtr) : pData(SmartPtr.pData), reference(SmartPtr.reference)
    {
        // Copy constructor
        // Copy the data and reference pointer
        // and increment the reference count
        reference->IncRef();
    };

    ~RedSmartPtr()
    {
        // Destructor
        // Decrement the reference count
        // if reference become zero delete the data
        reference->DecRef();
        if (reference->Count() == 0)
        {
            delete pData;
            delete reference;
        }
    };

    T* Data(void) { return pData; };

    T* operator* ()  { return pData; };

    //T& operator* ()  { return *pData; };
    T* operator-> () { return pData;  };

    const int RefCount(void) { return reference->Count(); }

    RedSmartPtr<T>& operator = (const RedSmartPtr<T>& SmartPtr)
    {
        // Assignment operator
        if (this != &SmartPtr) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            reference->DecRef();
            if (reference->IsRefZero())
            {
                delete pData;
                delete reference;
            }
            
            // Copy the data and reference pointer
            // and increment the reference count
            pData = SmartPtr.pData;
            reference = SmartPtr.reference;
            reference->IncRef();
        }
        return *this;
    };

private:
    T*           pData;     // pointer
    RedRefCount* reference; // Reference count

};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


