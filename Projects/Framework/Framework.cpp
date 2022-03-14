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

    Red::Core::RedDataString cTestString = "Red Framework";

    Red::Core::RedDataChar cTestCh = cTestString[2];
    cTestString.SetCharAtIndex(2, 'e');

    Red::Core::RedTinyMLNode cRootNode("root");
    cRootNode.CreateChildNode("OptA");

    Red::Core::RedBufferOutput outputBuf;
    RedTinyMLFileIO::SerialiseCore(outputBuf, &cRootNode, TESerialiseType::LinedIndentedContent);

    std::cout << "Hello " << cTestString.TextPtr() << "!\n" << outputBuf.ExtractData().TextPtr();


    char inputline[256];
    bool inputvalid = true;

    Red::VSI::RedVSIShell cVsiShell;

    std::cout << "\n";
    while (inputvalid)
    {
        for (int i = 0; i < 256; i++) inputline[i] = '\0';
        std::cout << ":>";
        std::cin.getline(inputline, 256);

        cVsiShell.ProcessCmdLine(RedDataString(inputline));

        if (cVsiShell.eState == TEShellState::Ended)
            inputvalid = false;
    }

}