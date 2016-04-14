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

#include "RedVSIContextFactory.h"
//
#include "RedVSILibTokenMap.h"
#include "RedVSITokenFactory.h"
#include "RedVSICmdFactory.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSIContextFactory::CreateContextForFragment(const RedString& InputCodeFragment, RedVSIContextFragment** OutputContext, RedLog& cLog)
{
    // Turn the code into tokens
    RedVSILibTokenMap cTokenMap;
    RedVSITokenBuffer cTokenList;
    RedLog            cRedLog;
    if (!RedVSITokenFactory::CreateTokens(InputCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
        return kResultFail;

    // Turn the tokens into code
    RedVSICmdInterface* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
    if (topCmd == REDNULL)
        return kResultFail;
    if (cRedLog.IsError())
        return kResultFail;

    *OutputContext = new RedVSIContextFragment(cRedLog, topCmd);

    if (*OutputContext == REDNULL)
        return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSIContextFactory::CreateRoutineContextForRoutine(const RedString& ClassName, const RedString& RoutineName, RedVSIContextRoutine** OutputContext, RedLog& cLog)
{
//    RedVSILibRoutineInterface* LibRoutine = lib.FindRoutine(ClassName, RoutineName);
//
//    RedLog            cRedLog;
//
//    *OutputContext = new RedVSIContextRoutine(cRedLog, LibRoutine->FirstCommand());
//
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSIContextFactory::CreateThreadContextForRoutine(RedVSILibRoutineInterface& cInputRoutineCall, RedVSILibInterface* pInputLib, RedVSIContextThread** OutputContext, RedLog& cLog)
{
    // Find the routine to execute
//    pInputLib->FindRoutine(pInputLib);

    return kResultSuccess;
}

//RedVSIContextRoutine* RedVSIContextFactory::CreateRoutineContext(RedVSILibRoutineInterface& cRoutineCall, RedVSILibRoutineInterface* pRoutineLib, CDataObject* pThisObj)
//{
//    RedVSIContextRoutine* pNewRoutine = new RedVSIContextRoutine();
//
//    // Assign the routine name details to the context
//    pNewRoutine->SetNameDetails(cRoutineCall.GetObjectName(), cRoutineCall.GetClassName(), cRoutineCall.GetFuncName());
//
//    // Setup the core elements of the routine
//    pNewRoutine->SetThisObj(pThisObj);
//    pNewRoutine->QueueCommand(pRoutineLib->GetCode());
//
//    // Loop through the parameters
//    RedVSIVariantListIterator cCallParamsIt(cRoutineCall.GetParams());
//    RedVSIStringStringTypeMapIterator cRoutineParamsIt(pRoutineLib->GetParams());
//    cCallParamsIt.First();
//    cRoutineParamsIt.First();
//
//    while ( (!cCallParamsIt.IsDone()) && (!cRoutineParamsIt.IsDone()) )
//    {
//        // get the data out of the lists to create the new data items
//        RedString  cName = cRoutineParamsIt.CurrentId();
//        RedVariant cData = cCallParamsIt.CurrentItem();
//        
//        pNewRoutine->AddParam(cName, cData.GetValue());
//
//        // move the list items on.
//        cCallParamsIt.Next();
//        cRoutineParamsIt.Next();
//    }
//
//    return pNewRoutine;  
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

