// -------------------------------------------------------------------------------------------------
// File: RedBoolean.cpp
// -------------------------------------------------------------------------------------------------

#include "RedBoolean.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBoolean::Set(const int iVal)
{
    if      (iVal == RED_YES)   iState = RED_YES;
    else if (iVal == RED_NO)    iState = RED_NO;
    else if (iVal == RED_TRUE)  iState = RED_TRUE;
    else if (iVal == RED_FALSE) iState = RED_FALSE;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedBoolean RedBoolean::Not(const RedBoolean val)
{
    if      (val.iState == RED_YES)   return kBoolNO;
    else if (val.iState == RED_NO)    return kBoolYES;
    else if (val.iState == RED_TRUE)  return kBoolFALSE;
    else if (val.iState == RED_FALSE) return kBoolTRUE;

    return kBoolFALSE;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedBoolean::Invert(void)
{
    if      (iState == RED_YES)   iState = RED_NO;
    else if (iState == RED_NO)    iState = RED_YES;
    else if (iState == RED_TRUE)  iState = RED_FALSE;
    else if (iState == RED_FALSE) iState = RED_TRUE;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

