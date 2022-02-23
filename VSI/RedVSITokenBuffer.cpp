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

#include "RedVSITokenBuffer.h"
#include "RedVSILibTokenMap.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSITokenBuffer::Init(void)
{
    cTokenList.DelAll();
    iCurrListIndex = cTokenList.FirstIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSITokenBuffer::AppendToken(const RedVSIToken& cNewTok)
{
    cTokenList.AddLast(cNewTok);
    iCurrListIndex = cTokenList.FirstIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIToken RedVSITokenBuffer::GetToken(void)
{
    RedVSIToken         cCurrTok;
    RedVSIToken         cRetTok;

    // check we can get the token
    if (cTokenList.FindElementAtIndex(iCurrListIndex, cRetTok))
        iCurrListIndex++;
    else
        cRetTok.SetNonPrintable(RedChar('\0'));

    return cRetTok;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIToken RedVSITokenBuffer::GetToken(const unsigned iTokenIndex)
{
    RedVSIToken cRetTok;

    // check we can get the token
    if (!cTokenList.FindElementAtIndex(iTokenIndex, cRetTok))
        cRetTok.Init();

    return cRetTok;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedVSITokenBuffer::DebugDump(void)
{
    RedString         RetStr;
    RedVSILibTokenMap map;

    IteratorType cIt = GetIterator();
    cIt.First();

    while (!cIt.IsDone())
    {
        RedVSIToken currToken = cIt.CurrentItem();
        RetStr += currToken.DebugText(map.cVSILibTokenMap);
        cIt.Next();
    }

    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


