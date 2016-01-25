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

#define RED_YES   1
#define RED_NO    0
#define RED_TRUE  1
#define RED_FALSE 0

class RedString;

/// Boolean value class. Child of RedType class.
class RedBoolean : public RedType
{
public:

    // constructors
    RedBoolean()                       { SetFalse(); };
    RedBoolean(const RedBoolean& cVal) { iState = cVal.iState; };
    RedBoolean(const int& iVal)        { Set(iVal); };
    ~RedBoolean()                      { };
    
    // Inherited: RedType
    void                Init(void)        { SetFalse(); };
    const RedDataType   Type(void) const  { return kDataTypeBool; };
    RedType*            Clone(void) const { RedBoolean* newB = new RedBoolean(); newB->iState = iState; return (RedType*)newB; };

    // simple set/get operations
    void               SetYes(void)        { iState=RED_YES; };
    void               SetNo(void)         { iState=RED_NO; };
    void               SetTrue(void)       { iState=RED_TRUE; };
    void               SetFalse(void)      { iState=RED_FALSE; };

    void               Set(const int iVal);
    void               Invert(void);
    const RedBoolean   Not(const RedBoolean val);

    const int          IsYes(void)   const { if (iState == RED_YES)   return 1; return 0; };
    const int          IsNo(void)    const { if (iState == RED_NO)    return 1; return 0; };
    const int          IsTrue(void)  const { if (iState == RED_TRUE)  return 1; return 0; };
    const int          IsFalse(void) const { if (iState == RED_FALSE) return 1; return 0; };

    static RedBoolean  True(void)  { RedBoolean cRetVal; cRetVal.SetTrue();  return cRetVal; };
    static RedBoolean  False(void) { RedBoolean cRetVal; cRetVal.SetFalse(); return cRetVal; };
    static RedBoolean  Yes(void)   { RedBoolean cRetVal; cRetVal.SetYes();   return cRetVal; };
    static RedBoolean  No(void)    { RedBoolean cRetVal; cRetVal.SetNo();    return cRetVal; };

    void      operator =(const RedBoolean cVal) { iState = cVal.iState; };
    
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
static const RedBoolean kBoolYES   = RedBoolean::Yes();
static const RedBoolean kBoolNO    = RedBoolean::No();

} // Core
} // Red


