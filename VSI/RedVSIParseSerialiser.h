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

#include "RedVSIParseTreeInterface.h"
#include "RedTokenPredefMap.h"
#include "RedTokenBuffer.h"

#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeUnaryOp.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeVar.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseSerialiser
{
public:

    static void SerialiseExpression(RedTokenBuffer& cTokenBuffer, RedVSIParseTreeInterface* pExpr);

private:

    static void SerialiseBinaryOp (RedTokenBuffer& cTokenBuffer, RedVSIParseTreeBinaryOp* pExpr);
    static void SerialiseUnaryOp  (RedTokenBuffer& cTokenBuffer, RedVSIParseTreeUnaryOp* pExpr);
    static void SerialiseValue    (RedTokenBuffer& cTokenBuffer, RedVSIParseTreeVal* pExpr);
    static void SerialiseVariable (RedTokenBuffer& cTokenBuffer, RedVSIParseTreeVar* pExpr);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

