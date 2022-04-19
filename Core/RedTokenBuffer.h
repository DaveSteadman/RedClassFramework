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

#include "RedToken.h"
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTokenBuffer
{
public:

    typedef RedDoubleLinkedList<RedToken>          ListType;
    typedef RedDoubleLinkedListIterator<RedToken>  IteratorType;

    RedTokenBuffer(void) { Init(); };
    ~RedTokenBuffer();

    void    Init(void);
    
    void    AppendToken(const RedToken& cNewTok);

    IteratorType GetIterator(void) { IteratorType cIt(&cTokenList); return cIt; };

    // all depricated on creation of iterator
    RedToken GetToken(void);
    RedToken GetToken(const unsigned iTokenIndex);

    void        SetTokenIndex(const unsigned iTokenIndex) { iCurrListIndex = iTokenIndex; };
    unsigned    GetTokenIndex(void)        { return iCurrListIndex; };
    void        SetTokenIndexBackOne(void) { if (iCurrListIndex>0) iCurrListIndex--; };

    bool        CurrIndexAtLastToken(void) { return (iCurrListIndex == cTokenList.NumItems()); };

    unsigned    NumTokens(void) { return cTokenList.NumItems(); };

    RedDataString   DebugDump(void);

private:

    ListType      cTokenList;
    unsigned      iCurrListIndex;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
