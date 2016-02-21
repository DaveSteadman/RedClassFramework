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


//#include "RedExpNamespace.h"

#include "RedTestExp.h"

using namespace Red::Core;
//using namespace Red::Exp;

namespace Red {
namespace Test {

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