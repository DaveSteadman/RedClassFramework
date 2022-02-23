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
#include "RedVSILangElement.h"
#include "RedVSIRoutineCallInterface.h"
#include "RedVSIContextThread.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef enum TECmdExecutePhases
{
    eCmdExecPhaseStart,
    eCmdExecPhaseExprQueued,
    eCmdExecPhaseExprExecuting,
    eCmdExecPhaseCmdLogic,
    eCmdExecPhaseCmdNextSetup

} TECmdExecutePhases;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class to represent the context required to execute a routine.
/// Uses parent class RedVSIContextInterface, allowing code-fragments and simple command sequences to
/// be executed in a lightweight environment.
class RedVSIContextRoutine : public RedVSIContextInterface
{
public:

    // Construction Routines
    RedVSIContextRoutine(RedLog* pInitLog);
    RedVSIContextRoutine(RedLog* pInitLog, RedVSICmdInterface* pFirstCmd);
    RedVSIContextRoutine(RedLog* pInitLog, const RedString& inClassName, const RedString& inRoutineName, RedVSICmdInterface* pFirstCmd);

    ~RedVSIContextRoutine(void);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // RedVSIContextInterface Inhertied Interface

    // Data accessors (RedVSIContextInterface)
    RedType*        CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName);
    RedType*        DuplicateDataItem(const RedVSILangElement& cLocation, const RedType* pDataItem, const RedString& cName);
    bool            FindDataItem(const RedString& cName, RedType*& pData);
    RedVariant      DataItemAsVariant(const RedString& cName);

    RedVSILib*      FindCodeLib(void);

    // Inhertied Expressions (RedVSIContextInterface)
    void            QueueExpr(RedVSIParseTreeInterface* pExpr);
    void            SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result);
    RedVariant      ExprResult(RedVSIParseTreeInterface* pExpr);
    void            ExecuteExprQueue(void);

    // Error reporting and debugging
    RedLog*         Log(void) { return pLog; };

    // Setup Calls
    void            SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature);
    void            QueueCommand(RedVSICmdInterface* pCmd) { if (pCmd != NULL) cCmdStack.Push(pCmd); else pCurrCmd = pCmd; };
    void            ClearCommandQueue(void) { cCmdStack.DelAll(); pCurrCmd = NULL; };
    void            SetValueToReturn(const RedVariant& cData);
    bool            IsExecutionComplete(void) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool            IsContextBlocked(const RedVSIContextRoutine* pRoutineContext) const;
    bool            IsContextExecutionComplete(const RedVSIContextRoutine* pRoutineContext) const;

    void            SetParamsList(RedRecord* pParamData);

    //    void                       SetRoutineCallData(const RedVSIRoutineCallInterface& d) { cRoutineCall = d; };
    //    RedVSIRoutineCallInterface RoutineCallData(void)                                   { return cRoutineCall; };


        // Inherited Routine creation and control (RedVSIContextInterface)
    RedVariant& ValueToReturn(void) { return cReturnValue; };
    void         SetReturnedValue(const RedVariant& cData);


    //void            SetSubroutineReturnValue(RedVariant& cData);
    //RedVSIObject*   GetThisObj(void) { return pThisObj; };

    // Execution
    void            Execute(const unsigned CmdCount);
    bool            HasCmdToExecute(void) const;

    void  SetRoutineName(const RedString& rname) { RoutineName = rname; };
    void  SetClassName(const RedString& cname) { ClassName = cname; };

    void                 SetThreadContextRecord(RedVSIContextThread* pCntxtRecord) { pThreadContextRecord = pCntxtRecord; };
    RedVSIContextThread* ThreadContextRecord(void)                                  const { return pThreadContextRecord; };

private:

    // Execution
    RedString RoutineName;
    RedString ClassName;

    /// Curr command initialised to zero, command popped off the stack.
    /// expressions for that command evaluated, then the command is evaluated
    /// which leads to a change on the stack. Following exection, the curr is cleared.
    RedVSICmdInterface* pCurrCmd;

    TECmdExecutePhases eCmdPhase;

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

    /// Pointer to the object associated to the routine call
    //RedVSIObject*        pThisObj;

    /// Variables and values created during the execution of the routine, including the parameters
    RedRecord cLocalVariables;

    // The data to be returned to the calling routine
    RedVariant cReturnValue;

    /// Record holding thread data
    RedVSIContextThread* pThreadContextRecord;

    /// Logging
    RedLog* pLog;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

