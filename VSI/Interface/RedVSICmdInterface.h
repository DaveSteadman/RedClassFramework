
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedLog.h"
#include "RedVSIContextInterface.h"
#include "RedVSILangElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSICmdInterface
{
public:

    virtual ~RedVSICmdInterface(void) { };

    // Operation to queue up the top level expressions in a command. A separate class
    // determines the actual traversing of the parse-tree.
    virtual void                 QueueExpr(RedVSIContextInterface* pContext) =0;
    
    // Execute the command, assuming the expressions are all fully executed and the
    // results are available in the context.
    virtual void                 Execute(RedVSIContextInterface* pContext) =0;
    
    // Get the next command in the sequence (not including the branches of
    // conditional/iterative commands)
    virtual RedVSICmdInterface*  NextCmd(void) { return pNextCmd; };
    
    // Assign the next command in the sequence (not including command branches)
    void                         SetNextCmd(RedVSICmdInterface* pNewNextCmd) { pNextCmd = pNewNextCmd; };

    // Get the command type, allowing a caller to determine the type of a RedVSICmdInterface
    // pointer.
    virtual RedVSILangElement    Type(void) =0;

private:

    RedVSICmdInterface* pNextCmd;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
