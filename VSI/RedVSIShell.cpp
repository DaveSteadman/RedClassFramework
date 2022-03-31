// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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
    // lib init
    // lib add <path>
    // lib list <classname>
    // 
    // log init
    // log list
    // 
    // run <routine sig>
    // heap list
    // heap clear <name>
    // heap add <type> <name> = <val>
    // runfrag <code fragment>
    // init

    RedVSITokenBuffer cInputBuffer;
    RedVSILibTokenMap map;

    int iCreateResult = RedVSITokenFactory::CreateTokens(inputstr, map.cVSILibTokenMap, cInputBuffer);

    RedLog cLog;
    if      (ExitComp(cInputBuffer, cLog))     retStr = cLog.AllLoggedText();
    else if (DataAddComp(cInputBuffer, cLog))  retStr = cLog.AllLoggedText();
    else if (DataInitComp(cInputBuffer, cLog)) retStr = cLog.AllLoggedText();
    else if (DataListComp(cInputBuffer, cLog)) retStr = cLog.AllLoggedText();
    else if (RunFragComp(cInputBuffer, cLog))  retStr = cLog.AllLoggedText();
    else if (cInputBuffer.NumTokens() > 0)     retStr = "Command Not Found\n";
    else                                       retStr = "";

    return retStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibAddComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{

    RedDataString filepath = "";

    if (!RedIOHandler::FileExists(filepath))
        return false;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibInitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{

    cVSIBase.cCodeLib.Init();

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibListComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedDataList cList = cVSIBase.cCodeLib.ClassNameList();

    unsigned listcount = cList.NumItems();

    RedDataString retstr;
    for (unsigned i = 0; i < listcount; i++)
    {
        RedDataString* x;
        x = dynamic_cast<RedDataString*>(cList.PtrForIndex(i));


        retstr += *x;
        retstr += "\n";
    }
    cLog.AddText(retstr);

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataAddComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok = cInputBuffer.GetToken();
    RedVSIToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellData() &&
        cCmd2Tok.Predef().IsKeywordShellAdd())
    {
        cLog.AddText("DataAdd Command Processed.");

        cVSIBase.cHeap.AddByValue("var1", 1);
        cVSIBase.cHeap.AddByValue("var2", 1.234);
        cVSIBase.cHeap.AddByValue("var3", "data");

        return true;
    }

    // not data init command, return the token and fail the comp.
    cInputBuffer.SetTokenIndexBackOne();
    cInputBuffer.SetTokenIndexBackOne();
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataInitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok  = cInputBuffer.GetToken();
    RedVSIToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellData() && 
        cCmd2Tok.Predef().IsKeywordShellInit() )
    {
        cLog.AddText("DataInit Command Processed.");

        return true;
    }

    // not data init command, return the token and fail the comp.
    cInputBuffer.SetTokenIndexBackOne();
    cInputBuffer.SetTokenIndexBackOne();
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataListComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok = cInputBuffer.GetToken();
    RedVSIToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellData() && cCmd2Tok.Predef().IsKeywordShellList())
    {
        cLog.AddText("DataList Command Processed.");

        unsigned NumElems = cVSIBase.cHeap.NumItems();

        RedDataString cDataList;
        cDataList = "Num Elements: ";
        cDataList.Append(RedDataNumber(NumElems).DecimalString());
        cLog.AddText(cDataList);

        RedDataString cDataLine;
        for (unsigned i = 0; i < NumElems; i++)
        {
            RedType* pData = cVSIBase.cHeap.PtrForIndex(i);

            cDataLine = "heap ";
            cDataLine.Append(pData->Type().Name());
            cDataLine += " ";
            cDataLine.Append(cVSIBase.cHeap.NameForIndex(i));

            cDataLine += " = ";
            RedDataVariant x(*pData);
            cDataLine += x.StringValue();

            cLog.AddText(cDataLine);
        }
        return true;
    }

    // not data init command, return the token and fail the comp.
    cInputBuffer.SetTokenIndexBackOne();
    cInputBuffer.SetTokenIndexBackOne();
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::RunFragComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok  = cInputBuffer.GetToken();
    RedVSIToken cCodeTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellRun() && 
        cCodeTok.Type().IsStringLiteral())
    {
        RedVSILibTokenMap cTokenMap;
        RedVSITokenBuffer cTokenList;
        RedDataString strCodeFragment = cCodeTok.Text();
        if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
            return true;

        // - - - From this point on we need to delete the created elements - - - - - -

        // Turn the tokens into code
        RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cLog);
        if (topCmd == NULL)
        {
            cLog.AddErrorEvent("Code construction competition failed.\n");
            return true;
        }
        if (cLog.ContainsError())
        {
            cLog.AddErrorEvent("Error detected post-Code construction competition.\n");
            delete topCmd;
            return true;
        }

        // Execute the code in a context
        RedVSIContextRoutine testContext(&cLog, topCmd);
        testContext.Execute(10);
        if (cLog.ContainsError())
        {
            cLog.AddErrorEvent("Code execution error.\n");
        }
        delete topCmd;
        return true;
    }

    // not data init command, return the token and fail the comp.
    cInputBuffer.SetTokenIndexBackOne();
    cInputBuffer.SetTokenIndexBackOne();
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::RunFuncComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellRun())
    {

    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::ExitComp(RedVSITokenBuffer& cInputBuffer, RedLog& cLog)
{
    RedVSIToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordShellExit())
    {
        cVSIBase.eState = TEContextState::Ended;
        cLog.AddText("Exit Command Processed.");
        return true;
    }

    // not exit command, return the token and fail the comp.
    cInputBuffer.SetTokenIndexBackOne();
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
