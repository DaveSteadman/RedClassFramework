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

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIToken.h"
#include "RedVSITokenBuffer.h"
#include "RedVSIParseTreeInterface.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseFactory
{
public:

    static RedVSIParseTreeInterface* ConstructAssignExpr        (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* ConstructStatementExpr     (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* ConstructValueExpr         (RedVSITokenBuffer& cInputBuffer, RedLog& log);

protected:

    static RedVSIParseTreeInterface* RunExprAssignCompetition   (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunCompareExprCompetition  (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunLogicExprCompetition    (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunSumExprCompetition      (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunMultiExprCompetition    (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunPowExprCompetition      (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunItemExprCompetition     (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunUnaryExprCompetition    (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunSubExprCompetition      (RedVSITokenBuffer& cInputBuffer, RedLog& log);    
    static RedVSIParseTreeInterface* RunValueCompetition        (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunVariableCompetition     (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunExternalCallCompetition (RedVSITokenBuffer& cInputBuffer, RedLog& log);
    static RedVSIParseTreeInterface* RunInternalCallCompetition (RedVSITokenBuffer& cInputBuffer, RedLog& log);

    static int                  IsValueToken(RedVSIToken cTok);
    static int                  IsVariableToken(RedVSIToken cTok);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

