

#include "RedTestCore.h"

namespace Red {
namespace Test {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::RunUnitTest(void)
{
    int BoolPassed        = RedTestCore::TestBoolean();
    int CharPassed        = RedTestCore::TestChar();
    int NumberPassed      = RedTestCore::TestNumber();
    int NumberRangePassed = RedTestCore::TestNumberRange();
    int StringPassed      = RedTestCore::TestString();
    int DataTypePassed    = RedTestCore::TestDataType();
    int VariantPassed     = RedTestCore::TestVariant();
    int RecordPassed      = RedTestCore::TestRecord();
    int LinkedListPassed  = RedTestCore::TestLinkedList();
    int ResultPassed      = RedTestCore::TestResult();
    int EventLogPassed    = RedTestCore::TestEventLog();
    int SmartPtrPassed    = RedTestCore::TestSmartPtr();
    int DatePassed        = RedTestCore::TestDate();
    int TimePassed        = RedTestCore::TestTime();

    if(!RedTestCore::TestOutputBuffer()) return 0;

    int OverallPassed = 0;

    if ((BoolPassed        == 1) &&
        (CharPassed        == 1) &&
        (NumberPassed      == 1) &&
        (NumberRangePassed == 1) &&
        (StringPassed      == 1) &&
        (DataTypePassed    == 1) &&
        (VariantPassed     == 1) &&
        (ResultPassed      == 1) &&
        (LinkedListPassed  == 1) &&
        (RecordPassed      == 1) &&
        (EventLogPassed    == 1) &&
        (SmartPtrPassed    == 1) &&
        (DatePassed        == 1) &&
        (TimePassed        == 1))
    {
        OverallPassed = 1;
    }

