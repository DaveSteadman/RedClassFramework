// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2021 David G. Steadman
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
// An RGBA color class.

class RedColor : public RedType
{
public:

    // constructors
    RedColor()                          { SetOpaqueBlack(); };
	RedColor(const RedColor& cVal)      { Set(cVal); };
	RedColor(unsigned uNewR, unsigned uNewG, unsigned uNewB, unsigned uNewA) { Set(uNewR, uNewG, uNewB, uNewA); };
    ~RedColor()                       { };
 
    // Inherited: RedType
    void               Init(void)          { SetFalse(); };
    RedDataType        Type(void) const    { return kDataTypeBool; };
    RedType*           Clone(void) const   { RedBoolean* newB = new RedBoolean(); newB->iState = iState; return dynamic_cast<RedType*>(newB); };

    // simple set/get operations

    void               SetOpaqueBlack(void) { uR = 0; uG = 0; uB = 0; uA = 255; };
    void               SetOpaqueWhite(void) { uR = 255; uG = 255; uB = 255; uA = 255; };
    void               Set(const RedColor& cVal) { uR = cVal.uR; uG = cVal.uG; uB = cVal.uB; uA = cVal.uA; };
    void               Set(unsigned uNewR, unsigned uNewG, unsigned uNewB, unsigned uNewA) { uR = uNewR; uG = uNewG; uB = uNewB; uA = uNewA; };

    void               Invert(void);


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

public:
    unsigned uR; // 0 to 255
	unsigned uG; // 0 to 255
	unsigned uB; // 0 to 255
	unsigned uA; // 0 to 255
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


