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
/// Uses parent class RedVSIContextInterface, allowing code-fragments and simple command sequences to
/// be executed in a lightweight environment.
class RedVSIContextRoutine : public RedVSIContextInterface
{
public:

    RedVSIContextRoutine(RedLog& initAnalysis);

    // Init with command for running a fragment
    RedVSIContextRoutine(RedLog& initAnalysis, RedVSICmdInterface* pFragmentCmd);
    ~RedVSIContextRoutine(void);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // RedVSIContextInterface Inhertied Interface

    // Data accessors (RedVSIContextInterface)
    RedType*       CreateDataItem(const RedVSILangElement& cLocation, const RedVSILangElement& cType, const RedString& cName);
    int            FindDataItem  (const RedString& cName, RedType*& pData);
    void           SetReturnValue(const RedVariant& cData);

    // Inhertied Expressions (RedVSIContextInterface)
    void            QueueExpr(RedVSIParseTreeInterface* pExpr);
    void            SetExprResult(RedVSIParseTreeInterface* pExpr, const RedVariant& result);
    RedVariant      ExprResult(RedVSIParseTreeInterface* pExpr);

    // Error reporting and debugging
    RedLog&         Log(void) { return cAnalysis; };

    // Setup Calls
    void            SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature);
    bool            IsBlocked(const RedVSIContextInterface* pRoutineContext) { return false; };
    void            QueueCommand(RedVSICmdInterface* pCmd)                 { cCmdStack.Push(pCmd); };
    void            ClearCommandQueue(void)                                { cCmdStack.DelAll(); };
    RedString       ClassName(void) const                                  { return cClassName; };
    RedString       ObjectName(void) const                                 { return cObjectName; };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void            SetParamsList(RedRecord* pParamData);

    void            ExecuteExprQueue(void);

//    void            SetNameDetails(RedString& cNewObjectName, RedString& cNewClassName, RedString& cNewFuncName);
//    void            AddParam(RedString cName, RedType* pData);
//    void            AddReturnValue(RedVariant& cNewReturnValue) { cReturnValue = cNewReturnValue; };
    // void            SetThisObj(RedType* pNewThisObject) { pThisObj=pNewThisObject; };

    // Inherited Routine creation and control (RedVSIContextInterface)
    RedVariant&     GetReturnValue(void) { return cReturnValue; };
    void            SetSubroutineReturnValue(RedVariant& cData);
    //RedVSIObject*   GetThisObj(void) { return pThisObj; };


    // Execution
    // void            Execute(CInterfaceContext* pTopLevelContext);


    void            ExecuteSnippet(const unsigned CmdCount);
    int             HasCmdToExecute(void);

private:

    // Execution
    RedString         cObjectName;
    RedString         cClassName;
    RedString         cFuncName;
    
    /// Curr command initialised to zero, command popped off the stack.
    /// expressions for that command evaluated, then the command is evaluated
    /// which leads to a change on the stack. Following exection, the curr is cleared.
    RedVSICmdInterface*      pCurrCmd;

    /// The currently considered expression. Zero when starting a routine or between commands,
    /// but maintains the address of the expression when the routine is blocked.
    RedVSIParseTreeInterface* pCurrExpr;

    /// The stack of commands in the routine. Added to by commands stacking up their
    /// branched and subsequent commands. Reduced by the context executing them.
    RedVSICmdStack       cCmdStack;
    
    /// The list of parse tree nodes which need to be executed IN ORDER before
    /// the pCurrCmd can be executed
    RedVSIParseStack     cExprStack;

    // Pointer to the object associated to the routine call
    //RedVSIObject*        pThisObj;
    
    // Variables and values created during the execution of the routine, including
    // the parameters
//    RedVSIStringDataMap   cRoutineData;
    RedRecord   cRoutineData;

    // The data to be returned to the calling routine
    RedVariant        cReturnValue;
    
    // The list of working data items from the evaluation of expressions. Cleared between 
    // each command call.
    RedVSIParseDataMap    cWorkingList;

    RedLog& cAnalysis;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

