

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