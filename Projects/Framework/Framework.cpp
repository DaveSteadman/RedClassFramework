// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"

#include "RedTestCentre.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NextTarget:
// - Load a code file into the library 
//
//         lib add "c:\util\scratch\test.txt"
//
// - Run a pre-loaded function
//
// Ideas:
// - Update number/string processing to simplify strings to/from numbers. static funcs etc.
//      - DataActions: Create a functional/utility class for addition routines and remove clutter from data classes?
// - RedDataVariant type reports the internal type, not the variant "container". 
//      - Maybe want to change that so actions like serialisation can correctly handle variants.
// - When an expression reaches an error, throw. Catch it at the command level that started the expression.
//      - Mop up anything about the expression, make sure an error message is logged. Move on.
// - DataString: Make the InsertAtIndex routines robust, and reuse then in all the append/prepend versions.
//      - Remove additional memory allocation calls.
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
        if (retstr.TextPtr() != NULL)
            std::cout << retstr.TextPtr();

        // End when shell done
        if (cVsiShell.RunState() == TEContextState::Ended)
            inputvalid = false;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
