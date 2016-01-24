
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSITokenBuffer.h"
#include "RedVSIParseTreeInterface.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

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

