
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIToken.h"
#include "RedVSITokenBuffer.h"
#include "RedVSITokenElementMap.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

class RedVSITokenFactory
{
public:

    static int CreateTokens(const RedString& cInputText,  RedVSITokenElementMap& cTokenMap, RedVSITokenBuffer& cOutputTokenList);
    static int CreateTokens(RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSITokenBuffer& cOutputTokenList);

private:

    // Operations to construct a token from an unknown buffer input
    static RedResult RunTokenComp      (RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSIToken& cNewTok);

    static RedResult NumberComp        (RedBufferInput& cInputBuffer, RedVSIToken& cNewTok);
    static RedResult StringLiteralComp (RedBufferInput& cInputBuffer, RedVSIToken& cNewTok);
    static RedResult NonPrintableComp  (RedBufferInput& cInputBuffer, RedVSIToken& cNewTok);
    static RedResult NameComp          (RedBufferInput& cInputBuffer, RedVSIToken& cNewTok);
    static RedResult PredefinedComp    (RedBufferInput& cInputBuffer, RedVSITokenElementMap& cTokenMap, RedVSIToken& cNewTok);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
