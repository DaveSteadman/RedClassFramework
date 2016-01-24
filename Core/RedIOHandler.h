
#pragma once 

#include "RedString.h"
#include "RedResult.h"
#include "RedBufferInput.h"
#include "RedBufferOutput.h"

namespace Red {
namespace Core {
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    class RedIOHandler
    {
    public:
        static RedResult FileExists(const RedString& filepath);

        static RedResult InputBufferFromFile(const RedString& cFilepath, RedBufferInput& cBuf);
        static RedResult OutputBufferToFile (const RedString& cFilepath, RedBufferOutput& cBuf);
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    
} // Core
} // Red


