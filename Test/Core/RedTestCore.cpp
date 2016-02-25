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

#include "RedTestCore.h"

using namespace Red::Core;

namespace Red {
namespace Test {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTestCore::RunUnitTest(RedLog& log)
{
    if (RedTestCore::TestBoolean().IsFail())      { log.AddErrorEvent("Core Unit Test: TestBoolean Failed");      return; }
    if (RedTestCore::TestChar().IsFail())         { log.AddErrorEvent("Core Unit Test: TestChar Failed");         return; }
    if (RedTestCore::TestNumber().IsFail())       { log.AddErrorEvent("Core Unit Test: TestNumber Failed");       return; }
    if (RedTestCore::TestNumberRange().IsFail())  { log.AddErrorEvent("Core Unit Test: TestNumberRange Failed");  return; }
    if (RedTestCore::TestString().IsFail())       { log.AddErrorEvent("Core Unit Test: TestString Failed");       return; }
    if (RedTestCore::TestDataType().IsFail())     { log.AddErrorEvent("Core Unit Test: TestDataType Failed");     return; }
    if (RedTestCore::TestVariant().IsFail())      { log.AddErrorEvent("Core Unit Test: TestVariant Failed");      return; }
    if (RedTestCore::TestRecord().IsFail())       { log.AddErrorEvent("Core Unit Test: TestRecord Failed");       return; }
    if (RedTestCore::TestLinkedList().IsFail())   { log.AddErrorEvent("Core Unit Test: TestLinkedList Failed");   return; }
    if (RedTestCore::TestResult().IsFail())       { log.AddErrorEvent("Core Unit Test: TestResult Failed");       return; }
    if (RedTestCore::TestEventLog().IsFail())     { log.AddErrorEvent("Core Unit Test: TestEventLog Failed");     return; }
    if (RedTestCore::TestSmartPtr().IsFail())     { log.AddErrorEvent("Core Unit Test: TestSmartPtr Failed");     return; }
    if (RedTestCore::TestDate().IsFail())         { log.AddErrorEvent("Core Unit Test: TestDate Failed");         return; }
    if (RedTestCore::TestTime().IsFail())         { log.AddErrorEvent("Core Unit Test: TestTime Failed");         return; }
    if (RedTestCore::TestOutputBuffer().IsFail()) { log.AddErrorEvent("Core Unit Test: TestOutputBuffer Failed"); return; }