    return OverallPassed;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestBoolean(void)
{
    RedBoolean x;
    x.SetYes();
    if (!x.IsYes()) return 0;

    RedBoolean y;
    y.SetNo();
    if (!y.IsNo()) return 0;

    x = y;
    if (x != y) return 0;


    RedBoolean* p = dynamic_cast<RedBoolean*>(x.Clone());
    p->SetFalse();
    if (p->IsTrue()) return 0;

    if (p->Type() != RedDataType::Bool()) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestChar(void)
{
    RedChar a = RedChar(0);
    RedChar b = RedChar('A');
    RedChar c = RedChar('{');

    if (a.IsPrintable()) return 0;
    if (!b.IsAlpha())    return 0;
    if (!c.IsBracket())  return 0;

    a.Set(b);
    if (!a.IsAlpha())    return 0;

    c = a;
    if (!a.IsAlpha())    return 0;

    c = 'k';
    if (!a.IsAlpha())    return 0;

    c = 67;
    if (!a.IsAlpha())    return 0;

    a = 'a';
    b = 'b';
    if (a == b) return 0;

    a = b;
    if (a != b) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestNumber(void)
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
    if (yy != "1.236") return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestNumberRange(void)
{
    RedNumberRange DegreesLongitude(-180.0, 180.0);    
    RedNumber x = 300;

    if (DegreesLongitude.IsInRange(x)) return 0;

    DegreesLongitude.WrapNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return 0;

    x = 300;
    DegreesLongitude.CropNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestString(void)
{
    // Case Changes
    {
        RedString x;
        x = "Hello";

        x = x.ToUpper();
        if (x == "Hello") return 0;
        if (x != "HELLO") return 0;

        x = x.ToLower();
        if (x == "HELLO") return 0;
        if (x != "hello") return 0;
    }

    // String type checks
    {
        RedString x;

        x = "qw23";
        if (!x.IsAlphaNumeric()) return 0;

        x = "!@@^";
        if (x.IsAlphaNumeric()) return 0;

        x = "Qwerty";
        if ( x.IsCharInString('a')) return 0;
        if (!x.IsCharInString('r')) return 0;

        if (x.IsEmpty()) return 0;
    }

    // Inserts and appends
    {
        RedString x;

        x = "123456789";
        x.Insert(3, "qwerty");
        if (x != "123qwerty456789") return 0;

        x = "123";
        x.Append("456");
        if (x != "123456") return 0;

        x = "qwerty";
        int ix = 123;
        x.Append(ix);
        if (x != "qwerty123") return 0;

        x = "121212121212121212121212121212121212";
        x.Append('A');
        if (x != "121212121212121212121212121212121212A") return 0;
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
            return 0;
    }

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestDataType(void)
{
    RedDataType x;
    x = RedDataType::Char();

    if (!x.IsChar()) return 0;

    RedDataType y = RedDataType::Num();

    if (x == y) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestVariant(void)
{
    {
        RedVariant x;
        RedString str = "qwerty";

        x = str;
        if (x.Type() != kDataTypeStr) return 0;

        RedString y = "1234";

        if (x.Type() == kDataTypeStr)
        {
            y = x.StringValue();
            if (y.Type() != kDataTypeStr) return 0;
            if (y != str) return 0;
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
            return 0;

        c = a + b;

        if (c != exp)
            return 0;
    }

    {
        RedVariant x(1);
        RedVariant y(2.2);
        RedVariant res("test");
        RedVariant exp(3.2);

        res = x + y;

        if ( res != exp )
            return 0;
    }

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestLinkedList(void)
{
    typedef RedLinkedList<int>         TIntList;
    typedef RedLinkedListIterator<int> TIntListIt;

    TIntList l;

    l.AddFirst(1);
    l.AddLast(2);
    l.AddLast(3);

    if (l.NumItems() != 3) return 0;

    int x=0;
    if (l.FindFirst(x) == 0) return 0;
    if (x != 1) return 0;

    if (l.FindLast(x) == 0) return 0;
    if (x != 3) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestResult(void)
{
    {
        RedResult x = kResultSuccess;

        if (x == kResultFail)    return 0;
        if (x != kResultSuccess) return 0;
    }
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestRecord(void)
{
    RedRecord x;
    RedString y("Data1");

    x.CloneAndAdd("Field1", &y);

    y = "Data2";
    x.CloneAndAdd("Field2", &y);

    RedType* p = 0;
    x.Find("Field1", p);

    if (p->Type() != kDataTypeStr) return 0;
    RedString* ps = (RedString*)p;
    if (*ps != "Data1") return 0;

    delete p;
    p = 0;
    ps = 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestEventLog(void)
{
    RedLog log;

    log.AddText("EventLogText1");
    log.AddText("EventLogText2");
    if (log.NumEvents() != 2) return 0;
    if (log.IsError()) return 0;

    RedLogEvent e(eErrorEvent, "ErrorText1");
    log.AddEvent(e);
    if (log.NumEvents() != 3) return 0;
    if (!log.IsError()) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestSmartPtr(void)
{
    RedNumberSmartPtr x(new RedNumber(1.23));
    if (x.RefCount() != 1) return 0;

    {
        RedNumberSmartPtr y;
        if (y.RefCount() != 1) return 0;

        y = x;
        if (x.RefCount() != 2) return 0;
        if (y.RefCount() != 2) return 0;

        y->Set(1.123);
        if (!y->IsEqualTo(RedNumber(1.123)))
            return 0;
    }

    if (x.RefCount() != 1) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestDate(void)
{
    RedDate d;
    d.Now();

    int x = d.EightDigitInt();
    if (x < 20130000) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestTime(void)
{
//    RedTime t;
//    t.Now();
//
//    int x = t.SixDigitInt();
//
//    int y = t.Hour().GetInteger() * 10000;
//    if (x < y) return 0;
//    

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// IO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestInputBuffer(void)
{
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTestCore::TestOutputBuffer(void)
{
    {
        RedBufferOutput outbuf;
        outbuf.SetIndent(RedString("  "));

        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedString("aaabbb")) return 0;
        outbuf.Empty();

        outbuf.Append("aaa");
        outbuf.SetIndentLevel(2);
        outbuf.WriteIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedString("aaa    bbb")) return 0;
        outbuf.Empty();

        RedString in = "111111\n222222";
        outbuf.SetIndentLevel(0);
        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.AppendIndented(in);
        outbuf.DecreaseIndent();
        outbuf.AppendIndented("bbb");
        if (outbuf.ExtractData() != RedString("aaa\n  111111\n  222222\nbbb")) return 0;
    }

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red




