// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"

#include "RedTestCentre.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NextTask:
// - Get the Token reading improved 
//      - Fix the strings for simplicity.
//      - Test reading tokens.
//      - Check the memory leaks when exiting a read-token routine.
// 
//      - Elevate the token from RedToken to RedToken, to cover all the uses (TinyML etc).
//      - Reads everything as its own thing - names, symbols, numbers etc. Then predef as an independent follow-up stage.
// 
// - Swap NULL for C++ nullptr keyword
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main()
{
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    std::cout << "- Built In Test - - - - - - - - - - - - - - - \n";
    Red::Core::RedLog cLog;
    Red::Test::RedTestCentre::RunAllUnitTests(cLog);
    std::cout << cLog.AllLoggedText().TextPtr();

    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - \n";
    std::cout << "Red Shell\n";

    char inputline[256];

    Red::VSI::RedVSIShell cVsiShell;
    Red::Core::RedDataString retstr;

    bool inputvalid = true;
    while (inputvalid)
    {
        // Initialise and get line
        for (int i = 0; i < 256; i++) inputline[i] = '\0';
        std::cout << ":>";
        std::cin.getline(inputline, 256);

        // Run Command and output results
        retstr = cVsiShell.ProcessCmdLine(RedDataString(inputline));
        std::cout << retstr.TextPtr();

        // End when shell done
        if (cVsiShell.RunState() == TEContextState::Ended)
            inputvalid = false;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
