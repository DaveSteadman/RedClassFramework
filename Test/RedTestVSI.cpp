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

#include "RedTestVSI.h"
#include "RedVSINamespace.h"
#include "RedVSIContextRoutine.h"

#include "RedVSICmdSerialiser.h"
#include "RedVSILibTokenMap.h"

using namespace Red::Core;
using namespace Red::VSI;

namespace Red {
namespace Test {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTestVSI::RunUnitTest(RedLog& log)
{
    if (RedTestVSI::TestParseTreeVal().IsFail())      { log.AddErrorEvent("VSI Unit Test: TestParseTreeVal Failed");      return; }
    if (RedTestVSI::TestParseTreeVar().IsFail())      { log.AddErrorEvent("VSI Unit Test: TestParseTreeVar Failed");      return; }
    if (RedTestVSI::TestParseTreeBinaryOp().IsFail()) { log.AddErrorEvent("VSI Unit Test: TestParseTreeBinaryOp Failed"); return; }

    if (RedTestVSI::TestParseFactory_001().IsFail())  { log.AddErrorEvent("VSI Unit Test: TestParseFactory_001 Failed");  return; }
    if (RedTestVSI::TestParseFactory_002().IsFail())  { log.AddErrorEvent("VSI Unit Test: TestParseFactory_002 Failed");  return; }
    if (RedTestVSI::TestParseFactory_003().IsFail())  { log.AddErrorEvent("VSI Unit Test: TestParseFactory_003 Failed");  return; }

    if (RedTestVSI::TestCmdNew().IsFail())            { log.AddErrorEvent("VSI Unit Test: TestCmdNew Failed");            return; }
    if (RedTestVSI::TestTokeniseCode().IsFail())      { log.AddErrorEvent("VSI Unit Test: TestTokeniseCode Failed");      return; }

    if (RedTestVSI::TestFragment_New().IsFail())      { log.AddErrorEvent("VSI Unit Test: TestFragment_New Failed");      return; }
    if (RedTestVSI::TestFragment_NewTypes().IsFail()) { log.AddErrorEvent("VSI Unit Test: TestFragment_NewTypes Failed"); return; }
    if (RedTestVSI::TestFragment_Expr().IsFail())     { log.AddErrorEvent("VSI Unit Test: TestFragment_Expr Failed");     return; }
    if (RedTestVSI::TestFragment_If().IsFail())       { log.AddErrorEvent("VSI Unit Test: TestFragment_If Failed");       return; }
    if (RedTestVSI::TestFragment_While().IsFail())    { log.AddErrorEvent("VSI Unit Test: TestFragment_While Failed");    return; }
    if (RedTestVSI::TestFragment_Log().IsFail())      { log.AddErrorEvent("VSI Unit Test: TestFragment_Log Failed");      return; }

    if (RedTestVSI::TestRunProg_001().IsFail())       { log.AddErrorEvent("VSI Unit Test: TestRunProg_001 Failed");       return; }

