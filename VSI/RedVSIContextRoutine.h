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

#include "RedCoreNamespace.h"

#include "RedVSICollections.h"
#include "RedVSICmd.h"
#include "RedVSILangElement.h"
#include "RedVSIRoutineCallInterface.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

class RedVSIContextBase;
class RedVSILib;

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

// Class to represent the context required to execute a routine.
// Uses parent class RedVSIContextRoutine, allowing code-fragments and simple command sequences to
// be executed in a lightweight environment.
class RedVSIContextRoutine
{
public:

    // Construction Routines
    RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext);
    RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext, RedVSICmd* pFirstCmd);
    RedVSIContextRoutine(RedVSIContextBase* pInitBaseContext, const RedDataString& inClassName, const RedDataString& inRoutineName, RedVSICmd* pFirstCmd);

    ~RedVSIContextRoutine(void);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // RedVSIContextRoutine Inhertied Interface

    // Data accessors (RedVSIContextRoutine)
    RedData*        CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedDataString& cName);
    RedData*        DuplicateDataItem(const RedVSILangElement& cLocation, const RedData* pDataItem, const RedDataString& cName);
    bool            FindDataItem(const RedDataString& cName, RedData*& pData);
    RedDataVariant  DataItemAsVariant(const RedDataString& cName);

    RedVSILib*      FindCodeLib(void);

    // Inhertied Expressions (RedVSIContextRoutine)
    void            QueueExpr(RedVSIParseTreeInterface* pExpr);
    void            SetExprResult(RedVSIParseTreeInterface* pExpr, const RedDataVariant& result);
    RedDataVariant  ExprResult(RedVSIParseTreeInterface* pExpr);
    void            ExecuteExprQueue(void);

    // Setup Calls
    void            SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature);
    void            QueueCommand(RedVSICmd* pCmd) { if (pCmd != NULL) cCmdStack.Push(pCmd); else pCurrCmd = pCmd; };
    void            ClearCommandQueue(void) { cCmdStack.DelAll(); pCurrCmd = NULL; };
    void            SetValueToReturn(const RedDataVariant& cData);
    bool            IsExecutionComplete(void) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool            IsContextBlocked(const RedVSIContextRoutine* pRoutineContext) const;
    bool            IsContextExecutionComplete(const RedVSIContextRoutine* pRoutineContext) const;

    void            SetParamsList(RedDataRecord* pParamData);

    //    void                       SetRoutineCallData(const RedVSIRoutineCallInterface& d) { cRoutineCall = d; };
    //    RedVSIRoutineCallInterface RoutineCallData(void)                                   { return cRoutineCall; };

        // Inherited Routine creation and control (RedVSIContextRoutine)
    RedDataVariant& ValueToReturn(void) { return cReturnValue; };
    void         SetReturnedValue(const RedDataVariant& cData);


    //void            SetSubroutineReturnValue(RedDataVariant& cData);
    //RedVSIObject*   GetThisObj(void) { return pThisObj; };

    // Execution
    void            Execute(const unsigned CmdCount);
    bool            HasCmdToExecute(void) const;

    void  SetRoutineName(const RedDataString& rname) { RoutineName = rname; };
    void  SetClassName(const RedDataString& cname)   { ClassName = cname; };

    void               SetBaseContext(RedVSIContextBase* pNewBaseContext) { pBaseContext = pNewBaseContext; };
    RedVSIContextBase* BaseContext(void)                            const { return pBaseContext; };

private:

    // Execution
    RedDataString RoutineName = "";
    RedDataString ClassName   = "";

    // Curr command initialised to zero, command popped off the stack.
    // expressions for that command evaluated, then the command is evaluated
    // which leads to a change on the stack. Following exection, the curr is cleared.
    RedVSICmd* pCurrCmd = NULL;

    TECmdExecutePhases eCmdPhase = eCmdExecPhaseStart;

    // The stack of commands in the routine. Added to by commands stacking up their
    // branched and subsequent commands. Reduced by the context executing them.
    RedVSICmdStack cCmdStack;

    // The currently considered expression. Zero when starting a routine or between commands,
    // but maintains the address of the expression when the routine is blocked.
    RedVSIParseTreeInterface* pCurrExpr = NULL;

    // The list of parse tree nodes which need to be executed IN ORDER before
    // the pCurrCmd can be executed
    RedVSIParseStack cExprStack;

    // The list of working data items from the evaluation of expressions. Cleared between
    // each command call.
    RedVSIParseDataMap cExprResultList;

    // Pointer to the object associated to the routine call
    //RedVSIObject*        pThisObj;

    // Variables and values created during the execution of the routine, including the parameters
    RedDataRecord cLocalVariables;

    // The data to be returned to the calling routine
    RedDataVariant cReturnValue;

    // Record holding thread data
    // Contains log
    RedVSIContextBase* pBaseContext = NULL;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

