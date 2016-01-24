
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIParseTreeInterface.h"
#include "RedVSITokenElementMap.h"
#include "RedVSITokenBuffer.h"

#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeUnaryOp.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeVar.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSIParseSerialiser
{
public:

	static void SerialiseExpression(RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeInterface* pExpr);

private:

	static void SerialiseBinaryOp (RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeBinaryOp* pExpr);
	static void SerialiseUnaryOp  (RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeUnaryOp* pExpr);
	static void SerialiseValue    (RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeVal* pExpr);
	static void SerialiseVariable (RedVSITokenBuffer& cTokenBuffer, RedVSIParseTreeVar* pExpr);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

