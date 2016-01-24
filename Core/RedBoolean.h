// -------------------------------------------------------------------------------------------------
// File: RedBoolean.h
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
    const int operator==(const RedBoolean& rhs) const { if (iState == rhs.iState) return 1; return 0; };
    const int operator!=(const RedBoolean& rhs) const { if (iState != rhs.iState) return 1; return 0; };

private:

    int iState;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedBoolean> RedBooleanSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedBoolean kBoolFALSE = RedBoolean::False();
static const RedBoolean kBoolTRUE  = RedBoolean::True();
static const RedBoolean kBoolYES   = RedBoolean::Yes();
static const RedBoolean kBoolNO    = RedBoolean::No();

} // Core
} // Red


