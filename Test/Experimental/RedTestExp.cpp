

//#include "RedExpNamespace.h"

#include "RedTestExp.h"

namespace Red {
namespace Test {

using namespace Red::Core;
//using namespace Red::Exp;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestExp::RunUnitTest(void)
{
    int ExpOnePassed          = RedTestExp::TestOne();
    int ExpTwoPassed          = RedTestExp::TestTwo();
    //RedBoolean CorePassed         = RedTestCore::RunUnitTest();
    //RedBoolean MathPassed         = RedTestMath::RunUnitTest();

    return ExpOnePassed & ExpTwoPassed;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestExp::TestOne(void)
{
//    RedStringIdMap StrMap;
//    RedString str;
//
//    str = "str1";
//    StrMap.Add(str);
//
//    str = "str2";
//    StrMap.Add(str, 34);
//
//    str = "str3";
//    StrMap.Add(str, 2);
//
//
//    str = StrMap.StringForNumber(34);
//    str = StrMap.StringForNumber(55);

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestExp::TestTwo(void)
{
//    RedStringIdMap StrMap;
//    RedString str;
//
//    RedWordWeb web;
//    RedString str1;
//    RedString str2;
//    RedString str3;
//
//    str1 = "blue";
//    str2 = "isa";
//    str3 = "colour";
//    web.AddElement(StrMap.NumberForString(str1), StrMap.NumberForString(str2), StrMap.NumberForString(str3));
//
//    str1 = "red";
//    str2 = "isa";
//    str3 = "colour";
//    web.AddElement(StrMap.NumberForString(str1), StrMap.NumberForString(str2), StrMap.NumberForString(str3));
//
//    str1 = "green";
//    str2 = "isa";
//    str3 = "colour";
//    web.AddElement(StrMap.NumberForString(str1), StrMap.NumberForString(str2), StrMap.NumberForString(str3));
//
//    str1 = "red";
//    RedWordWeb w;
//    w = web.ElementsWithSrc(StrMap.NumberForString(str1));

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red