    log.AddText("Core Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestBoolean(void)
{
    RedBoolean x;
    x.SetYes();
    if (!x.IsYes()) return kResultFail;

    RedBoolean y;
    y.SetNo();
    if (!y.IsNo()) return kResultFail;

    x = y;
    if (x != y) return kResultFail;


    RedBoolean* p = dynamic_cast<RedBoolean*>(x.Clone());
    p->SetFalse();
    if (p->IsTrue()) return kResultFail;

    if (p->Type() != RedDataType::Bool()) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestChar(void)
{
    RedChar a = RedChar(0);
    RedChar b = RedChar('A');
    RedChar c = RedChar('{');

    if (a.IsPrintable()) return kResultFail;
    if (!b.IsAlpha())    return kResultFail;
    if (!c.IsBracket())  return kResultFail;

    a.Set(b);
    if (!a.IsAlpha())    return kResultFail;

    c = a;
    if (!a.IsAlpha())    return kResultFail;

    c = 'k';
    if (!a.IsAlpha())    return kResultFail;

    c = 67;
    if (!a.IsAlpha())    return kResultFail;

    a = 'a';
    b = 'b';
    if (a == b) return kResultFail;

    a = b;
    if (a != b) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestNumber(void)
{
    RedNumber x;
    RedNumber y;

    x.Set(12);
    x.Set(12.12);
    y.SetZero();
    y.Set(x);

    RedString strNum;

    strNum.Set("1.234");
    y.SetDecimalString(strNum);
    RedString strNum2 = y.DecimalString();

    RedNumber xx = 1.2355;
    RedString yy = xx.DecimalStringWithDP(3);
    if (yy != "1.236") return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestNumberRange(void)
{
    RedNumberRange DegreesLongitude(-180.0, 180.0);    
    RedNumber x = 300;

    if (DegreesLongitude.IsInRange(x)) return kResultFail;

    DegreesLongitude.WrapNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return kResultFail;

    x = 300;
    DegreesLongitude.CropNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestString(void)
{
    // Case Changes
    {
        RedString x;
        x = "Hello";

        x = x.ToUpper();
        if (x == "Hello") return kResultFail;
        if (x != "HELLO") return kResultFail;

        x = x.ToLower();
        if (x == "HELLO") return kResultFail;
        if (x != "hello") return kResultFail;
    }

    // String type checks
    {
        RedString x;

        x = "qw23";
        if (!x.IsAlphaNumeric()) return kResultFail;

        x = "!@@^";
        if (x.IsAlphaNumeric()) return kResultFail;

        x = "Qwerty";
        if ( x.IsCharInString('a')) return kResultFail;
        if (!x.IsCharInString('r')) return kResultFail;

        if (x.IsEmpty()) return kResultFail;
    }

    // Inserts and appends
    {
        RedString x;

        x = "123456789";
        x.Insert(3, "qwerty");
        if (x != "123qwerty456789") return kResultFail;

        x = "123";
        x.Append("456");
        if (x != "123456") return kResultFail;

        x = "qwerty";
        int ix = 123;
        x.Append(ix);
        if (x != "qwerty123") return kResultFail;

        x = "121212121212121212121212121212121212";
        x.Append('A');
        if (x != "121212121212121212121212121212121212A") return kResultFail;
    }

    // Strip characters
    {
        RedString str;

        str = "Utter Maddness";
        str.StripChar('M');
        if (str != "Utter addness")
            return kResultFail;

        str = "ABC 123 XYZ";
        str.StripChar(' ');
        if (str != "ABC123XYZ")
            return kResultFail;
    }

    // Code has failed on a 32 character string - specific test here to ensure the end-of-string
    // character is preserved when we have two strings allocated next to each other.
    // Addition dicriminatory factor was the string starting with a "/"? Not understood.
    {
        RedString F = "/tmp/TestBasicVSILibrary_001.tml";
        RedString x = "123456789abcde0abcd12123131313ef";
        const int origFLen = F.Length();

        const int newFLen = F.Length();

        if (newFLen != origFLen)
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataType(void)
{
    RedDataType x;
    x = RedDataType::Char();

    if (!x.IsChar()) return kResultFail;

    RedDataType y = RedDataType::Num();

    if (x == y) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestVariant(void)
{
    {
        RedVariant x;
        RedString str = "qwerty";

        x = str;
        if (x.Type() != kDataTypeStr) return kResultFail;

        RedString y = "1234";

        if (x.Type() == kDataTypeStr)
        {
            y = x.StringValue();
            if (y.Type() != kDataTypeStr) return kResultFail;
            if (y != str) return kResultFail;
        }
    }

    {
        RedVariant a;
        RedVariant b;
        RedVariant c;
        RedVariant exp;

        a = "hello";
        b = " world";
        c = "test-unassigned";
        exp = "hello world";

        if (c == exp)
            return kResultFail;

        c = a + b;

        if (c != exp)
            return kResultFail;
    }

    {
        RedVariant x(1);
        RedVariant y(2.2);
        RedVariant res("test");
        RedVariant exp(3.2);

        res = x + y;

        if ( res != exp )
            return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestLinkedList(void)
{
    typedef RedLinkedList<int>         TIntList;
    typedef RedLinkedListIterator<int> TIntListIt;

    TIntList l;

    l.AddFirst(1);
    l.AddLast(2);
    l.AddLast(3);

    if (l.NumItems() != 3) return kResultFail;

    int x=0;
    if (l.FindFirst(x) == 0) return kResultFail;
    if (x != 1) return kResultFail;

    if (l.FindLast(x) == 0) return kResultFail;
    if (x != 3) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestResult(void)
{
    {
        RedResult x = kResultSuccess;

        if (x == kResultFail)    return kResultFail;
        if (x != kResultSuccess) return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestRecord(void)
{
    RedRecord x;
    RedString y("Data1");

    x.CloneAndAdd("Field1", &y);

    y = "Data2";
    x.CloneAndAdd("Field2", &y);

    RedType* p = 0;
    x.Find("Field1", p);

    if (p->Type() != kDataTypeStr) return kResultFail;
    RedString* ps = (RedString*)p;
    if (*ps != "Data1") return kResultFail;

    delete p;
    p = 0;
    ps = 0;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestEventLog(void)
{
    RedLog log;

    log.AddText("EventLogText1");
    log.AddText("EventLogText2");
    if (log.NumEvents() != 2) return kResultFail;
    if (log.IsError()) return kResultFail;

    RedLogEvent e(eErrorEvent, "ErrorText1");
    log.AddEvent(e);
    if (log.NumEvents() != 3) return kResultFail;
    if (!log.IsError()) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestSmartPtr(void)
{
    RedNumberSmartPtr x(new RedNumber(1.23));
    if (x.RefCount() != 1) return kResultFail;

    {
        RedNumberSmartPtr y;
        if (y.RefCount() != 1) return kResultFail;

        y = x;
        if (x.RefCount() != 2) return kResultFail;
        if (y.RefCount() != 2) return kResultFail;

        y->Set(1.123);
        if (!y->IsEqualTo(RedNumber(1.123)))
            return kResultFail;
    }

    if (x.RefCount() != 1) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDate(void)
{
    RedDate d;
    d.Now();

    int x = d.EightDigitInt();
    if (x < 20130000) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestTime(void)
{
//    RedTime t;
//    t.Now();
//
//    int x = t.SixDigitInt();
//
//    int y = t.Hour().GetInteger() * 10000;
//    if (x < y) return kResultFail;
//    

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// IO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestInputBuffer(void)
{
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestOutputBuffer(void)
{
    {
        RedBufferOutput outbuf;
        outbuf.SetIndent(RedString("  "));

        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedString("aaabbb")) return kResultFail;
        outbuf.Empty();

        outbuf.Append("aaa");
        outbuf.SetIndentLevel(2);
        outbuf.WriteIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedString("aaa    bbb")) return kResultFail;
        outbuf.Empty();

        RedString in = "111111\n222222";
        outbuf.SetIndentLevel(0);
        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.AppendIndented(in);
        outbuf.DecreaseIndent();
        outbuf.AppendIndented("bbb");
        if (outbuf.ExtractData() != RedString("aaa\n  111111\n  222222\nbbb")) return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




