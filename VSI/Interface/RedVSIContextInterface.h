
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIRoutineCallInterface.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// define the RedVSICmdInterface class without a #include specifically to avoid
// a circular dependency.
class RedVSICmdInterface;
class RedVSIParseTreeInterface;
class RedVSIContextRoutine;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Interface class used to pass the context between the command and parse tree elements.

class RedVSIContextInterface
{
public:

    // Data accessors
    virtual RedType*      CreateDataItem(RedVSILangElement cLocation, RedVSILangElement cType, RedString cName) =0;
    virtual int           FindDataItem(const RedString& cName, RedType*& pData) =0;
    virtual int           SetReturnValue(RedVariant& cData) =0;

    // expressions
    virtual void          QueueExpr(RedVSIParseTreeInterface* pExpr) =0;
    virtual void          SetExprResult(RedVSIParseTreeInterface* pExpr, RedVariant& result) =0;
    virtual RedVariant    GetExprResult(RedVSIParseTreeInterface* pExpr) =0;

    // Error reporting and debugging
    virtual RedLog&       Log(void) { return log; };

    // Routine creation and control
    virtual void          SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature) =0;
    virtual int           IsBlocked(const RedVSIContextRoutine* pRoutineContext) =0;
    virtual void          QueueCommand(RedVSICmdInterface* pCmd) =0;
    virtual void          ClearCommandQueue(void) =0;
    virtual RedString     ClassName(void) const =0;
    virtual RedString     ObjectName(void) const =0;

private:
    RedLog log;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

