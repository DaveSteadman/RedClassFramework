// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSICmdInterface.h"


#include "RedVSILangElement.h"
#include "RedVSIContextInterface.h"
#include "RedVSIContextRoutine.h"
#include "RedVSILibInterface.h"
#include "RedVSILibRoutineInterface.h"
#include "RedVSIRoutineCallInterface.h"


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIContextThread : public RedVSIContextInterface
{
public:

    RedVSIContextThread(void);
    void           SetCodeLib(RedVSILibInterface* pNewCodeLib) { pCodeLib = pNewCodeLib; };

    // Data accessors
    RedType*       CreateDataItem(RedVSILangElement cLocation, RedVSILangElement cType, RedString cName);
    int            FindDataItem(RedString cName, RedType*& pData);
    void           SetUserObj(RedRecord* pNewUserObject) { pUserObj=pNewUserObject; };
    RedRecord*     GetUserObj(void) { return pUserObj; };
    int            AssignReturnValue(RedVariant& cData);
    
    // Expressions
    void           QueueExpr(RedVSIParseTreeInterface* pExpr);
    void           SetExprResult(RedVSIParseTreeInterface* pExpr, RedVariant& result);
    RedVariant     GetExprResult(RedVSIParseTreeInterface* pExpr);

    // Error reporting and debugging
    RedLog& GetAnalysis(void) { return cAnalysis; };

    // Routine creation and control
    void           SetupRoutineCall(RedVSIRoutineCallInterface& cSignature);
    void           Execute(int& iCmdCount);
    void           QueueCommand(RedVSICmdInterface* pCmd);
    void           ClearCommandQueue(void);
    RedString      ClassName(void);
    RedString      ObjectName(void);
    int            IsBlocked(RedVSIContextRoutine* pRoutineContext);

private:

    /// replace with datacentre
    typedef RedStackLIFO<RedVSIContextRoutine*>          RedVSIRoutineContextStack;

    // Routine Context
    RedVSIRoutineContextStack cRoutineStack;

    // Static Code
    RedVSILibInterface*      pCodeLib;

    // Data attributes
    RedRecord*        pUserObj;

    // debugging
    RedLog       cAnalysis;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

