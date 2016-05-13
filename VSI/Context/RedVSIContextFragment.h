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

#include "RedCoreNamespace.h"

#include "RedVSICollections.h"
#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedVSIObject.h"
#include "RedVSILangElement.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class to represent the context required to execute a routine.
/// Uses parent class RedVSIContextInterface, allowing code-fragments and simple command sequences
/// to be executed in a lightweight environment.
class RedVSIContextFragment : public RedVSIContextInterface
{
public:

    // Construction Routines
    RedVSIContextFragment(RedLog& initAnalysis);
    RedVSIContextFragment(RedLog& initAnalysis, RedVSICmdInterface* pFragmentCmd);
    ~RedVSIContextFragment(void);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // RedVSIContextInterface Inhertied Interface

    // Data accessors (RedVSIContextInterface)
    RedType*        CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName);
    RedType*        DuplicateDataItem(const RedVSILangElement& cLocation, const RedType* pDataItem, const RedString& cName);
    bool            FindDataItem  (const RedString& cName, RedType*& pData);
    RedVariant      DataItemAsVariant(const RedString& cName);

    // Inhertied Expressions (RedVSIContextInterface)
    void            QueueExpr(RedVSIParseTreeInterface* pExpr);
    void            SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result);
    RedVariant      ExprResult(RedVSIParseTreeInterface* pExpr);
    void            ExecuteExprQueue(void);

    // Error reporting and debugging
    RedLog&         Log(void) { return cAnalysis; };

    // Setup Calls
    void            SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature) { };
    bool            IsBlocked(const RedVSIContextInterface* pRoutineContext) { return false; };
    void            QueueCommand(RedVSICmdInterface* pCmd)                   { if (pCmd != NULL) cCmdStack.Push(pCmd); else pCurrCmd = pCmd; };
    void            ClearCommandQueue(void)                                  { cCmdStack.DelAll(); pCurrCmd=NULL; };
    void            SetValueToReturn(const RedVariant& cData)                { };
    bool            IsExecutionComplete(void) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Execution
    void            Execute(const unsigned CmdCount);
    bool            HasCmdToExecute(void);

private:

    void            SetTopCmd(RedVSICmdInterface* pFragmentCmd);

    /// A fragment owns the code it executes. We maintain a pointer to the top command so we can
    /// delete it when finished.
    RedVSICmdInterface* pTopCmd;

    /// Curr command initialised to zero, command popped off the stack.
    /// expressions for that command evaluated, then the command is evaluated
    /// which leads to a change on the stack. Following exection, the curr is cleared.
    RedVSICmdInterface* pCurrCmd;

    /// The stack of commands in the routine. Added to by commands stacking up their
    /// branched and subsequent commands. Reduced by the context executing them.
    RedVSICmdStack cCmdStack;

    /// The currently considered expression. Zero when starting a routine or between commands,
    /// but maintains the address of the expression when the routine is blocked.
    RedVSIParseTreeInterface* pCurrExpr;

    /// The list of parse tree nodes which need to be executed IN ORDER before
    /// the pCurrCmd can be executed
    RedVSIParseStack cExprStack;

    /// The list of working data items from the evaluation of expressions. Cleared between
    /// each command call.
    RedVSIParseDataMap cExprResultList;

    /// Variables and values created during the execution of the routine, including the parameters
    RedRecord cLocalVariables;

    /// Log object
    RedLog& cAnalysis;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

