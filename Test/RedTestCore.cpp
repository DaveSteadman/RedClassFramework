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
#include "RedCoreNamespace.h"

#include <stdio.h>
#include <stdlib.h>

using namespace Red::Core;

namespace Red {
namespace Test {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTestCore::RunUnitTest(RedLog& log)
{
    if (RedTestCore::TestBoolean().IsFail())      { log.AddErrorEvent("Core Unit Test: TestBoolean Failed");      return; }
    if (RedTestCore::TestChar().IsFail())         { log.AddErrorEvent("Core Unit Test: TestChar Failed");         return; }
    if (RedTestCore::TestDataType().IsFail())     { log.AddErrorEvent("Core Unit Test: TestDataType Failed");     return; }
    if (RedTestCore::TestDate().IsFail())         { log.AddErrorEvent("Core Unit Test: TestDate Failed");         return; }
    if (RedTestCore::TestEventLog().IsFail())     { log.AddErrorEvent("Core Unit Test: TestEventLog Failed");     return; }
    if (RedTestCore::TestLinkedList().IsFail())   { log.AddErrorEvent("Core Unit Test: TestLinkedList Failed");   return; }
    if (RedTestCore::TestNumber().IsFail())       { log.AddErrorEvent("Core Unit Test: TestNumber Failed");       return; }
    if (RedTestCore::TestNumberRange().IsFail())  { log.AddErrorEvent("Core Unit Test: TestNumberRange Failed");  return; }
    if (RedTestCore::TestOutputBuffer().IsFail()) { log.AddErrorEvent("Core Unit Test: TestOutputBuffer Failed"); return; }
    if (RedTestCore::TestRecord().IsFail())       { log.AddErrorEvent("Core Unit Test: TestRecord Failed");       return; }
    if (RedTestCore::TestFlexRecord().IsFail())   { log.AddErrorEvent("Core Unit Test: TestFlexRecord Failed");   return; }
    if (RedTestCore::TestResult().IsFail())       { log.AddErrorEvent("Core Unit Test: TestResult Failed");       return; }
    if (RedTestCore::TestSmartPtr().IsFail())     { log.AddErrorEvent("Core Unit Test: TestSmartPtr Failed");     return; }
    if (RedTestCore::TestString().IsFail())       { log.AddErrorEvent("Core Unit Test: TestString Failed");       return; }
    if (RedTestCore::TestTime().IsFail())         { log.AddErrorEvent("Core Unit Test: TestTime Failed");         return; }
    if (RedTestCore::TestVariant().IsFail())      { log.AddErrorEvent("Core Unit Test: TestVariant Failed");      return; }

