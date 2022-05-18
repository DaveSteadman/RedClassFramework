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
#include "RedTinyMLFileIO.h"

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

    RedTokenBuffer cInputBuffer;

    int iCreateResult = RedTokenFactory::CreateTokens(inputstr, cInputBuffer);

    cVSIBase.cLog.Init();

    if (BlankLineComp(cInputBuffer))
    {
        retStr = "";
    }
    else
    {
        if      (ExitComp(cInputBuffer))     retStr = cVSIBase.cLog.AllLoggedText();
        else if (DataAddComp(cInputBuffer))  retStr = cVSIBase.cLog.AllLoggedText();
        else if (DataInitComp(cInputBuffer)) retStr = cVSIBase.cLog.AllLoggedText();
        else if (DataListComp(cInputBuffer)) retStr = cVSIBase.cLog.AllLoggedText();
        else if (RunFragComp(cInputBuffer))  retStr = cVSIBase.cLog.AllLoggedText();
        else if (HelpComp(cInputBuffer))     retStr = cVSIBase.cLog.AllLoggedText();
        else if (LibAddComp(cInputBuffer))   retStr = cVSIBase.cLog.AllLoggedText();
        else if (LibListComp(cInputBuffer))  retStr = cVSIBase.cLog.AllLoggedText();
        else                                 retStr = "Command not found.\n";
    }
    return retStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::BlankLineComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.IsEOF())
    {
        return true;
    }
    else
    {
        // Not the EOF keyword, put the token back.
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

bool RedVSIShell::HelpComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordHelp())
    {
        cVSIBase.cLog.AddText(":>data list - List items in the heap.");
        cVSIBase.cLog.AddText(":>exit - End program.");
        cVSIBase.cLog.AddText(":>help - List all shell commands.");
        cVSIBase.cLog.AddText(":>lib add <filepath> - Add new class to code library.");
        cVSIBase.cLog.AddText(":>lib list - Show contents of code libary.");
        cVSIBase.cLog.AddText(":>run \"new heap number x = 1\" - Run a VSI code fragment.");

        return true;
    }
    else
    {
        // Not the help keyword, put the token back.
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibAddComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCmd2Tok = cInputBuffer.GetToken();

    if (!cCmdTok.Predef().IsKeywordLib() || !cCmd2Tok.Predef().IsKeywordAdd())
    {
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
        return false;
    }
    cVSIBase.cLog.AddText("LibAdd Shell Command Processed.");

    RedToken cFilePathTok = cInputBuffer.GetToken();
    RedDataString filepathStr = cFilePathTok.Text();
    if (!cFilePathTok.Type().IsStringLiteral())
    {
        RedDataString cErrStr = "String literal token for filepath not found with token: ";
        cErrStr += filepathStr;
        cVSIBase.cLog.AddErrorEvent(cErrStr);
        return true;
    }

    if (!RedIOHandler::FileExists(filepathStr))
    {
        RedDataString cErrStr = "Could not find filepath with token: ";
        cErrStr += filepathStr;
        cVSIBase.cLog.AddErrorEvent(cErrStr);
        return true;
    }

    // --- 
    // Have a path to a known file. open it and import.

    RedTinyMLElement* pTopTinyMLElem = RedTinyMLFileIO::CreateTinyMLFromFile(filepathStr);

    if (pTopTinyMLElem == NULL)
    {
        RedDataString cErrStr = "Unable to create basic TinyML structure from file: ";
        cErrStr += filepathStr;
        cVSIBase.cLog.AddErrorEvent(cErrStr);
        return true;
    }

    RedVSILibFactory vsiCodeLibFactory(&cVSIBase.cCodeLib);

    vsiCodeLibFactory.InputTmlClass(pTopTinyMLElem, cVSIBase.cLog);

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibInitComp(RedTokenBuffer& cInputBuffer)
{

    cVSIBase.cCodeLib.Init();

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::LibListComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordLib() && cCmd2Tok.Predef().IsKeywordList())
    {
        cVSIBase.cLog.AddText("LibList Shell Command Processed.");

        RedDataList cList;

        //cVSIBase.cCodeLib.ListClassNames(cList);

        unsigned listcount = cList.NumItems();

        RedDataString retstr;
        //RedDataNumber numClasses(listcount);

        //retstr = "NumClasses: " + RedDataActions::StringFromNumber(numClasses);
        //cVSIBase.cLog.AddText(retstr);

        //retstr = "";
        //for (unsigned i = 0; i < listcount; i++)
        //{
        //    RedDataString* x;
        //    x = dynamic_cast<RedDataString*>(cList.PtrForIndex(i));

        //    retstr += *x;
        //    retstr += "\n";
        //}
        //cVSIBase.cLog.AddText(retstr);


        cVSIBase.cCodeLib.RoutineSigList(cList);
        listcount = cList.NumItems();
        retstr = "";
        for (unsigned i = 0; i < listcount; i++)
        {
            RedDataString* x;
            x = dynamic_cast<RedDataString*>(cList.PtrForIndex(i));

            retstr += *x;
            retstr += "\n";
        }
        cVSIBase.cLog.AddText(retstr);

        return true;
    }
    else
    {
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataAddComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordData() &&  cCmd2Tok.Predef().IsKeywordAdd())
    {
        cVSIBase.cLog.AddText("DataAdd Command Processed.");

        cVSIBase.cHeap.AddByValue("var1", 1);
        cVSIBase.cHeap.AddByValue("var2", 1.234);
        cVSIBase.cHeap.AddByValue("var3", "data");

        return true;
    }
    else
    {
        // not data init command, return the token and fail the comp.
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataInitComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordData() && 
        cCmd2Tok.Predef().IsKeywordInit() )
    {
        cVSIBase.cLog.AddText("DataInit Command Processed.");

        return true;
    }
    else
    {
        // not data init command, return the token and fail the comp.
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::DataListComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCmd2Tok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordData() && cCmd2Tok.Predef().IsKeywordList())
    {
        cVSIBase.cLog.AddText("DataList Command Processed.");

        unsigned NumElems = cVSIBase.cHeap.NumItems();

        cVSIBase.cLog.AddText("Num Elements: " + RedDataActions::StringFromInt(NumElems));

        RedDataString cDataLine;
        for (unsigned i = 0; i < NumElems; i++)
        {
            RedData* pData = cVSIBase.cHeap.PtrForIndex(i);

            cDataLine = kIOStringKeywordHeap;
            cDataLine += " ";
            cDataLine.Append(pData->Type().Name());
            cDataLine += " ";
            cDataLine.Append(cVSIBase.cHeap.NameForIndex(i));

            cDataLine += " = ";
            RedDataVariant x(*pData);
            cDataLine += x.StringValue();

            cVSIBase.cLog.AddText(cDataLine);
        }
        return true;
    }
    else
    {
        // not data init command, return the token and fail the comp.
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// run "new heap number x = 1"
// run "if x == 1 then new heap number y = 2 endif"

bool RedVSIShell::RunFragComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok  = cInputBuffer.GetToken();
    RedToken cCodeTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordRun() && cCodeTok.Type().IsStringLiteral())
    {
        RedTokenBuffer cTokenList;
        RedDataString strCodeFragment = cCodeTok.Text();
        if (!RedTokenFactory::CreateTokens(strCodeFragment, cTokenList))
            return true;

        // - - - From this point on we need to delete the created elements - - - - - -

        // Turn the tokens into code
        RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cVSIBase.cLog);
        if (topCmd == NULL)
        {
            cVSIBase.cLog.AddErrorEvent("Code construction competition failed.\n");
            return true;
        }
        if (cVSIBase.cLog.ContainsError())
        {
            cVSIBase.cLog.AddErrorEvent("Error detected post-Code construction competition.\n");
            delete topCmd;
            return true;
        }

        // Execute the code in a context
        RedVSIContextRoutine testContext(&cVSIBase, topCmd);
        testContext.SetBaseContext(&cVSIBase);
        testContext.Execute(10);
        if (cVSIBase.cLog.ContainsError())
        {
            cVSIBase.cLog.AddErrorEvent("Code execution error.\n");
        }
        delete topCmd;
        return true;
    }
    else
    {
        // not data init command, return the token and fail the comp.
        cInputBuffer.SetTokenIndexBackOne();
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::RunFuncComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordRun())
    {
        cVSIBase.cLog.AddText("RedVSIShell::RunFuncComp");
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIShell::ExitComp(RedTokenBuffer& cInputBuffer)
{
    RedToken cCmdTok = cInputBuffer.GetToken();

    if (cCmdTok.Predef().IsKeywordExit())
    {
        cVSIBase.eState = TEContextState::Ended;
        cVSIBase.cLog.AddText("Exit Command Processed.");
        return true;
    }
    else
    {
        // not exit command, return the token and fail the comp.
        cInputBuffer.SetTokenIndexBackOne();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
