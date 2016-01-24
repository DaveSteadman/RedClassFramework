
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSICollections.h"
#include "RedVSICmdInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;


// Class has only read-only routines, so the consumers of the routines have no access to change anything.
// The Child RedVSILibRoutine class is contained within the library construction code.

class RedVSILibRoutineInterface
{
public:

    RedVSILibRoutineInterface(void) { Init(); };
    ~RedVSILibRoutineInterface(void) {  };

    void Init(void);
    int  IsValid(void);
    
    RedString                   Name(void)              { return cName; };
    int                         NumParams(void)         { return cParamList.NumItems(); };
    RedVSIStringLangElementMap* Params(void)            { return &cParamList; };
    RedVSICmdInterface*         FirstCommand(void)      { return pCode; };

    void GetDetails(RedString& cOutName, RedVSIStringLangElementMap& cOutParamList, RedVSICmdInterface*& pOutCode);

protected:
    RedString                   cName;
    RedVSIStringLangElementMap  cParamList;
    RedVSICmdInterface*         pCode;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
