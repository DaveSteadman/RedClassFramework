// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIRoutineCallInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {


RedVSIRoutineCallInterface::~RedVSIRoutineCallInterface()
{   
    cParams.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineCallInterface::Init(void)
{
    cClassName = ""; 
    cObjName   = ""; 
    cFuncName  = ""; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineCallInterface::SetupCall(RedString& cNewObjName, RedString& cNewClassName, RedString& cNewFuncName)
{
    cObjName   = cNewObjName; 
    cClassName = cNewClassName; 
    cFuncName  = cNewFuncName; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
void RedVSIRoutineCallInterface::SetupObjCall(RedString& cNewObjName, RedString& cNewFuncName) 
{ 
    cClassName = ""; 
    cObjName   = cNewObjName; 
    cFuncName  = cNewFuncName; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineCallInterface::SetupClassCall(RedString& cNewClassName, RedString& cNewFuncName) 
{ 
    cClassName = cNewClassName; 
    cObjName   = ""; 
    cFuncName  = cNewFuncName; 
}
*/
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
