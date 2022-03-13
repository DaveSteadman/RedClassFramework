// RedConsoleApp2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"
#include "RedTestCentre.h"

using namespace Red::Core;
using namespace Red::VSI;
using namespace Red::Test;

int main()
{
    std::cout << "Hello World!\n";

    RedLog cLog;
    RedTestCentre::RunAllUnitTests(cLog);
    std::cout << cLog.AllLoggedText().TextPtr();
    if (cLog.ContainsError())
        std::cout << "ERROR\n";

    bool bLoopValid = true;
    RedVSIShell cRedShell;
    while (cRedShell.eState != TEShellState::Ended)
    {
        char line[255];
        for (unsigned i = 0; i < 255; i++) line[i] = '\0';
        
        std::cout << ":>";
        std::cin.getline(line, 255);

        RedDataString retstr = cRedShell.ProcessCmdLine(RedDataString(line));
        std::cout << retstr.TextPtr();
    }

    return 0;
}

