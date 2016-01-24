
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIDataList.h"
#include "RedVSIParseList.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class RedVSIRoutineCallInterface
{
public:

    // construction
    RedVSIRoutineCallInterface(void) { Init(); };
    ~RedVSIRoutineCallInterface();

    void            Init(void);

    void            SetupCall(RedString& cNewObjName, RedString& cNewClassName, RedString& cNewFuncName);
    //void            SetupObjCall(RedString& cNewObjName, RedString& cNewClassName, RedString& cNewFuncName);
    //void            SetupClassCall(RedString& cNewClassName, RedString& cNewFuncName);
    
    //int             IsObjCall(void) { return (!cObjName.IsEmpty()); };
    void            SetClassName(RedString& cNewClassName)  { cClassName = cNewClassName; };
    void            SetObjectName(RedString& cNewClassName) { cClassName = cNewClassName; };

    // Query
    //const int          IsInternalCall(void) const { return ( (cObjName.IsEmpty()) && (cClassName.IsEmpty()) ); };
    const RedString    ClassName(void)   const { return cClassName; };
    const RedString    ObjectName(void)  const { return cObjName; };
    const RedString    FuncName(void)    const { return cFuncName; };

    void               AppendParam(RedVariant& cNewParam) { cParams.AddLast(cNewParam); };
    RedVSIDataList*    GetParams(void)     { return &cParams; };

    void operator =(RedVSIRoutineCallInterface& cSig);
    
private:

    RedString         cClassName;
    RedString         cObjName;

    RedString         cFuncName;
    RedVSIDataList    cParams;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



