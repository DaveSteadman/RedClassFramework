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

#include "RedTokenBuffer.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTokenBuffer::~RedTokenBuffer()
{
    Init();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTokenBuffer::Init(void)
{
    cTokenList.DelAll();
    iCurrListIndex = cTokenList.FirstIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTokenBuffer::AppendToken(const RedToken& cNewTok)
{
    cTokenList.AddLast(cNewTok);
    iCurrListIndex = cTokenList.FirstIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedToken RedTokenBuffer::GetToken(void)
{
    RedToken         cCurrTok;
    RedToken         cRetTok;

    // check we can get the token
    if (cTokenList.FindElementAtIndex(iCurrListIndex, cRetTok))
        iCurrListIndex++;
    else
        cRetTok.SetNonPrintable(RedDataChar('\0'));

    return cRetTok;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedToken RedTokenBuffer::GetToken(const unsigned iTokenIndex)
{
    RedToken cRetTok;

    // check we can get the token
    if (!cTokenList.FindElementAtIndex(iTokenIndex, cRetTok))
        cRetTok.Init();

    return cRetTok;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedTokenBuffer::DebugDump(void)
{
    RedDataString RetStr;

    IteratorType cIt = GetIterator();
    cIt.First();

    while (!cIt.IsDone())
    {
        RedToken currToken = cIt.CurrentItem();
        RetStr += currToken.DebugText();
        cIt.Next();
    }

    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


