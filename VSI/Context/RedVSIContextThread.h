// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
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

