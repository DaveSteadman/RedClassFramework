// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseDataMap.h"
#include "RedVSIStringDataMap.h"
#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedVSICmdStack.h"
#include "RedVSICmdInterface.h"
#include "RedVSIParseStack.h"
#include "RedVSIObject.h"
#include "RedVSILangElement.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    class RedVSIContextRoutine : public RedVSIContextInterface
    {
    public:

        RedVSIContextRoutine(void);
        ~RedVSIContextRoutine(void);

        // Setup Calls
        void            SetNameDetails(RedString& cNewObjectName, RedString& cNewClassName, RedString& cNewFuncName);
        void            AddParam(RedString cName, RedType* pData);
        void            AddReturnValue(RedVariant& cNewReturnValue) { cReturnValue = cNewReturnValue; };
        // void            SetThisObj(RedType* pNewThisObject) { pThisObj=pNewThisObject; };
        void            SetParamsList(RedVSIStringDataMap* pParamData);

        // Inhertied Data accessors (RedVSIContextInterface)
        RedType*        CreateDataItem(RedVSILangElement cLocation, RedVSILangElement cType, RedString cName);
        int             FindDataItem(const RedString& cName, RedType*& pData);
        int             SetReturnValue(RedVariant& cData);

        // Inhertied Expressions (RedVSIContextInterface)
        void            QueueExpr(RedVSIParseTreeInterface* pExpr);
        void            SetExprResult(RedVSIParseTreeInterface* pExpr, RedVariant& result);
        RedVariant      GetExprResult(RedVSIParseTreeInterface* pExpr);
        void            ExecuteExprQueue(void);

        // Inherited Routine creation and control (RedVSIContextInterface)
        RedVariant&     GetReturnValue(void) { return cReturnValue; };
        void            SetSubroutineReturnValue(RedVariant& cData);
        RedVSIObject*   GetThisObj(void) { return pThisObj; };

        void            SetupRoutineCall(const RedVSIRoutineCallInterface& cSignature) { }; // ***
        int             IsBlocked(const RedVSIContextRoutine* pRoutineContext) { return 0; }; // ***
        void            QueueCommand(RedVSICmdInterface* pCmd) { cCmdStack.Push(pCmd); };
        void            ClearCommandQueue(void) { cCmdStack.DelAll(); };
        RedString       ClassName(void) const  { return cClassName; };
        RedString       ObjectName(void) const { return cObjectName; };


        // Execution
        // void            Execute(CInterfaceContext* pTopLevelContext);


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

        // Data
        RedVSIObject*        pThisObj;
        
        // Variables and values created during the execution of the routine, including
        // the parameters
        RedVSIStringDataMap   cRoutineData;
        
        // The data to be returned to the calling routine
        RedVariant        cReturnValue;
        
        // The list of working data items from the evaluation of expressions. Cleared between 
        // each command call.
        RedVSIParseDataMap    cWorkingList;
    };

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

