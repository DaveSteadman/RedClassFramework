// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#pragma once

#include "RedCoreNamespace.h"
#include "RedVSINamespace.h"

#include "RedVSIShell.h"

using namespace Red::Core;
using namespace Red::VSI;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSIShell::ProcessCmdLine(RedDataString inputstr)
{
    RedDataString retStr = "";

    // Parse line
    // lib load <path>
    // lib list <classname>
    // lib clear <classname>
    // log list
    // log clear
    // run <routine sig>
    // heap list
    // heap clear <name>
    // heap add <type> <name> = <val>
    // runfrag <code fragment>
    // init

    RedVSITokenBuffer cInputBuffer;
    RedVSILibTokenMap map;

    int iCreateResult = RedVSITokenFactory::CreateTokens(inputstr, map.cVSILibTokenMap, cInputBuffer);


    retStr = "command processed.\n";
    return retStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibAddComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{

    RedDataString filepath = "";

    if (!RedIOHandler::FileExists(filepath))
        return false;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibInitComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{

    eCodeLib.Init();

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibListComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{

    RedDataList cList = eCodeLib.ClassNameList();

    unsigned listcount = cList.NumItems();

    for (unsigned i = 0; i < listcount; i++)
    {
        RedDataString* x;
        x = dynamic_cast<RedDataString*>(cList.PtrForIndex(i));


        retstr += *x;
        retstr += "\n";
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataAddComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataInitComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataListComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::RunFragComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::RunFuncComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::ExitComp(RedDataString& retstr, RedVSITokenBuffer& cInputBuffer)
{
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
