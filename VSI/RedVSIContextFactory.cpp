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

#include "RedVSIContextFactory.h"
//
#include "RedTokenFactory.h"
#include "RedVSILibRoutine.h"
#include "RedVSICmdFactory.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/*
RedResult RedVSIContextFactory::CreateContext(RedVSIContextRoutine** OutputContext, RedLog& cLog)
{
    // Turn the code into tokens
    //RedVSILibTokenMap cTokenMap;
    //RedTokenBuffer cTokenList;
    //if (!RedTokenFactory::CreateTokens(InputCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
    //    return kResultFail;

    /// Turn the tokens into code
    //RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cLog);
    //if (topCmd == NULL)
    //    return kResultFail;
    //if (cLog.IsError())
    //    return kResultFail;

    RedVSIContextBase    baseContext;
    RedVSIContextRoutine testContext(&baseContext);

    * OutputContext = new RedVSIContextRoutine(&cLog);

    if (*OutputContext == NULL)
        return kResultFail;

    return kResultSuccess;
}
*/

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
RedResult RedVSIContextFactory::LoadFragmentIntoContext(const RedDataString& InputCodeFragment, RedVSIContextRoutine& UpdateContext)
{
    // Turn the code into tokens
    RedTokenBuffer cTokenList;
    if (!RedTokenFactory::CreateTokens(InputCodeFragment, cTokenList))
        return kResultFail;

    RedLog* pLog = UpdateContext.Log();

    // Turn the tokens into code
    RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, *pLog);
    if (topCmd == NULL)
        return kResultFail;
    if (pLog->ContainsError())
        return kResultFail;

    UpdateContext.ClearCommandQueue();
    UpdateContext.QueueCommand(topCmd);

    return kResultSuccess;
}
*/
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//RedResult RedVSIContextFactory::CreateThreadContextForRoutine(const RedDataString& classname, const RedDataString& routinename, RedVSILib* pInputLib, RedVSIContextThread** OutputThreadContext, RedLog& cLog)
//{
//    // Find the routine to execute
//    RedVSILibRoutine* LibRoutine = pInputLib->FindRoutine(classname, routinename);
//
//    if (LibRoutine == NULL)
//        return kResultFail;
//
//    *OutputThreadContext = new RedVSIContextThread();
//
//    RedVSIContextRoutine* pFirstRoutineContext = new RedVSIContextRoutine(&cLog, classname, routinename, LibRoutine->FirstCommand());
//
//    pFirstRoutineContext->SetBaseContext(*OutputThreadContext);
//    (*OutputThreadContext)->PushRoutineOnStack(pFirstRoutineContext);
//    (*OutputThreadContext)->SetCodeLib(pInputLib);
//
//    return kResultSuccess;
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

