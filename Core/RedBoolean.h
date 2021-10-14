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

#include "RedType.h"
#include "RedSmartPtr.h"
#include "RedDataType.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define RED_TRUE  1
#define RED_FALSE 0

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Boolean value class. As a child of RedType class, this allows a boolean value to exist in 
// collections and VSI expressions alongside other RedType objects. The primary purpose of the class 
// isn't to replace a bool type in normal operation, which is useful in conditional statements.
class RedBoolean : public RedType
{
public:

    // constructors
    RedBoolean()                           { SetFalse(); };
    RedBoolean(const RedBoolean& cVal)     { iState = cVal.iState; };
    RedBoolean(const int& iVal)            { Set(iVal); };
    RedBoolean(const bool Val)             { Set(Val); };
    ~RedBoolean()                          { };
    
    // Inherited: RedType
    void               Init(void)          { SetFalse(); };
    RedDataType        Type(void) const    { return kDataTypeBool; };
    RedType*           Clone(void) const   { RedBoolean* newB = new RedBoolean(); newB->iState = iState; return dynamic_cast<RedType*>(newB); };

    // simple set/get operations
    void               SetTrue(void)       { iState=RED_TRUE; };
    void               SetFalse(void)      { iState=RED_FALSE; };

    void               Set(const int iVal);
    void               Set(const bool val) { if (val) SetTrue(); else SetFalse(); };
    void               Invert(void);

    bool               IsTrue(void)  const { return (iState == RED_TRUE);  };
    bool               IsFalse(void) const { return (iState == RED_FALSE); };

    static RedBoolean  True(void)  { RedBoolean cRetVal; cRetVal.SetTrue();  return cRetVal; };
    static RedBoolean  False(void) { RedBoolean cRetVal; cRetVal.SetFalse(); return cRetVal; };

    static RedBoolean  NOT(RedBoolean v1)                 { return RedBoolean(v1.IsFalse());                 };
    static RedBoolean  OR(RedBoolean v1, RedBoolean v2)   { return RedBoolean(v1.IsTrue()  || v2.IsTrue());  };
    static RedBoolean  NOR(RedBoolean v1, RedBoolean v2)  { return RedBoolean(v1.IsFalse() || v2.IsFalse()); };
    static RedBoolean  AND(RedBoolean v1, RedBoolean v2)  { return RedBoolean(v1.IsTrue()  && v2.IsTrue());  };
    static RedBoolean  XOR(RedBoolean v1, RedBoolean v2)  { return RedBoolean(v1.IsTrue()  != v2.IsTrue());  };
    static RedBoolean  NAND(RedBoolean v1, RedBoolean v2) { return RedBoolean(v1.IsFalse() && v2.IsFalse()); };

    void      operator =(const RedBoolean& cVal) { iState = cVal.iState; };
    void      operator =(const bool        val ) { if (val) iState=RED_TRUE; else iState=RED_FALSE; };
    
    // Obtain the integer representation of the object for serialisation
    const int intState(void) const { return iState; };

private:

    int iState;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedBoolean& lhs, const RedBoolean& rhs);
bool operator!=(const RedBoolean& lhs, const RedBoolean& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedBoolean> RedBooleanSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedBoolean kBoolFALSE = RedBoolean::False();
static const RedBoolean kBoolTRUE  = RedBoolean::True();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


