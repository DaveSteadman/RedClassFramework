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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedRefCount
{
public:
    RedRefCount(void) : count(0) {};
    void           IncRef(void)          { count++; };
    void           DecRef(void)          { count--; };
    const unsigned Count(void) const     { return count; };
    const int      IsRefZero(void) const { if (count==0) return 1; return 0; };
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


