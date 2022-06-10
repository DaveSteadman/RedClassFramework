// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"

#include "RedTestCentre.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NextTarget:
// - Organise routine calls onto a stack and then unwind on returning from a call.
//      - Constrain to only single-threaded ideas until function calls are established/stable.
//
// - Run a pre-loaded function
//         lib add "c:\util\scratch\test.txt"
//
//      Creation of any thread places it in a list:
//          - Design statement that the threads/stacks are stored statically, like expressions.
//          - Place routine context in list. Then call base context to execute, not on the context itself.
// 
// 
// What do I want from a signature?
// - Create one during parse tree, got look up in the library. "Dynamic".
// - Library create one per routine for checking against, and debug output. "Static".
// - Compare Static and Dynamic signatures.
//      - Function and class names are simple enough.
//      - Checking List of parameters as types, vs name-type is the complexity.
// 
// Create one class for signatures, that can represent static, dynamic and perform all the comparisons.
// - Signatures will be created for routines as they enter the library.
// - Signatures will be able to create strong representations.
// 
// - Dynamic signature is the actual value, so the whole signature is the thing passed around for both 
//   finding the library function and setting up the new call.
// 
// 
// 
// Ideas:
// - RedDataVariant type reports the internal type, not the variant "container". 
//      - Maybe want to change that so actions like serialisation can correctly handle variants.
// - When an expression reaches an error, throw. Catch it at the command level that started the expression.
//      - Mop up anything about the expression, make sure an error message is logged. Move on.
// - DataString: Make the InsertAtIndex routines robust, and reuse then in all the append/prepend versions.
//      - Remove additional memory allocation calls.
// - Only value of a language is its interaction with its environment.
//      - e.g. Create a List object from files in a directory run "new heap list x = system::filelist('c:\', 'R')"
// - Atomic blocks:
//      - No yielding, to allow thread-safe operations. No loops allowed?
// 
// - Contexts
//      - LocalRoutine 
//          - Params, locals, return value
//          - Expression processing
//          - Command pointer
//      - Globals
//          - Heap 
//          - Routine stack
// 
//  Relegate the Thread to a struct within the Global? 
//      - How does a function call add to itself?
//          - Create the new context, add to itself, call current context blocked?
// 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// What is a Routine Signature?
// 
// Uses:
//      - Finding a routine in the library to call
//          - Checking if a routine exists before replacing it
//      - Listing the library contents
//      - ParseTreeCall loads up a Routine signature with objects and param-values, and says "call this".
//          - Dynamic use
//          - Does it need to exist? Can everything be setup dynamically?
// Looks Like:
// 
//      rettype ClassA::RoutineB(type, type, type)
//      ObjectA.RoutineB(varname, varname)
// 
// Can we:
// 
//      Have a single signature class to look-up and present?
//      Always list/find them based on the static lib view, massage the object view when needed.
// 
// What is a signature:
// 
//      We have the classes and routines as separate things.
//      - So the objects aren't maintained. Just create them and 
// 
//      Have a static version, then add the dynamic data to it for the run-time call?
// 
//      Compare types by strings, so we can include classnames in the future.
// 
// Solution:
//      Static:
//          - Class: 
//              Get list of static signatures
//              Does signature exist
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
