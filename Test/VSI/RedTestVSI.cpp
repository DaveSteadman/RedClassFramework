
#include "RedTestVSI.h"
#include "RedVSINamespace.h"

#include "RedVSICmdSerialiser.h"
#include "RedVSILibTokenMap.h"

namespace Red {
namespace Test {

using namespace Red::Core;
using namespace Red::VSI;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestVSI::RunUnitTest(void)
{
    if (RedTestVSI::TestParseTreeVal().IsFail())      return 0;
    if (RedTestVSI::TestParseTreeVar().IsFail())      return 0;
    if (RedTestVSI::TestParseTreeBinaryOp().IsFail()) return 0;

    if (RedTestVSI::TestParseFactory_001().IsFail())  return 0;
    if (RedTestVSI::TestParseFactory_002().IsFail())  return 0;
    if (RedTestVSI::TestParseFactory_003().IsFail())  return 0;

    if (RedTestVSI::TestCmdNew().IsFail())            return 0;
    if (RedTestVSI::TestTokeniseCode().IsFail())      return 0;


//    if (RedTestVSI::TestLoadLibrary_001().IsFail())   return 0;
    if (RedTestVSI::TestLoadLibrary_002().IsFail())   return 0;

    if (RedTestVSI::TestSaveLibrary_001().IsFail())   return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseTreeVal(void)
{
    // Basic Creation and calculation
    {
        RedVariant           testValue("Hello");
        RedVSIParseTreeVal   testPTVal;
        RedVSIContextRoutine testContext;
        RedVariant           expRes(12);

        testPTVal.SetValue(testValue);

        testPTVal.CalcResult(&testContext);

        expRes = testContext.GetExprResult(&testPTVal);

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
        RedVSIContextRoutine testContext;
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedString("testVar1"));

        RedNumber* testVar1  = REDNULL;
        RedType*   pFoundDataItem = REDNULL;
        if (testContext.FindDataItem(RedString("testVar1"), pFoundDataItem))
        {
            if (pFoundDataItem->Type() != kDataTypeNum)
                return kResultFail;

            testVar1 = (RedNumber*)pFoundDataItem;
            *testVar1 = 1.234;

            RedVSIParseTreeVar ptv;
            ptv.SetVarName(RedString("testVar1"));

            ptv.CalcResult(&testContext);

            RedVariant exprRes = testContext.GetExprResult(&ptv);

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
        RedVSIContextRoutine    testContext;

        RedVSIParseTreeVal      testPTVal1(RedNumber(1200));
        RedVSIParseTreeVal      testPTVal2(RedNumber(34));
        RedVSIParseTreeBinaryOp testPTOp1(&testPTVal1, RedVSILangElement::BinaryOpPlus(), &testPTVal2);

        testPTVal1.CalcResult(&testContext);
        testPTVal2.CalcResult(&testContext);
        testPTOp1.CalcResult(&testContext);

        RedNumber expectRes(1234);
        RedVariant exprRes = testContext.GetExprResult(&testPTOp1);

        if(!exprRes.Type().IsNum())
            return kResultFail;
        if(exprRes.NumberValue() != expectRes)
            return kResultFail;
    }

    // Simple Addition Test: String
    {
        RedVSIContextRoutine    testContext;

        RedVSIParseTreeVal      testPTVal1(RedString("Hello"));
        RedVSIParseTreeVal      testPTVal2(RedString(" Red"));
        RedVSIParseTreeBinaryOp testPTOp1(&testPTVal1, RedVSILangElement::BinaryOpPlus(), &testPTVal2);

        testPTVal1.CalcResult(&testContext);
        testPTVal2.CalcResult(&testContext);
        testPTOp1.CalcResult(&testContext);

        RedString expectRes("Hello Red");
        RedVariant exprRes = testContext.GetExprResult(&testPTOp1);

        if(!exprRes.Type().IsStr())
            return kResultFail;
        if(exprRes.StringValue() != expectRes)
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestTokeniseCode(void)
{
    RedVSILibTokenMap map;
    RedString testCode = "new local number varX = 3.14159 varX = varX * 2 return varX";
    {
        RedVSITokenBuffer cInputBuffer;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testCode, map.cVSILibTokenMap, cInputBuffer);

        RedString debugText = cInputBuffer.DebugDump();

        if (iCreateResult == 0)
            return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_001(void)
{
    {
        RedString testExpr("4300 + 21");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedString("+"), RedVSIIOElement::SymbolPlus());
        tokenMap.Add(RedString("-"), RedVSIIOElement::SymbolMinus());

        RedVSITokenBuffer tokBuf;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr,tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.IsError())
            return kResultFail;
        if (pt == REDNULL)
            return kResultFail;

        RedVSIContextRoutine testContext;
        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedVariant res = testContext.GetExprResult(pt);

        if (res.NumberValue() != RedNumber(4321))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_002(void)
{
    {
        RedString testExpr("x = 'hello' + ' red'");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedString("+"), RedVSIIOElement::SymbolPlus());
        tokenMap.Add(RedString("="), RedVSIIOElement::SymbolAssignEqual());
        //tokenMap.Add(RedString("'"), RedVSIIOElement::SymbolStringContent());

        RedVSITokenBuffer tokBuf;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr,tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.IsError())
            return kResultFail;
        if (pt == REDNULL)
            return kResultFail;

        RedVSIContextRoutine testContext;
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeString(), RedString("x"));

        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedVariant res = testContext.GetExprResult(pt);

        if (res.NumberValue() != RedString("hello red"))
            return kResultFail;

        RedType* resultX;
        testContext.FindDataItem(RedString("x"), resultX);
        if (resultX->Type() != kDataTypeStr)
            return kResultFail;
        if (*(RedString*)resultX != RedString("hello red"))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestParseFactory_003(void)
{
    {
        RedString testExpr("x = (3 + 2) * 20");

        RedVSITokenElementMap tokenMap;
        tokenMap.Add(RedString("+"), RedVSIIOElement::SymbolPlus());
        tokenMap.Add(RedString("*"), RedVSIIOElement::SymbolMultiply());
        tokenMap.Add(RedString("="), RedVSIIOElement::SymbolAssignEqual());
        tokenMap.Add(RedString("("), RedVSIIOElement::SymbolOpenBracket());
        tokenMap.Add(RedString(")"), RedVSIIOElement::SymbolCloseBracket());

        RedVSITokenBuffer tokBuf;

        int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr,tokenMap, tokBuf);

        if (iCreateResult == 0)
            return kResultFail;

        RedLog log;
        RedVSIParseTreeInterface* pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

        if (log.IsError())
            return kResultFail;
        if (pt == REDNULL)
            return kResultFail;

        RedVSIContextRoutine testContext;
        testContext.CreateDataItem(RedVSILangElement::LocationStack(), RedVSILangElement::TypeNumber(), RedString("x"));

        testContext.QueueExpr(pt);
        testContext.ExecuteExprQueue();

        RedVariant res = testContext.GetExprResult(pt);

        if (res.NumberValue() != RedNumber(100))
            return kResultFail;

        RedType* resultX;
        testContext.FindDataItem(RedString("x"), resultX);
        if (resultX->Type() != kDataTypeNum)
            return kResultFail;
        if (*(RedNumber*)resultX != RedNumber(100))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestCmdNew(void)
{
    RedVSICmdNew cmdNew;
    {

        RedVSIParseTreeInterface* pt = REDNULL;
        {
            RedString testExpr("4300 + 12");

            RedVSITokenElementMap tokenMap;
            tokenMap.Add(RedString("+"), RedVSIIOElement::SymbolPlus());
            tokenMap.Add(RedString("-"), RedVSIIOElement::SymbolMinus());

            RedVSITokenBuffer tokBuf;

            int iCreateResult = RedVSITokenFactory::CreateTokens(testExpr, tokenMap, tokBuf);

            if (iCreateResult == 0)
                return kResultFail;

            RedLog log;
            pt = RedVSIParseFactory::ConstructAssignExpr(tokBuf, log);

            if (log.IsError())
                return kResultFail;
            if (pt == REDNULL)
                return kResultFail;
        }

        cmdNew.SetDetails(kLangElementTypeNumber, kLangElementLocationStack, RedString("x"), pt);

        RedVSIContextRoutine testContext;
        cmdNew.QueueExpr(&testContext);
        testContext.ExecuteExprQueue();
        cmdNew.Execute(&testContext);

        RedType* resultX;
        testContext.FindDataItem(RedString("x"), resultX);
        if (resultX->Type() != kDataTypeNum)
            return kResultFail;
        if (*(RedNumber*)resultX != RedNumber(4312))
            return kResultFail;
    }

    // serialise the command
    {
        RedVSILibTokenMap cLibMap;

        RedVSITokenBuffer cTokenBuffer;
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, &cmdNew);
        RedBufferOutput outBuf;
        RedVSICmdSerialiser::TokenBufferToOutputBuffer(cTokenBuffer, cLibMap.cVSILibTokenMap, outBuf);

        if (outBuf.ExtractData() != RedString("new local number x = 4300 + 12 "))
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//RedResult RedTestVSI::TestLoadLibrary_001(void)
//{
//    {
//        RedLog    log;
//        RedString path("/tmp/TestBasicVSILibrary_0001.tml");
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

RedResult RedTestVSI::TestLoadLibrary_002(void)
{
    RedVSILib        vsiCodeLib;
    RedVSILibFactory vsiCodeLibFactory(&vsiCodeLib);

    // Test read in class
    {
        RedLog    log;
        RedString iPath("/tmp/TestBasicVSILibrary_0001.tml");

        RedTmlElement* newX = REDNULL;

        if (RedTmlAction::CreateTmlFromFile(iPath, &newX) != kResultSuccess)
            return kResultFail;

        RedTmlNode* newNodeX = (RedTmlNode*)newX;


        



        vsiCodeLibFactory.InputTmlClass(*newNodeX, log);

        if (vsiCodeLib.NumClasses() == 0)
            return kResultFail;
    }

    // Test output class
    {
        RedLog    log;
        RedString iPath("/tmp/TestBasicVSILibrary_0003.tml");

        RedTmlElement* newX2 = REDNULL;
        RedString name("TestRoutines");

        newX2 =  vsiCodeLibFactory.OutputTmlClass(name);

        RedBufferOutput oB2;
        RedTmlAction::SerialiseTinyML(oB2, newX2, eLinedIndentedContent);
        oB2.WriteNewLine();
        RedIOHandler::OutputBufferToFile(iPath, oB2);
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestSaveLibrary_001(void)
{
    {
        RedVSICmdNew pCmd1(kLangElementTypeNumber, kLangElementLocationStack, RedString("x"), REDNULL);
        RedVSICmdExpr();
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestVSI::TestRunProg_001(void)
{
    {
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