    log.AddText("Core Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestBoolean(void)
{
    // Test basic operation
    {
        RedBoolean x;
        x.SetTrue();
        if (!x.IsTrue()) return kResultFail;

        RedBoolean y;
        y.SetFalse();
        if (!y.IsFalse()) return kResultFail;

        x = y;
        if (x != y) return kResultFail;
    }

    // Test cloning
    {
        RedBoolean x(true);
        RedBoolean* p = dynamic_cast<RedBoolean*>(x.Clone());
        if (p->IsFalse()) return kResultFail;

        if (p->Type() != RedDataType::Bool())
        {
            delete p;
            return kResultFail;
        }
        delete p;
    }
    
    // Test Logic statements
    {
        RedBoolean a = kBoolTRUE;
        RedBoolean b = kBoolTRUE;
        RedBoolean c;

        c = RedBoolean::OR(a,b);
        if (c.IsFalse()) return kResultFail;
        c = RedBoolean::AND(a,b);
        if (c.IsFalse()) return kResultFail;
        c = RedBoolean::NAND(a,b);
        if (c.IsTrue()) return kResultFail;
        c = RedBoolean::XOR(a,b);
        if (c.IsTrue()) return kResultFail;
    }
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
    // Comparisons
    {
        RedNumber t1 = 1.0000000001;
        if (!t1.IsEqualToWithinTollerance(1, 0.001)) return kResultFail;
    }

    // String representations
    {
        RedNumber z1(12.345);
        RedString zstr1 = z1.DecimalString();
        if (zstr1 != "12.345000") return kResultFail;

        RedNumber z2(12345);
        RedString zstr2 = z2.DecimalString();
        if (zstr2 != "12345") return kResultFail;
    }
    {
        RedNumber abc1(12);
        RedString abcstr1 = abc1.DecimalStringWithDP(2);
        if (abcstr1 != "12.00") return kResultFail;

        RedNumber abc2(12.3456);
        RedString abcstr2 = abc2.DecimalStringWithDP(2);
        if (abcstr2 != "12.35") return kResultFail;

        RedNumber abc3(12.34);
        RedString abcstr3 = abc3.DecimalStringWithDP(4);
        if (abcstr3 != "12.3400") return kResultFail;
    }
    {
        RedNumber abc1(12);
        RedString abcstr1 = abc1.DecimalStringWithMinDigitsAndDP(3, 2);
        if (abcstr1 != "12.00") return kResultFail;

        RedNumber abc2(12.3);
        RedString abcstr2 = abc2.DecimalStringWithMinDigitsAndDP(5, 0);
        if (abcstr2 != "00012") return kResultFail;

        RedNumber abc3(12.3);
        RedString abcstr3 = abc3.DecimalStringWithMinDigitsAndDP(7, 3);
        if (abcstr3 != "012.300") return kResultFail;
    }

    // Reading strings
    {
        RedNumber x;
        RedNumber y;
        RedString strNum;

        strNum.Set("1.234");
        y.SetDecimalString(strNum);
        if (y != 1.234) return kResultFail;

        strNum.Set("-1.234");
        y.SetDecimalString(strNum);
        if (y != -1.234) return kResultFail;
    }

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

    
    RedNumberRange FullCircleDegrees(0.0, 360.0);
    RedNumberRange FullCircleRadians(0.0, 2 * pi);
    RedNumber angle = 90.0;
    
    RedNumber ftr(FullCircleDegrees.FractionThroughRange(angle));
    if (ftr != 0.25) return kResultFail;
 
    // RedNumber angleRads = RedNumberRange::RescaleNumber(angle, FullCircleDegrees, FullCircleRadians);
    // if (angleRads != half_pi) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestString(void)
{
    // Allocation sizes
    {
        unsigned b1 = 0;
        unsigned b2 = 0;

        b1 = RedString::NumBlocksForSize(15);
        b2 = RedString::SizeForNumBlocks(b1);
        if (b1 != 1)                        return kResultFail;
        if (b2 != kRedStringAllocBlockSize) return kResultFail;

        b1 = RedString::NumBlocksForSize(31);
        b2 = RedString::SizeForNumBlocks(b1);
        if (b1 != 1)                          return kResultFail;
        if (b2 != 1*kRedStringAllocBlockSize) return kResultFail;

        b1 = RedString::NumBlocksForSize(32);
        b2 = RedString::SizeForNumBlocks(b1);
        if (b1 != 2)                          return kResultFail;
        if (b2 != 2*kRedStringAllocBlockSize) return kResultFail;

        b1 = RedString::NumBlocksForSize(319);
        b2 = RedString::SizeForNumBlocks(b1);
        if (b1 != 10)                          return kResultFail;
        if (b2 != 10*kRedStringAllocBlockSize) return kResultFail;
    }

    // Construction and calls
    {
        RedString x;
        char ch = x.LastChar();

        if (ch != '\0') return kResultFail;
    }

    // Set
    {
        RedString x("1234567890");
        if (x.FirstContentIndex() != 0)                          return kResultFail;
        if (x.LastContentIndex()  != 9)                          return kResultFail;
        if (x.AllocSize()         != kRedStringAllocBlockSize)   return kResultFail;

        x.Set("1234567890123456789012345678901");
        if (x.LastContentIndex() != 30)                          return kResultFail;
        if (x.AllocSize()        != kRedStringAllocBlockSize)    return kResultFail;

        x.Set("12345678901234567890123456789012");
        if (x.LastContentIndex() != 31)                          return kResultFail;
        if (x.AllocSize()        != 2*kRedStringAllocBlockSize)  return kResultFail;
    }

    // Append Char
    {
        RedString x("12345");
        x.Append('Q');
        if (x.LastContentIndex() != 5) return kResultFail;

        x.Set("123456789012345678901234567890");
        x.Append('X');
        if (x.LastContentIndex() != 30) return kResultFail;
        if (x.AllocSize()        != kRedStringAllocBlockSize) return kResultFail;

        x.Set("1234567890123456789012345678901");
        x.Append('X');
        if (x.LastContentIndex() != 31) return kResultFail;
        if (x.AllocSize()        != 2*kRedStringAllocBlockSize) return kResultFail;
    }

    // Append Str
    {
        RedString x1("123");
        x1.Append("ABC");
        if (x1 != "123ABC") return kResultFail;
        if (x1.ContentSize() != 6) return kResultFail;

        x1 = "ABC";
        x1.Append("\n");
        if (x1 != "ABC\n") return kResultFail;

        x1 = "1234567890123456789012345678901";
        x1.Append("\n");
        if (x1 != "1234567890123456789012345678901\n") return kResultFail;
    }

    // Delete Char
    {
        RedString x1("11233");
        x1.DelCharsAtIndex(2,1);
        if (x1 != "1133") return kResultFail;

        x1.Set("1122222");
        x1.DelCharsAtIndex(2, 20);
        if (x1 != "11") return kResultFail;

        x1.Set("1");
        x1.DelCharsAtIndex(0,1);
        if (!x1.IsEmpty()) return kResultFail;
    }

    // Insert Char
    {
        RedString x1("abc123");
        x1.InsertAtIndex(3,'A');
        if (x1 != "abcA123") return kResultFail;
    }

    // Insert Str
    {
        RedString x1("abc123");
        x1.InsertAtIndex(3, "ABC");
        if (x1 != "abcABC123") return kResultFail;

        x1 = "123";
        x1.InsertAtIndex(0, "ABC");
        if (x1 != "ABC123") return kResultFail;
    }

    // SubStr
    {
        RedString x1("123456789");
        RedString x2;

        x2 = x1.SubStr(2, 3);
        if (x2 != "345") return kResultFail;

        x2 = x1.SubStr(0, 3);
        if (x2 != "123") return kResultFail;

        x2 = x1.SubStr(6, 5);
        if (x2 != "789") return kResultFail;
    }

    // Numlines & LineAtNum
    {
        RedString x1 = "123\nabc\nQWE";
        if (x1.NumLines() != 3) return kResultFail;

        RedString x2;
        if (!x1.LineAtNum(2, x2)) return kResultFail;
        if (x2 != "abc") return kResultFail;

        if (!x1.LineAtNum(1, x2)) return kResultFail;
        if (x2 != "123") return kResultFail;

        if (x1.LineAtNum(0, x2)) return kResultFail;
    }

    // Operators
    {
        RedString x1 = "abc";
        RedString x2;
        RedChar   c1 = '1';

        x1 = "abc";
        x2.Empty();
        c1 = '1';

        x2 = x1 + c1;
        if (x2 != "abc1") return kResultFail;

        x1.Empty();
        x2.Empty();
        c1 = '1';

        x2 = x1 + c1;
        if (x2 != "1") return kResultFail;
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

    RedType* p = NULL;
    x.Find("Field1", p);

    if ((p == NULL) || (p->Type() != kDataTypeStr)) return kResultFail;
    RedString* ps = (RedString*)p;
    if (*ps != "Data1") return kResultFail;

    delete p;
    p = NULL;
    ps = NULL;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestFlexRecord(void)
{
    // Define the record for the whole test
    RedFlexRecord fRec;

    // Add data items within limited scope
    {
        RedString IndexStr("indexqwerty");
        RedString DataStr("dataqwerty");

        fRec.CloneAndAdd(&IndexStr, &DataStr);
    }
    {
        RedNumber indexNum(3);
        RedString Datanum("data3");

        fRec.CloneAndAdd(&indexNum, &Datanum);
    }

    // Find objects
    {
        RedString FindStr("indexqwerty");
        RedType*  FindData = NULL;

        RedType* FindIndex = dynamic_cast<RedType*>(&FindStr);

        if (!fRec.Find(FindIndex, FindData))
            return kResultFail;
    }


//    {
//        RedNumber toFindNum(3);
//        RedType* pdata = NULL;
//        fRec.Find(&toFindNum, pdata);
//
//        if (pdata!=NULL)
//        {
//            if (pdata->Type()==kDataTypeStr)
//            {
//                RedString* pstr = dynamic_cast<RedString*>(pdata);
//
//                int a = pstr->Length();
//            }
//        }
//
//    }


    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestEventLog(void)
{
    RedLog log;

    log.AddText("EventLogText1");
    log.AddText("EventLogText2");
    if (log.NumEvents() != 2) return kResultFail;
    if (log.ContainsError()) return kResultFail;

    RedLogEvent e(eErrorEvent, "ErrorText1");
    log.AddEvent(e);
    if (log.NumEvents() != 3) return kResultFail;
    if (!log.ContainsError()) return kResultFail;

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
    RedDate d(2021,10,10);

    unsigned x = d.EightDigitDate();
    if (x != 20211010) return kResultFail;

    unsigned x2 = d.SixDigitDate();
    if (x2 != 211010) return kResultFail;

    unsigned x3 = d.TwoDigitYear();
    if (x3 != 21) return kResultFail;

    RedString xstr = d.DateString();
    if (xstr != "2021/10/10") return kResultFail;

    RedString xstr2 = d.SixDigitDateString();
    if (xstr2 != "211010") return kResultFail;

    RedString xstr3 = d.EightDigitDateString();
    if (xstr3 != "20211010") return kResultFail;

    RedDate dateToday1 = RedDate::Today();
    RedDate dateToday2 = RedDate::Today();
    if (dateToday1 != dateToday2) return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestTime(void)
{
    RedTime t(12, 0, 0.0);

    RedString xstr = t.TimeString();
    if (xstr != "12:00:00.00") return kResultFail;

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
    // Test appending and indents
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

    // Test stream operator
    {
        RedBufferOutput outbuf;
        RedNumber zz(12);
        RedString yy("qwqw");
        outbuf << 34 << "\n " << zz << " " << yy;
        if (outbuf.ExtractData() != RedString("34\n 12 qwqw")) return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




