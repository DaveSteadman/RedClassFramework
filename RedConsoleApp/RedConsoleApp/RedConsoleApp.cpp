// RedConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "RedTestCentre.h"
#include "RedVSINamespace.h"

using namespace Red::Core;
using namespace Red::Test;
using namespace Red::VSI;

int main()
{
    std::cout << "Hello World!\n";

    // Run std testing
    Red::Core::RedLog testlog;
    RedTestCentre::RunAllUnitTests(testlog);
    std::cout << testlog.AllLoggedText().TextPtr();

    RedLog                 cRedLog;
    RedVSIContextRoutine testContext(&cRedLog);

    //RedVSIContextFactory::CreateContext(testContext, cRedLog);


    while (1)
    {
        // Read the next line
        std::cout << "\n>";
        std::string line;
        std::getline(std::cin, line);
        RedString rline = line.c_str();

        // Execute the code in a context, while we have no completion and no error
        RedVSIContextFactory::LoadFragmentIntoContext(rline, testContext); // <- not preserving context between commands.
        while ((!testContext.IsExecutionComplete()) && (!cRedLog.IsError()))
            testContext.Execute(1);

        if (cRedLog.IsError())
            std::cout << cRedLog.AllLoggedText().TextPtr();

    }
}
