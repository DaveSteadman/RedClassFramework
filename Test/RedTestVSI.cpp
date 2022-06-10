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

    if (RedTestVSI::TestSignature().IsFail())         { log.AddErrorEvent("VSI Unit Test: TestSignature Failed");         return; }

    log.AddText("VSI Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseTreeVal(void)
{
    // Basic Creation and calculation
    {
        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);

        RedDataVariant       testValue("Hello");
        RedDataVariant       expRes(12);
       
        RedVSIParseTreeVal   testPTVal;

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
        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);

        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedDataString("testVar1"));

        RedDataNumber* testVar1 = NULL;
        RedData* pFoundDataItem = NULL;
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
        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);

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
        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);

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
    RedDataString testCode = "new stack number varX = 3.14159 varX = varX * 2 return varX";
    {
        RedTokenBuffer cInputBuffer;

        bool bCreateResult = RedTokenFactory::CreateTokens(testCode, cInputBuffer);

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

        RedTokenBuffer tokBuf;
        int iCreateResult = RedTokenFactory::CreateTokens(testExpr, tokBuf);

        RedToken cTok1 = tokBuf.GetToken();
        RedToken cTok2 = tokBuf.GetToken();
        RedToken cTok3 = tokBuf.GetToken();

        if (!cTok1.Type().IsNumber())               return kResultFail;
        if (!cTok2.Type().IsSymbol())               return kResultFail;
        if (!cTok3.Type().IsNumber())               return kResultFail;

        if (!cTok1.Predef().IsInvalid())            return kResultFail;
        if (!cTok2.Predef().IsSymbolOperatorPlus()) return kResultFail;
        if (!cTok3.Predef().IsInvalid())            return kResultFail;

        tokBuf.SetTokenIndex(0); // reset token read index for expr-competition
        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (pt == NULL)
            return kResultFail;

        if (log.ContainsError())
            return kResultFail;

        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);

        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedDataVariant res = testContext.ExprResult(pt);

        if (res.NumberValue() != RedDataNumber(4321))
            return kResultFail;

        delete pt;
    }


    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_002(void)
{
    {
        RedDataString testExpr("x = 'hello' + ' red'");

        RedTokenBuffer tokBuf;
        int iCreateResult = RedTokenFactory::CreateTokens(testExpr, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.ContainsError())
            return kResultFail;
        if (pt == NULL)
            return kResultFail;

        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeString(), RedDataString("x"));

        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedDataVariant res = testContext.ExprResult(pt);

        if (res.StringValue() != RedDataString("hello red"))
            return kResultFail;

        RedData* resultX;
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

        // - - - Extract the tokens - - - 

        RedTokenBuffer tokBuf;
        int iCreateResult = RedTokenFactory::CreateTokens(testExpr, tokBuf);

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

        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedDataString("x"));
        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        if (log.ContainsError())
            return kResultFail;

        // - - - Check the calculaterd balue - - - 

        RedDataVariant res = testContext.ExprResult(pt);
        if (res.NumberValue() != RedDataNumber(100))
            return kResultFail;

        RedData* resultX;
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
            RedTokenBuffer tokBuf;

            int iCreateResult = RedTokenFactory::CreateTokens(testExpr, tokBuf);

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

        RedVSIContextBase    baseContext;
        RedVSIContextRoutine testContext(&baseContext);
        cmdNew.QueueExpr(&testContext);
        testContext.ExecuteExprQueue();
        cmdNew.Execute(&testContext);

        RedData* resultX;
        testContext.FindDataItem(RedDataString("x"), resultX);
        if (resultX->Type() != kDataTypeNum)
            return kResultFail;
        if (*(RedDataNumber*)resultX != RedDataNumber(4312))
            return kResultFail;
    }

    // serialise the command
    {
        RedTokenBuffer cTokenBuffer;
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, &cmdNew);
        RedBufferOutput outBuf;
        RedVSICmdSerialiser::TokenBufferToOutputBuffer(cTokenBuffer, outBuf);

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


        {
            RedVSIContextBase    cVSIBase;

            RedVSILibFactory vsiCodeLibFactory(&cVSIBase.cCodeLib);
            vsiCodeLibFactory.InputTmlClass(tmlTreeNode, cVSIBase.cLog);

            RedVSICmd* pTopCmd = NULL;
            RedVSILibRoutine* pRtn = cVSIBase.cCodeLib.FindRoutine("TestRoutines", "TestCall");
            if (pRtn != NULL)
                pTopCmd = pRtn->FirstCommand();
                
            RedVSIContextBase    baseContext;
            RedVSIContextRoutine testContext(&baseContext, pTopCmd);

            testContext.SetBaseContext(&cVSIBase);
            testContext.Execute(10);
            if (cVSIBase.cLog.ContainsError())
            {
                cVSIBase.cLog.AddErrorEvent("Code execution error.\n");
            }
        }
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestFragment_New(void)
{
    // Define a small code fragment
    RedDataString strCodeFragment = "new stack number x=3.2 x=x*2";

    RedVSIContextBase baseContext;

    // Turn the tokens into code
    RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
    if (pTopCmd == NULL)
        return kResultFail;
    RedVSIContextRoutine testContext(&baseContext, pTopCmd);

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
        testContext.Execute(5);
    delete pTopCmd;

    // Check the execution result
    if (baseContext.cLog.ContainsError())
        return kResultFail;
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

    RedVSIContextBase baseContext;

    // Turn the tokens into code
    RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
    if (pTopCmd == NULL)
        return kResultFail;
    RedVSIContextRoutine testContext(&baseContext, pTopCmd);

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
        testContext.Execute(5);
    delete pTopCmd;

    // Check the execution result
    if (baseContext.cLog.ContainsError())
        return kResultFail;
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
        new stack number x = 3 \
        x = x + 1 \
        x = x * 2";

    RedVSIContextBase baseContext;

    // Turn the tokens into code
    RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
    if (pTopCmd == NULL)
        return kResultFail;
    RedVSIContextRoutine testContext(&baseContext, pTopCmd);

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
        testContext.Execute(5);
    delete pTopCmd;

    // Check the execution result
    if (baseContext.cLog.ContainsError())
        return kResultFail;
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 8) 
        return kResultFail;

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

        RedVSIContextBase baseContext;

        // Turn the tokens into code
        RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
        if (pTopCmd == NULL)
            return kResultFail;
        RedVSIContextRoutine testContext(&baseContext, pTopCmd);

        // Execute the code in a context, while we have no completion and no error
        while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
            testContext.Execute(5);
        delete pTopCmd;

        // Check the execution result
        if (baseContext.cLog.ContainsError())
            return kResultFail;
        RedDataVariant x = testContext.DataItemAsVariant("res");
        if (x != 12) return kResultFail;
    }

    {
        // Define a small code fragment
        RedDataString strCodeFragment = "\
        new stack number x = 3 \
        if x == 4 then \
            x = x + 10 \
        endif";

        RedVSIContextBase baseContext;

        // Turn the tokens into code
        RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
        if (pTopCmd == NULL)
            return kResultFail;
        RedVSIContextRoutine testContext(&baseContext, pTopCmd);

        // Execute the code in a context, while we have no completion and no error
        while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
            testContext.Execute(5);
        delete pTopCmd;

        // Check the execution result
        if (baseContext.cLog.ContainsError())
            return kResultFail;
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

    RedVSIContextBase baseContext;

    // Turn the tokens into code
    RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
    if (pTopCmd == NULL)
        return kResultFail;
    RedVSIContextRoutine testContext(&baseContext, pTopCmd);

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
        testContext.Execute(5);
    delete pTopCmd;

    // Check the execution result
    if (baseContext.cLog.ContainsError())
        return kResultFail;
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

    RedVSIContextBase baseContext;

    // Turn the tokens into code
    RedVSICmd* pTopCmd = RedVSICmdFactory::RunConstuctionCompetition(strCodeFragment, baseContext.cLog);
    if (pTopCmd == NULL)
        return kResultFail;
    RedVSIContextRoutine testContext(&baseContext, pTopCmd);

    // Execute the code in a context, while we have no completion and no error
    while ((!testContext.IsExecutionComplete()) && (!baseContext.cLog.ContainsError()))
        testContext.Execute(5);
    delete pTopCmd;

    // Check the execution result
    if (baseContext.cLog.ContainsError())
        return kResultFail;
    RedDataVariant x = testContext.DataItemAsVariant("x");
    if (x != 2.2) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestSignature(void)
{
    {
        RedVSIRoutineSignature cCallSig;

        cCallSig.SetStatic();
        cCallSig.SetNames("classname", "funcname");

        cCallSig.AddStaticParam(kDataTypeBool, "name1");
        cCallSig.AddStaticParam(kDataTypeNum,  "name2");

        RedDataString cCheckStr = cCallSig.StringView();

        if (cCheckStr != "classname::funcname(bool name1, number name2)")
            return kResultFail;
    }

    {
        RedVSIRoutineSignature cCallSig;

        cCallSig.SetDynamic();
        cCallSig.SetNames("classname2", "funcname2");

        RedDataBoolean cBool(0);
        cCallSig.AddDynamicParam(&cBool);

        RedDataString cStr("www");
        cCallSig.AddDynamicParam(&cStr);

        RedDataString cCheckStr = cCallSig.StringView();

        if (cCheckStr != "classname2::funcname2(bool, string)")
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




