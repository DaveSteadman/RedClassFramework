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

#include "RedCoreNamespace.h"

#include "RedToken.h"
#include "RedTokenBuffer.h"
#include "RedVSIParseTreeInterface.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseFactory
{
public:

    static RedVSIParseTreeInterface* ConstructAssignExpr        (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* ConstructStatementExpr     (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* ConstructValueExpr         (RedTokenBuffer& cInputBuffer, RedLog& log);

protected:

    static RedVSIParseTreeInterface* RunExprAssignCompetition   (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunCompareExprCompetition  (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunLogicExprCompetition    (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunSumExprCompetition      (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunMultiExprCompetition    (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunPowExprCompetition      (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunItemExprCompetition     (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunUnaryExprCompetition    (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunSubExprCompetition      (RedTokenBuffer& cInputBuffer, RedLog& log);    
    static RedVSIParseTreeInterface* RunValueCompetition        (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunVariableCompetition     (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunExternalCallCompetition (RedTokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunInternalCallCompetition (RedTokenBuffer& cInputBuffer, RedLog& log);

    static bool                      IsValueToken(const RedToken& cTok);
    static bool                      IsVariableToken(const RedToken& cTok);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

