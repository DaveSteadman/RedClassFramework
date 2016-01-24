
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSICmdInterface.h"
#include "RedVSITokenBuffer.h"
#include "RedVSICmdExpr.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdWhile.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdSerialiser
{
public:
	static void SerialiseCommandChain(RedVSITokenBuffer& cTokenBuffer, RedVSICmdInterface* pCmd);
    static void TokenBufferToOutputBuffer(RedVSITokenBuffer& cInTokenBuffer, RedVSITokenElementMap& tokenMap, RedBufferOutput& outBuffer);

private:
	static void SerialiseExprCmd    (RedVSITokenBuffer& cTokenBuffer, RedVSICmdExpr* pCmd);
	static void SerialiseNewCmd     (RedVSITokenBuffer& cTokenBuffer, RedVSICmdNew* pCmd);
	static void SerialiseReturnCmd  (RedVSITokenBuffer& cTokenBuffer, RedVSICmdReturn* pCmd);
	static void SerialiseIfCmd      (RedVSITokenBuffer& cTokenBuffer, RedVSICmdIf* pCmd);
	static void SerialiseWhileCmd   (RedVSITokenBuffer& cTokenBuffer, RedVSICmdWhile* pCmd);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

