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

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "RedIOHandler.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedIOHandler::FileExists(const RedString& filepath)
{
    if (FILE * file = fopen(filepath.TextPtr(), "r"))
    {
        fclose(file);
        return kResultSuccess;
    }
    return kResultFail;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedIOHandler::InputBufferFromFile(const RedString& cFilepath, RedBufferInput& cBuf)
{
    // open the file, returning fail if required
    FILE* pFile = fopen (cFilepath.TextPtr(),"r");
    if (pFile == 0)
        return kResultFail;

    // create and/or initialise the variables to read the data
    RedString cData;
    int c;

    // loop, read each character until we run out of file
    while ( (c=fgetc(pFile)) != EOF )
          cData += c;

    fclose(pFile);

    cBuf.Assign(cData);

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedIOHandler::OutputBufferToFile(const RedString& cFilepath, RedBufferOutput& cBuf)
{
    // open the file, returning fail if required
    FILE* pFile = fopen (cFilepath.TextPtr(),"w");
    if (pFile == 0)
    {
        return kResultFail;
    }

    RedString strBuf = cBuf.ExtractData();
    int iLen = strBuf.Length();
    
    for (int i=0; i<iLen; i++)
    {
        int iChar = (int)strBuf.CharAtPos(i);
        fputc(iChar, pFile);
    }
    
    fclose(pFile);

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


