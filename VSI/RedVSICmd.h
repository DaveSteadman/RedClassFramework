// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

#pragma once

#include "RedLog.h"
#include "RedVSIContextInterface.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmd
{
public:

    virtual ~RedVSICmd(void) { };

    // Get the command type, allowing a caller to determine the type of a RedVSICmd
    // pointer.
    virtual RedVSILangElement Type(void) const =0;

    // Operation to queue up the top level expressions in a command. A separate class
    // determines the actual traversing of the parse-tree.
    virtual void QueueExpr(RedVSIContextInterface* pContext) =0;
    
    // Execute the command, assuming the expressions are all fully executed and the
    // results are available in the context.
    virtual void Execute(RedVSIContextInterface* pContext) =0;
    
    // Get the next command in the sequence (not including the branches of
    // conditional/iterative commands)
    RedVSICmd* NextCmd(void) const { return pNextCmd; };
    
    // Assign the next command in the sequence (not including command branches)
    void SetNextCmd(RedVSICmd* pNewNextCmd) { pNextCmd = pNewNextCmd; };

private:

    RedVSICmd* pNextCmd = NULL;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