    log.AddText("VSI Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseTreeVal(void)
{
    // Basic Creation and calculation
    {
        RedLog               cLog;
        RedDataVariant       testValue("Hello");
        RedVSIParseTreeVal   testPTVal;
        RedVSIContextRoutine testContext(&cLog);
        RedDataVariant       expRes(12);

        testPTVal.SetValue(testValue);

        testPTVal.CalcResult(&testContext);

        expRes = testContext.ExprResult(&testPTVal);

        if (expRes != testValue)
            return kResultFail;

    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseTreeVar(void)
{
    // Basic Creation and calculation
    {
        RedLog               cLog;
        RedVSIContextRoutine testContext(&cLog);
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedDataString("testVar1"));

        RedDataNumber* testVar1 = NULL;
        RedType* pFoundDataItem = NULL;
        if (testContext.FindDataItem(RedDataString("testVar1"), pFoundDataItem))
        {
            if (pFoundDataItem->Type() != kDataTypeNum)
                return kResultFail;

            testVar1 = (RedDataNumber*)pFoundDataItem;
            *testVar1 = 1.234;

            RedVSIParseTreeVar ptv;
            ptv.SetVarName(RedDataString("testVar1"));

            ptv.CalcResult(&testContext);

            RedDataVariant exprRes = testContext.ExprResult(&ptv);

            if (!exprRes.Type().IsNum())
                return kResultFail;
            if (exprRes.NumberValue() != *testVar1)
                return kResultFail;
        }
        else
        {
            return kResultFail;
        }
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseTreeBinaryOp(void)
{
    // Simple Addition Test: Number
    {
        RedLog                  cLog;
        RedVSIContextRoutine    testContext(&cLog);

        RedVSIParseTreeVal      testPTVal1(RedDataNumber(1200));
        RedVSIParseTreeVal      testPTVal2(RedDataNumber(34));
        RedVSIParseTreeBinaryOp testPTOp1(&testPTVal1, RedVSILangElement::BinaryOpPlus(), &testPTVal2);

        testPTVal1.CalcResult(&testContext);
        testPTVal2.CalcResult(&testContext);
        testPTOp1.CalcResult(&testContext);

        RedDataNumber expectRes(1234);
        RedDataVariant exprRes = testContext.ExprResult(&testPTOp1);

        if (!exprRes.Type().IsNum())
            return kResultFail;
        if (exprRes.NumberValue() != expectRes)
            return kResultFail;
    }

    // Simple Addition Test: String
    {
        RedLog                  cLog;
        RedVSIContextRoutine    testContext(&cLog);

        RedVSIParseTreeVal      testPTVal1(RedDataString("Hello"));
        RedVSIParseTreeVal      testPTVal2(RedDataString(" Red"));
        RedVSIParseTreeBinaryOp testPTOp1(&testPTVal1, RedVSILangElement::BinaryOpPlus(), &testPTVal2);

        testPTVal1.CalcResult(&testContext);
        testPTVal2.CalcResult(&testContext);
        testPTOp1.CalcResult(&testContext);

        RedDataString expectRes("Hello Red");
        RedDataVariant exprRes = testContext.ExprResult(&testPTOp1);

        if (!exprRes.Type().IsStr())
            return kResultFail;
        if (exprRes.StringValue() != expectRes)
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestTokeniseCode(void)
{
    RedVSILibTokenMap map;
    RedDataString testCode = "new stack number varX = 3.14159 varX = varX * 2 return varX";
    {
        RedVSITokenBuffer cInputBuffer;

        bool bCreateResult = RedVSITokenFactory::CreateTokens(testCode, map.cVSILibTokenMap, cInputBuffer);

        RedDataString debugText = cInputBuffer.DebugDump();

        if (bCreateResult == false)
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_001(void)
{
    {
        RedDataString testExpr("4300 + 21");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedDataString("+"), RedVSIIOElement::SymbolOperatorPlus());
        tokenMap.Add(RedDataString("-"), RedVSIIOElement::SymbolOperatorMinus());

        RedVSITokenBuffer tokBuf;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr, tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.ContainsError())
            return kResultFail;
        if (pt == NULL)
            return kResultFail;

        RedLog               cLog;
        RedVSIContextRoutine testContext(&cLog);
        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedDataVariant res = testContext.ExprResult(pt);

        if (res.NumberValue() != RedDataNumber(4321))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_002(void)
{
    {
        RedDataString testExpr("x = 'hello' + ' red'");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedDataString("+"), RedVSIIOElement::SymbolOperatorPlus());
        tokenMap.Add(RedDataString("="), RedVSIIOElement::SymbolAssignEqual());
        //tokenMap.Add(RedDataString("'"), RedVSIIOElement::SymbolStringContent());

        RedVSITokenBuffer tokBuf;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr, tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.ContainsError())
            return kResultFail;
        if (pt == NULL)
            return kResultFail;

        RedLog               cLog;
        RedVSIContextRoutine testContext(&cLog);
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeString(), RedDataString("x"));

        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedDataVariant res = testContext.ExprResult(pt);

        if (res.StringValue() != RedDataString("hello red"))
            return kResultFail;

        RedType* resultX;
        testContext.FindDataItem(RedDataString("x"), resultX);
        if (resultX->Type() != kDataTypeStr)
            return kResultFail;
        if (*(RedDataString*)resultX != RedDataString("hello red"))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_003(void)
{
    {
        // - - - Define the data - - - 

        RedDataString testExpr("x = (3 + 2) * 20");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedDataString("+"), RedVSIIOElement::SymbolOperatorPlus());
        tokenMap.Add(RedDataString("*"), RedVSIIOElement::SymbolOperatorMultiply());
        tokenMap.Add(RedDataString("="), RedVSIIOElement::SymbolAssignEqual());
        tokenMap.Add(RedDataString("("), RedVSIIOElement::SymbolBracketOpen());
        tokenMap.Add(RedDataString(")"), RedVSIIOElement::SymbolBracketClose());

        // - - - Extract the tokens - - - 

        RedVSITokenBuffer tokBuf;
        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr, tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.ContainsError())
            return kResultFail;
        if (pt == NULL)
            return kResultFail;
        log.Clear();

        // - - - Execute the expression - - - 

        RedVSIContextRoutine testContext(&log);
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedDataString("x"));
        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        if (log.ContainsError())
            return kResultFail;

        // - - - Check the calculaterd balue - - - 

        RedDataVariant res = testContext.ExprResult(pt);
        if (res.NumberValue() != RedDataNumber(100))
            return kResultFail;

        RedType* resultX;
        testContext.FindDataItem(RedDataString("x"), resultX);
        if (resultX->Type() != kDataTypeNum)
            return kResultFail;
        if (*(RedDataNumber*)resultX != RedDataNumber(100))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestCmdNew(void)
{
    RedVSICmdNew cmdNew;
    {
        RedVSIParseTreeInterface* pt = NULL;
        {
            RedDataString testExpr("4300 + 12");

            RedVSITokenElementMap tokenMap;
            tokenMap.Add(RedDataString("+"), RedVSIIOElement::SymbolOperatorPlus());
            tokenMap.Add(RedDataString("-"), RedVSIIOElement::SymbolOperatorMinus());

            RedVSITokenBuffer tokBuf;

            int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr, tokenMap, tokBuf);

            if (iCreateResult == 0)
                return kResultFail;

            RedLog log;
            pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

            if (log.ContainsError())
                return kResultFail;
            if (pt == NULL)
                return kResultFail;
        }

        cmdNew.SetDetails(kLangElementTypeNumber, kLangElementLocationStack, RedDataString("x"), NULL, pt);

        RedLog               cLog;
        RedVSIContextRoutine testContext(&cLog);
        cmdNew.QueueExpr(&testContext);
        testContext.ExecuteExprQueue();
        cmdNew.Execute(&testContext);

        RedType* resultX;
        testContext.FindDataItem(RedDataString("x"), resultX);
        if (resultX->Type() != kDataTypeNum)
            return kResultFail;
        if (*(RedDataNumber*)resultX != RedDataNumber(4312))
            return kResultFail;
    }

    // serialise the command
    {
        RedVSILibTokenMap cLibMap;

        RedVSITokenBuffer cTokenBuffer;
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, &cmdNew);
        RedBufferOutput outBuf;
        RedVSICmdSerialiser::TokenBufferToOutputBuffer(cTokenBuffer, cLibMap.cVSILibTokenMap, outBuf);

        if (outBuf.ExtractData() != RedDataString("new stack number x = 4300 + 12 "))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedResult RedTestVSI::TestLoadLibrary_001(void)
//{
//    {
//        RedLog    log;
//        RedDataString path("/tmp/TestBasicVSILibrary_0001.tml");
//
//        RedVSILibTokenMap tokenMap;
//        tokenMap.SetupTokenMap();
//
//        RedVSILib        vsiCodeLib;
//        RedVSILibFactory vsiCodeLibFactory(&vsiCodeLib);
//
//        RedBufferInput iB;
//        RedIOHandler::InputBufferFromFile(path, iB);
//        vsiCodeLibFactory.InputCode(iB.StringBuffer(), tokenMap.cVSILibTokenMap, log);
//
//        if (vsiCodeLib.NumClasses() == 0)
//            return kResultFail;
//
//    }
//    return kResultSuccess;
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedResult RedTestVSI::TestLoadLibrary_002(void)
//{
//    RedVSILib        vsiCodeLib;
//    RedVSILibFactory vsiCodeLibFactory(&vsiCodeLib);
//
//    // Test read in class
//    {
//        RedLog    log;
//        RedDataString iPath("/tmp/TestBasicVSILibrary_0001.tml");
//
//        RedTinyMLElement* newX = NULL;
//
//        if (RedTinyMLAction::CreateTmlFromFile(iPath, &newX) != kResultSuccess)
//            return kResultFail;
//
//        RedTinyMLNode* newNodeX = (RedTinyMLNode*)newX;
//
//
//        
//
//
//
//        vsiCodeLibFactory.InputTmlClass(*newNodeX, log);
//
//        if (vsiCodeLib.NumClasses() == 0)
//            return kResultFail;
//    }
//
//    // Test output class
//    {
//        RedLog    log;
//        RedDataString iPath("/tmp/TestBasicVSILibrary_0003.tml");
//
//        RedTinyMLElement* newX2 = NULL;
//        RedDataString name("TestRoutines");
//
//        newX2 =  vsiCodeLibFactory.OutputTmlClass(name);
//
//        RedBufferOutput oB2;
//        RedTinyMLAction::SerialiseTinyML(oB2, newX2, eLinedIndentedContent);
//        oB2.WriteNewLine();
//        RedIOHandler::OutputBufferToFile(iPath, oB2);
//    }
//
//    return kResultSuccess;
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedResult RedTestVSI::TestSaveLibrary_001(void)
//{
//    {
//        RedVSICmdNew pCmd1(kLangElementTypeNumber, kLangElementLocationStack, RedDataString("x"), NULL);
//        RedVSICmdLet();
//    }
//    return kResultSuccess;
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestRunProg_001(void)
{
    RedVSILib        vsiCodeLib;
    RedVSILibFactory vsiCodeLibFactory(&vsiCodeLib);

    {
        RedBufferInput codeBuffer(RedDataString(" \
            {{class} \
                {{name}TestRoutines} \
                {{routine} \
                    {{name}TwoPi} \
                    {{code} \
                        new stack number varX = 3.14159 \
                        varX = varX * 2 \
                        return varX \
                    } \
                } \
                {{routine} \
                    {{name}Double} \
                    {{params} \
                        {{X}number} \
                    } \
                    {{code} \
                        X = X * 2 \
                        return X \
                    } \
                } \
                {{routine} \
                    {{name}Halve} \
                    {{params} \
                        {{X}number} \
                    } \
                    {{code} \
                        X = X / 2 \
                        return X \
                    } \
                } \
                {{routine} \
                    {{name}TestCall} \
                    {{code} \
                        new stack number x1 = 1234 \
                        new heap  number x2 = 0 \
                        x2 = TestRoutines::Halve(x1) \
                    } \
                } \
                {{routine} \
                    {{name}TestExecute} \
                    {{code} \
                        new stack number varX = 3.14159 \
                        new stack number varY \
                        varY = varX * 2 \
                    } \
                } \
            } "));

        // Create the TML tree from the code buffer
        RedTinyMLElement* tmlTreeElement = RedTinyMLFileIO::CreateTinyML(codeBuffer);
        RedTinyMLNode* tmlTreeNode = dynamic_cast<RedTinyMLNode*>(tmlTreeElement);

        if (tmlTreeElement == NULL)
            return kResultFail;

        // Paint after which we own the created structure
        if (tmlTreeNode == NULL)
        {
            delete tmlTreeElement;
            return kResultFail;
        }

        // Import the TML into the code library
        RedLog log;
        vsiCodeLibFactory.InputTmlClass(tmlTreeNode, log);
        if (vsiCodeLib.NumClasses() == 0)
            return kResultFail;
        if (log.ContainsError())
            return kResultFail;

        // Execute code
        /*
        {
            RedVSIContextThread* tc;

            if (RedVSIContextFactory::CreateThreadContextForRoutine("TestRoutines", "TestCall", &vsiCodeLib, &tc, log) == kResultSuccess)
            {
                tc->Execute(10);

                if (log.ContainsError()) return kResultFail;

                RedDataNumber* pXNum = dynamic_cast<RedDataNumber*>(tc->HeapDataItem("x2"));
                if (pXNum)
                {
                    if (!pXNum->IsEqualToWithinTollerance(617, kNumberFloatCompTollerance))
                        return kResultFail;
                }
                else
                    return kResultFail;
            }
        }
        */
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_New(void)
{
    // Define a small code fragment
    RedDataString strCodeFragment = "new stack number x = 3.2 x = x * 2";

    // Turn the code into tokens
    RedVSILibTokenMap cTokenMap;
    RedVSITokenBuffer cTokenList;
    RedLog            cRedLog;
    if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
        return kResultFail;

    // Turn the tokens into code
    RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
    if (topCmd == NULL)
        return kResultFail;
    if (cRedLog.ContainsError())
        return kResultFail;

    // Execute the code in a context
    RedVSIContextRoutine testContext(&cRedLog, topCmd);
    testContext.Execute(10);
    if (cRedLog.ContainsError())
        return kResultFail;

    // Check the execution result
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 6.4) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_NewTypes(void)
{
    // Define a small code fragment
    RedDataString strCodeFragment = " \
        new stack bool   testB = true \
        new stack number testN = 123 \
        new stack string testS = 'Str' ";

    // Turn the code into tokens
    RedVSILibTokenMap cTokenMap;
    RedVSITokenBuffer cTokenList;
    RedLog            cRedLog;
    if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
        return kResultFail;

    // Turn the tokens into code
    RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
    if (topCmd == NULL)
        return kResultFail;
    if (cRedLog.ContainsError())
        return kResultFail;

    // Execute the code in a context
    RedVSIContextRoutine testContext(&cRedLog, topCmd);
    while (!testContext.IsExecutionComplete())
        testContext.Execute(1);
    if (cRedLog.ContainsError())
        return kResultFail;

    // Check the execution result
    RedDataVariant testB = testContext.DataItemAsVariant("testB");
    if (testB != true) return kResultFail;
    RedDataVariant testN = testContext.DataItemAsVariant("testN");
    if (testN != 123) return kResultFail;
    RedDataVariant testS = testContext.DataItemAsVariant("testS");
    if (testS != "Str") return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_Expr(void)
{
    // Define a small code fragment
    RedDataString strCodeFragment = "\
        new stack number x   = 3 \
        x = x + 1 \
        x = x * 2";

    // Turn the code into tokens
    RedVSILibTokenMap cTokenMap;
    RedVSITokenBuffer cTokenList;
    RedLog            cRedLog;
    if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
        return kResultFail;

    // - - - From this point on we need to delete the created elements - - - - - -
 
    // Turn the tokens into code
    RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
    if (topCmd == NULL)
        return kResultFail;
    if (cRedLog.ContainsError())
    {
        delete topCmd;
        return kResultFail;
    }

    // Execute the code in a context
    RedVSIContextRoutine testContext(&cRedLog, topCmd);
    testContext.Execute(10);
    if (cRedLog.ContainsError())
    {
        delete topCmd;
        return kResultFail;
    }

    // Check the execution result
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 8) 
    {
        delete topCmd;
        return kResultFail;
    }

    delete topCmd;
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_If(void)
{
    {
        // Define a small code fragment
        RedDataString strCodeFragment = "\
        new stack number x   = 3 \
        new stack number res = 0 \
        if x < 4 then \
            res = x + 1 \
        endif \
        res = res * 3";

        // Turn the code into tokens
        RedVSILibTokenMap cTokenMap;
        RedVSITokenBuffer cTokenList;
        RedLog            cRedLog;
        if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
            return kResultFail;

        // Turn the tokens into code
        RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
        if (topCmd == NULL)
            return kResultFail;
        if (cRedLog.ContainsError())
            return kResultFail;

        // Execute the code in a context
        RedVSIContextRoutine testContext(&cRedLog);
        RedVSIContextFactory::LoadFragmentIntoContext(strCodeFragment, testContext);
        testContext.Execute(10);
        if (cRedLog.ContainsError())
            return kResultFail;

        // Check the execution result
        RedDataVariant x = testContext.DataItemAsVariant("res");
        if (x != 12) return kResultFail;
    }

    {
        // Define a small code fragment
        RedDataString strCodeFragment = "\
        new stack number x   = 3 \
        if x == 4 then \
            x = x + 10 \
        endif";

        // Turn the code into tokens
        RedVSILibTokenMap cTokenMap;
        RedVSITokenBuffer cTokenList;
        RedLog            cRedLog;
        if (!RedVSITokenFactory::CreateTokens(strCodeFragment, cTokenMap.cVSILibTokenMap, cTokenList))
            return kResultFail;

        // Turn the tokens into code
        RedVSICmd* topCmd = RedVSICmdFactory::RunConstuctionCompetition(cTokenList, cRedLog);
        if (topCmd == NULL)
            return kResultFail;
        if (cRedLog.ContainsError())
            return kResultFail;

        // Execute the code in a context
        RedVSIContextRoutine testContext(&cRedLog);
        RedVSIContextFactory::LoadFragmentIntoContext(strCodeFragment, testContext);
        testContext.Execute(10);
        if (cRedLog.ContainsError())
            return kResultFail;

        // Check the execution result
        RedDataVariant x = testContext.DataItemAsVariant("x");
        if (x != 3) return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_While(void)
{
    // Define a small code fragment
    // The quick +1 on the end help check that we've correctly detected the endof the command
    RedDataString strCodeFragment = " \
        new stack number x = 2 \
        while x < 99 loop \
            x = x * 2 \
        endloop \
        x = x + 1 ";

    RedLog                 cRedLog;
    RedVSIContextRoutine  testContext(&cRedLog);

    RedVSIContextFactory::LoadFragmentIntoContext(strCodeFragment, testContext);
    if (cRedLog.ContainsError()) return kResultFail;

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!cRedLog.ContainsError()))
        testContext.Execute(1);

    if (cRedLog.ContainsError())
        return kResultFail;

    // Check the execution result
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 129) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_Log(void)
{
    // Define a small code fragment
    // The quick +1 on the end help check that we've correctly detected the endof the command
    RedDataString strCodeFragment = " \
        new stack number x = 2.2 \
        new stack string zxz = 'zz' \
        log x ";

    RedLog                 cRedLog;
    RedVSIContextRoutine testContext(&cRedLog);

    RedVSIContextFactory::LoadFragmentIntoContext(strCodeFragment, testContext);
    if (cRedLog.ContainsError()) return kResultFail;

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!cRedLog.ContainsError()))
        testContext.Execute(1);

    if (cRedLog.ContainsError())
        return kResultFail;

    // Check the execution result
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 2.2) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




