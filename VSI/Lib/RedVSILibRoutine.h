
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedString.h"
#include "RedVSICmdInterface.h"
#include "RedVSILibRoutineInterface.h"
#include "RedVSILibRoutineInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSILibRoutine : public RedVSILibRoutineInterface
{
public:

    RedVSILibRoutine(void);

    void          SetName (const RedString& cNewName)                            { cName = cNewName; };
    void          AddParam(const RedString& cParamName, RedVSILangElement cType) { cParamList.Add(cParamName, cType); };
    void          SetCode (RedVSICmdInterface* pNewCode)                         { pCode = pNewCode; };

    const int     IsMatching(RedVSIRoutineCallInterface& cSig);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

