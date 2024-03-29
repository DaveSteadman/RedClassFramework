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

#include "RedDataString.h"
#include "RedBufferInput.h"
#include "RedResult.h"
#include "RedToken.h"
#include "RedTokenBuffer.h"

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

class RedTokenFactory
{
public:

    static bool CreateTokens(const RedDataString& cInputText, RedTokenBuffer& cOutputTokenList);
    static bool CreateTokens(RedBufferInput& cInputBuffer,  RedTokenBuffer& cOutputTokenList);

private:

    // Operations to construct a token from an unknown buffer input
    static RedResult RunTokenComp      (RedBufferInput& cInputBuffer, RedToken& cNewTok);

    static RedResult NumberComp        (RedBufferInput& cInputBuffer, RedToken& cNewTok);
    static RedResult StringLiteralComp (RedBufferInput& cInputBuffer, RedToken& cNewTok);
    static RedResult NonPrintableComp  (RedBufferInput& cInputBuffer, RedToken& cNewTok);
    static RedResult NameComp          (RedBufferInput& cInputBuffer, RedToken& cNewTok);
    static RedResult SymbolComp        (RedBufferInput& cInputBuffer, RedToken& cNewTok);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
