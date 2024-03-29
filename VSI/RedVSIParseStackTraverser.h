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

#include "RedVSICollections.h"
#include "RedVSIParseTreeInterface.h"
#include "RedLog.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class to convert a parse-tree structure into a stack we can execute in the correct order to satisfy
// the dependent results for each node.
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

