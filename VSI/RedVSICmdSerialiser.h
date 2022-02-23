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

#include "RedCoreNamespace.h"

#include "RedVSICmdInterface.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdLet.h"
#include "RedVSICmdLog.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdWhile.h"
#include "RedVSITokenBuffer.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdSerialiser
{
public:
    static void SerialiseCommandChain(RedVSITokenBuffer& cTokenBuffer, RedVSICmdInterface* pCmd);
    static void TokenBufferToOutputBuffer(RedVSITokenBuffer& cInTokenBuffer, RedVSITokenElementMap& tokenMap, RedBufferOutput& outBuffer);

private:
    static void SerialiseIfCmd      (RedVSITokenBuffer& cTokenBuffer, RedVSICmdIf*     pCmd);
    static void SerialiseLetCmd     (RedVSITokenBuffer& cTokenBuffer, RedVSICmdLet*    pCmd);
    static void SerialiseLogCmd     (RedVSITokenBuffer& cTokenBuffer, RedVSICmdLog*    pCmd);
    static void SerialiseNewCmd     (RedVSITokenBuffer& cTokenBuffer, RedVSICmdNew*    pCmd);
    static void SerialiseReturnCmd  (RedVSITokenBuffer& cTokenBuffer, RedVSICmdReturn* pCmd);
    static void SerialiseWhileCmd   (RedVSITokenBuffer& cTokenBuffer, RedVSICmdWhile*  pCmd);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

