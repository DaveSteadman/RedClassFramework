
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

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


