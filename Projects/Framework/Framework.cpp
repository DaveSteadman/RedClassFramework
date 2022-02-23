// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"
#include "RedTestCentre.h"

int main()
{
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Red::Core::RedLog cLog;
    Red::Test::RedTestCentre::RunAllUnitTests(cLog);
    std::cout << cLog.AllLoggedText().TextPtr();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    Red::Core::RedString cTestString = "Red Framework";

    Red::Core::RedChar cTestCh = cTestString[2];
    cTestString.SetCharAtIndex(2, 'e');

    Red::Core::RedTinyMLNode cRootNode("root");
    cRootNode.CreateChildNode("OptA");

    Red::Core::RedBufferOutput outputBuf;
    RedTinyMLFileIO::SerialiseCore(outputBuf, &cRootNode, eLinedIndentedContent);

    std::cout << "Hello " << cTestString.TextPtr() << "!\n" << outputBuf.ExtractData().TextPtr();
}