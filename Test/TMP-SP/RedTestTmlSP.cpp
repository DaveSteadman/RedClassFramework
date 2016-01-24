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

//#include "RedTmlSpNamespace.h"

#include "RedTestTmlSP.h"

namespace Red {
namespace Test {

using namespace Red::Core;
//using namespace Red::TinyMLSP;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestTmlSP::RunUnitTest(void)
{
    //int TmlOnePassed          = RedTestTml::TestOne();
    //RedBoolean CorePassed         = RedTestCore::RunUnitTest();
    //RedBoolean MathPassed         = RedTestMath::RunUnitTest();

    return 0; //TmlOnePassed;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestTmlSP::TestOne(void)
{
//    RedString path  = "/tmp/Test.tml";
//    RedString path2 = "/tmp/Test2.tml";
//
//    RedTmlSpNode x("name");
//
//    RedTmlSpNode* y = x.CreateChildNode("childnode");
//
//    if (!y)
//        return 0;
//    
//    y->CreateChildLeaf("xyzname", "xyzdata");
//
//    RedBufferOutput oB;
//    RedTmlSpParser::SerialiseTinyML(oB, &x, eDenseContent);
//    RedIOHandler::OutputBufferToFile(path, oB);
//
//
//    RedBufferInput iB;
//    RedIOHandler::InputBufferFromFile(path, iB);
//    RedTmlSpElement* newX = RedTmlSpParser::ParseTinyML(iB);
//
//    if (!newX)
//        return 0;
//
//    RedBufferOutput oB2;
//    RedTmlSpParser::SerialiseTinyML(oB2, newX, eDenseContent);
//    RedIOHandler::OutputBufferToFile(path2, oB2);

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red