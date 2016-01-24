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

RedVSIToken RedVSITokenBuffer::GetToken(int iTokenIndex)
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
        RetStr += currToken.GetDebugText(map.cVSILibTokenMap);
        cIt.Next();
    }

    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


