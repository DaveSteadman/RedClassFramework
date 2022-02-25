// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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
class RedDataBoolean : public RedType
{
public:

    // constructors
    RedDataBoolean()                           { SetFalse(); };
    RedDataBoolean(const RedDataBoolean& cVal) { iState = cVal.iState; };
    RedDataBoolean(const int& iVal)            { Set(iVal); };
    RedDataBoolean(const bool Val)             { Set(Val); };
    ~RedDataBoolean()                          { };
    
    // Inherited: RedType
    void               Init(void)          { SetFalse(); };
    RedDataType        Type(void) const    { return kDataTypeBool; };
    RedType*           Clone(void) const   { RedDataBoolean* newB = new RedDataBoolean(); newB->iState = iState; return dynamic_cast<RedType*>(newB); };

    // simple set/get operations
    void               SetTrue(void)       { iState=RED_TRUE; };
    void               SetFalse(void)      { iState=RED_FALSE; };

    void               Set(const int iVal);
    void               Set(const bool val) { if (val) SetTrue(); else SetFalse(); };
    void               Invert(void);

    bool               IsTrue(void)  const { return (iState == RED_TRUE);  };
    bool               IsFalse(void) const { return (iState == RED_FALSE); };

    static RedDataBoolean  True(void)  { RedDataBoolean cRetVal; cRetVal.SetTrue();  return cRetVal; };
    static RedDataBoolean  False(void) { RedDataBoolean cRetVal; cRetVal.SetFalse(); return cRetVal; };

    static RedDataBoolean  NOT(RedDataBoolean v1)                     { return RedDataBoolean(v1.IsFalse());                 };
    static RedDataBoolean  OR(RedDataBoolean v1, RedDataBoolean v2)   { return RedDataBoolean(v1.IsTrue()  || v2.IsTrue());  };
    static RedDataBoolean  NOR(RedDataBoolean v1, RedDataBoolean v2)  { return RedDataBoolean(v1.IsFalse() || v2.IsFalse()); };
    static RedDataBoolean  AND(RedDataBoolean v1, RedDataBoolean v2)  { return RedDataBoolean(v1.IsTrue()  && v2.IsTrue());  };
    static RedDataBoolean  XOR(RedDataBoolean v1, RedDataBoolean v2)  { return RedDataBoolean(v1.IsTrue()  != v2.IsTrue());  };
    static RedDataBoolean  NAND(RedDataBoolean v1, RedDataBoolean v2) { return RedDataBoolean(v1.IsFalse() && v2.IsFalse()); };

    void      operator =(const RedDataBoolean& cVal) { iState = cVal.iState; };
    void      operator =(const bool        val ) { if (val) iState=RED_TRUE; else iState=RED_FALSE; };
    
    // Obtain the integer representation of the object for serialisation
    const int intState(void) const { return iState; };

private:

    int iState;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataBoolean& lhs, const RedDataBoolean& rhs);
bool operator!=(const RedDataBoolean& lhs, const RedDataBoolean& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedDataBoolean> RedDataBooleanSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDataBoolean kBoolFALSE = RedDataBoolean::False();
static const RedDataBoolean kBoolTRUE  = RedDataBoolean::True();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


