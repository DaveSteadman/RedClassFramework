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

RedResult RedVSIContextFactory::LoadFragmentIntoContext (const RedString& InputCodeFragment, RedVSIContextFragment* UpdateContext, RedLog& cLog)
{
    if (UpdateContext == REDNULL)
        return kResultFail;

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

    UpdateContext->ClearCommandQueue();
    UpdateContext->QueueCommand(topCmd);

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedVSIContextFactory::CreateThreadContextForRoutine(const RedString& classname, const RedString& routinename, RedVSILibInterface* pInputLib, RedVSIContextThread** OutputThreadContext, RedLog& cLog)
{
    // Find the routine to execute
    RedVSILibRoutineInterface* LibRoutine = pInputLib->FindRoutine(classname, routinename);

    if (LibRoutine == REDNULL)
        return kResultFail;

    *OutputThreadContext = new RedVSIContextThread();

    RedVSIContextRoutine* pFirstRoutineContext = new RedVSIContextRoutine(classname, routinename, LibRoutine->FirstCommand(), cLog);

    pFirstRoutineContext->SetThreadContextRecord(*OutputThreadContext);
    (*OutputThreadContext)->PushRoutineOnStack(pFirstRoutineContext);
    (*OutputThreadContext)->SetCodeLib(pInputLib);

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

