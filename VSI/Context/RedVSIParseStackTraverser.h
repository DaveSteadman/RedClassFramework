
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIParseStack.h"
#include "RedVSIParseTreeInterface.h"
#include "RedLog.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseStackTraverser
{
public:
	static void PopulateStack(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log);

private:
	static void AddBinaryOp(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log);
	static void AddVariable(RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log);    
	static void AddValue   (RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log);
	static void AddCall    (RedVSIParseStack& cStack, RedVSIParseTreeInterface* pExpr, RedLog& log);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

