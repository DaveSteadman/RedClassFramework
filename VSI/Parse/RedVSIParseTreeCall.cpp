
#include "RedVSIParseTreeCall.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Constructors
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIParseTreeCall::~RedVSIParseTreeCall()
{
/*    if (!pParamList->IsEmpty())
    {
        ParamListItType cListIt(pParamList);

        cListIt.First();
        while (!cListIt.IsDone())
        {
            SParam* pParamStruct = cListIt.CurrentItem();

            delete pParamStruct->pParam;
            delete pParamStruct;

            cListIt.Next();
        }
    }*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeCall::SetDetails(const RedString& cInObjName, const RedString& cInClassName, const RedString& cInFuncName, RedVSIParseList*& pInParamList)
{
    cObjectName = cInObjName;
    cClassName  = cInClassName;
    cFuncName   = cInFuncName;
    pParamList  = pInParamList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIParseTreeCall::GetDetails(RedString& cOutObjName, RedString& cOutClassName, RedString& cOutFuncName, RedVSIParseList*& pOutParamList)
{
    cOutObjName   = cObjectName;
    cOutClassName = cClassName;
    cOutFuncName  = cFuncName;
    pOutParamList = pParamList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// The call to calculate a routine call results in the creation of a new layer on the stack.
// The execution then has to go back to the thread, to realise it needs to be a level higher
// start processing the new routine's commands.

void RedVSIParseTreeCall::CalcResult(RedVSIContextInterface* pContext)
{ 
/*
    // The params results list
    RedVSILibRoutineInterface cCall;

    // Assign the object anbd class information, even if its blank
    cCall.SetupCall(cObjectName, cClassName, cFuncName);

    // loop through the params list to calculate any we don't have a result for
    RedVSIParseListIterator cParseIt(pParamList);
    cParseIt.First();
    while(!cParseIt.IsDone())
    {
        // get the current parameter
        RedVSIParseTreeInterface* pCurrParam = cParseIt.CurrentItem();

        // add the result of the expr to the param list
        cCall.AppendParam(pContext->GetExprResult(pCurrParam));
        
        // move onto the next parameter
        cParseIt.Next();
    }

    pContext->SetupRoutineCall(cCall);
*/
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

