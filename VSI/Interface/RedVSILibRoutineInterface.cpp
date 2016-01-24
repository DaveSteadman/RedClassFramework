// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  CRoutineSignatureInterface.cpp
//  Implementation of the Class CRoutineSignatureInterface
//  Created on:      07-May-2008 12:51:07
//  Original author: Sony
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILibRoutineInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

void RedVSILibRoutineInterface::Init(void)
{
    cName.Init(); 
    cParamList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSILibRoutineInterface::IsValid(void)
{
    if (cName.IsEmpty()) return 0;
    
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibRoutineInterface::GetDetails(RedString& cOutName, RedVSIStringLangElementMap& cOutParamList, RedVSICmdInterface*& pOutCode)
{
    cOutName      = cName;
    cOutParamList = cParamList;
    pOutCode      = pCode;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
