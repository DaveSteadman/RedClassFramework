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
    // Test Core Classes
    if (RedTestCore::TestDataType().IsFail())     { log.AddErrorEvent("Core Unit Test: TestDataType Failed");      }
 
    // Test Data Types
    if (RedTestCore::TestDataBoolean().IsFail())  { log.AddErrorEvent("Core Unit Test: TestDataBoolean Failed");   }
    if (RedTestCore::TestDataChar().IsFail())     { log.AddErrorEvent("Core Unit Test: TestDataChar Failed");      }
    if (RedTestCore::TestDataList().IsFail())     { log.AddErrorEvent("Core Unit Test: TestDataList Failed");      }
    if (RedTestCore::TestDataNumber().IsFail())   { log.AddErrorEvent("Core Unit Test: TestDataNumber Failed");    }
    if (RedTestCore::TestDataRecord().IsFail())   { log.AddErrorEvent("Core Unit Test: TestDataRecord Failed");    }
    if (RedTestCore::TestDataString().IsFail())   { log.AddErrorEvent("Core Unit Test: TestDataString Failed");    }
    if (RedTestCore::TestDataVariant().IsFail())  { log.AddErrorEvent("Core Unit Test: TestDataVariant Failed");   }

    // Test Time Types
    if (RedTestCore::TestTime().IsFail())         { log.AddErrorEvent("Core Unit Test: TestTime Failed");          }
    if (RedTestCore::TestDate().IsFail())         { log.AddErrorEvent("Core Unit Test: TestDate Failed");          }

    // Test Collections
    if (RedTestCore::TestLinkedList().IsFail())   { log.AddErrorEvent("Core Unit Test: TestLinkedList Failed");    }

    // Test Tokens
    if (RedTestCore::TestTokens().IsFail())       { log.AddErrorEvent("Core Unit Test: TestTokens Failed");        }

    // Test Misc Types
    if (RedTestCore::TestEventLog().IsFail())     { log.AddErrorEvent("Core Unit Test: TestEventLog Failed");      }
    if (RedTestCore::TestNumberRange().IsFail())  { log.AddErrorEvent("Core Unit Test: TestNumberRange Failed");   }
    if (RedTestCore::TestOutputBuffer().IsFail()) { log.AddErrorEvent("Core Unit Test: TestOutputBuffer Failed");  }
    if (RedTestCore::TestResult().IsFail())       { log.AddErrorEvent("Core Unit Test: TestResult Failed");        }

    if (!log.ContainsError())
        log.AddText("Core Unit Test: Passed");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Core classes
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
// Test Data types
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataBoolean(void)
{
    // Test basic operation
    {
        RedDataBoolean x;
        x.SetTrue();
        if (!x.IsTrue()) return kResultFail;

        RedDataBoolean y;
        y.SetFalse();
        if (!y.IsFalse()) return kResultFail;

        x = y;
        if (x != y) return kResultFail;
    }

    // Test cloning
    {
        RedDataBoolean x(true);
        RedDataBoolean* p = dynamic_cast<RedDataBoolean*>(x.Clone());
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
        RedDataBoolean a = kBoolTRUE;
        RedDataBoolean b = kBoolTRUE;
        RedDataBoolean c;

        c = RedDataBoolean::OR(a,b);
        if (c.IsFalse()) return kResultFail;
        c = RedDataBoolean::AND(a,b);
        if (c.IsFalse()) return kResultFail;
        c = RedDataBoolean::NAND(a,b);
        if (c.IsTrue()) return kResultFail;
        c = RedDataBoolean::XOR(a,b);
        if (c.IsTrue()) return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataChar(void)
{
    {
        RedDataChar a = RedDataChar(0);
        RedDataChar b = RedDataChar('A');
        RedDataChar c = RedDataChar('{');

        if (a.IsPrintable()) return kResultFail;
        if (!b.IsAlpha())    return kResultFail;
        if (!c.IsBracket())  return kResultFail;

        a.Set(b);
        if (!a.IsAlpha()) return kResultFail;

        c = a;
        if (!a.IsAlpha()) return kResultFail;

        c = 'k';
        if (!a.IsAlpha()) return kResultFail;

        c = 67;
        if (!a.IsAlpha()) return kResultFail;

        a = 'a';
        b = 'b';
        if (a == b) return kResultFail;
        a = b;
        if (a != b) return kResultFail;
    }
    {
        RedDataChar a('0');
        RedDataChar b('4');
        RedDataChar c('9');
        RedDataChar x('x');

        if (!a.IsDecimalNumber())    return kResultFail;
        if (a.IntFromCharNum() != 0) return kResultFail;

        if (!b.IsDecimalNumber())    return kResultFail;
        if (b.IntFromCharNum() != 4) return kResultFail;

        if (!c.IsDecimalNumber())    return kResultFail;
        if (c.IntFromCharNum() != 9) return kResultFail;

        if (x.IsDecimalNumber())     return kResultFail;
        if (x.IntFromCharNum() != 0) return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataList(void)
{
    // Basic add items list
    {
        RedDataList cList;

        cList.AddLastByValue(123);
        cList.AddLastByValue(234);
        cList.DelAtIndex(0);

        RedDataNumber* pNum = dynamic_cast<RedDataNumber*>(cList.PtrForIndex(0));
        if (*pNum != 234) return kResultFail;
    }

    // Basic create sized list
    {
        RedDataList cList(100, kDataTypeNum);
        if (cList.NumItems() != 100) return kResultFail;
        RedDataNumber* pNum50 = dynamic_cast<RedDataNumber*>(cList.PtrForIndex(50));
        if (pNum50 == NULL) return kResultFail;
        if (pNum50->Type() != kDataTypeNum) return kResultFail;
    }

    // List copying
    {
        RedDataList cList;

        cList.AddLastByValue(12);
        cList.AddLastByValue(false);
        cList.AddLastByValue("qwerty");

        RedDataList cList2;
        cList2 = cList;

        if (cList2.NumItems() != 3) return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataNumber(void)
{
    // Comparisons
    {
        RedDataNumber t1 = 1.0000000001;
        if (!t1.IsEqualToWithinTollerance(1, 0.001)) return kResultFail;
    }

    // StringFromNumber
    {
        RedDataString strNum;
        RedDataNumber z1(12.345);
        strNum = RedDataActions::StringFromNumber(z1);
        if (strNum != "12.345000") return kResultFail;

        RedDataNumber z2(12345);
        strNum = RedDataActions::StringFromNumber(z2);
        if (strNum != "12345") return kResultFail;
    }

    // StringFromDoubleWithMinDigits
    {
        RedDataString strNum;
        strNum = RedDataActions::StringFromDoubleWithDP(13.123, 10);
        if (strNum != "13.1230000000") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithDP(13.123, 4);
        if (strNum != "13.1230") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithDP(13.123, 1);
        if (strNum != "13.1") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithDP(13.183, 1);
        if (strNum != "13.2") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithDP(13.123, 0);
        if (strNum != "13") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithDP(13.888, 0);
        if (strNum != "14") return kResultFail;
    }

    // StringFromDoubleWithMinDigitsAndDP
    {
        RedDataString strNum;
        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.123, 4, 4);
        if (strNum != "0013.1230") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.123, 1, 1);
        if (strNum != "13.1") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.466, 3, 1);
        if (strNum != "013.5") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.466, 3, 0);
        if (strNum != "013") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.466, 0, 0);
        if (strNum != "13") return kResultFail;

        strNum = RedDataActions::StringFromDoubleWithMinDigitsAndDP(13.776, 0, 0);
        if (strNum != "14") return kResultFail;
    }

    // Hexadecimal strings
    {
        RedDataString strNum;
        strNum = RedDataActions::HexadecimalStringFromInt(12);
        if (strNum != "0xc") return kResultFail;

        strNum = RedDataActions::HexadecimalStringFromIntWithMinDigits(12, 4);
        if (strNum != "0x000c") return kResultFail;

        strNum = RedDataActions::HexadecimalStringFromIntWithMinDigits(32000, 4);
        if (strNum != "0x7d00") return kResultFail;
    }

    // Reading strings
    {
        RedDataNumber y;
        RedDataString strNum;

        strNum.Set("1.234");
        y = RedDataActions::NumberFromString(strNum);
        if (y != 1.234) return kResultFail;

        strNum.Set("-1.234");
        y = RedDataActions::NumberFromString(strNum);
        if (y != -1.234) return kResultFail;

        y = RedDataActions::NumberFromString("121212");
        if (y != 121212) return kResultFail;
    }

    // New format string
    {
        RedDataString cStr = RedDataActions::StringFromInt(12);
        if (cStr != "12") return kResultFail;

        cStr = RedDataActions::StringFromDouble(12.123);
        if (cStr != "12.123000") return kResultFail;

        cStr = RedDataActions::StringFromDoubleWithDP(12.123, 3);
        if (cStr != "12.123") return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataRecord(void)
{
    {
        RedDataRecord x;

        x.AddByPtr("Field1", RedDataNumber(12).Clone());
        x.AddByPtr("Field2", RedDataString("str12").Clone());
        x.AddByPtr("Field3", RedDataBoolean(true).Clone());
        x.AddByPtr("Field4", RedDataNumber(345.5).Clone());
        if (x.NumItems() != 4) return kResultFail;

        x.Del("Field1");

        RedDataChar c('q');
        x.CloneAndAdd("Field5", &c);

        RedDataType t1 = x.TypeForName("Field3");
        RedDataBoolean* pB = dynamic_cast<RedDataBoolean*>(x.PtrForName("Field3"));
        RedDataNumber* pErr = dynamic_cast<RedDataNumber*>(x.PtrForName("Field3"));

        RedDataBoolean* pB2 = dynamic_cast<RedDataBoolean*>(x.CreateAddReturn("FieldBool", kDataTypeBool));
        pB2->SetTrue();

        RedDataVariant* pV = dynamic_cast<RedDataVariant*>(x.CreateAddReturn("FieldBool", kDataTypeVariant));
        *pV = "qq";
        *pV = 1234;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDataString(void)
{
    // Allocation sizes
    {
        unsigned b1 = 0;
        unsigned b2 = 0;

        b1 = RedDataString::NumBlocksForSize(15);
        b2 = RedDataString::SizeForNumBlocks(b1);
        if (b1 != 1)                     return kResultFail;
        if (b2 != kStringAllocBlockSize) return kResultFail;

        b1 = RedDataString::NumBlocksForSize(31);
        b2 = RedDataString::SizeForNumBlocks(b1);
        if (b1 != 1)                       return kResultFail;
        if (b2 != 1*kStringAllocBlockSize) return kResultFail;

        b1 = RedDataString::NumBlocksForSize(32);
        b2 = RedDataString::SizeForNumBlocks(b1);
        if (b1 != 2)                       return kResultFail;
        if (b2 != 2*kStringAllocBlockSize) return kResultFail;

        b1 = RedDataString::NumBlocksForSize(319);
        b2 = RedDataString::SizeForNumBlocks(b1);
        if (b1 != 10)                       return kResultFail;
        if (b2 != 10*kStringAllocBlockSize) return kResultFail;
    }

    // Construction and calls
    {
        RedDataString x;
        char ch = x.LastChar();

        if (ch != '\0') return kResultFail;
    }

    // Set
    {
        RedDataString x("1234567890");
        if (x.FirstContentIndex() != 0)                       return kResultFail;
        if (x.LastContentIndex()  != 9)                       return kResultFail;
        if (x.AllocSize()         != kStringAllocBlockSize)   return kResultFail;

        x.Set("1234567890123456789012345678901");
        if (x.LastContentIndex() != 30)                       return kResultFail;
        if (x.AllocSize()        != kStringAllocBlockSize)    return kResultFail;

        x.Set("12345678901234567890123456789012");
        if (x.LastContentIndex() != 31)                       return kResultFail;
        if (x.AllocSize()        != 2*kStringAllocBlockSize)  return kResultFail;
    }

    // Append Char
    {
        RedDataString x("12345");
        x.Append('Q');
        if (x.LastContentIndex() != 5) return kResultFail;

        x.Set("123456789012345678901234567890");
        x.Append('X');
        if (x.LastContentIndex() != 30)                    return kResultFail;
        if (x.AllocSize()        != kStringAllocBlockSize) return kResultFail;

        x.Set("1234567890123456789012345678901");
        x.Append('X');
        if (x.LastContentIndex() != 31)                      return kResultFail;
        if (x.AllocSize()        != 2*kStringAllocBlockSize) return kResultFail;
    }

    // Append Str
    {
        RedDataString x1("123");
        x1.Append("ABC");
        if (x1 != "123ABC")        return kResultFail;
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
        RedDataString x1("11233");
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
        RedDataString x1("abc123");
        x1.InsertAtIndex(3,'A');
        if (x1 != "abcA123") return kResultFail;
    }

    // Insert Str
    {
        RedDataString x1("abc123");
        x1.InsertAtIndex(3, "ABC");
        if (x1 != "abcABC123") return kResultFail;

        x1 = "123";
        x1.InsertAtIndex(0, "ABC");
        if (x1 != "ABC123") return kResultFail;
    }

    // SubStr
    {
        RedDataString x1("123456789");
        RedDataString x2;

        x2 = x1.SubStr(2, 3);
        if (x2 != "345") return kResultFail;

        x2 = x1.SubStr(0, 3);
        if (x2 != "123") return kResultFail;

        x2 = x1.SubStr(6, 5);
        if (x2 != "789") return kResultFail;
    }

    // Numlines & LineAtNum
    {
        RedDataString x1 = "123\nabc\nQWE";
        if (x1.NumLines() != 3) return kResultFail;

        RedDataString x2;
        if (!x1.LineAtNum(2, x2)) return kResultFail;
        if (x2 != "abc")          return kResultFail;

        if (!x1.LineAtNum(1, x2)) return kResultFail;
        if (x2 != "123")          return kResultFail;

        if (x1.LineAtNum(0, x2)) return kResultFail;
    }

    // Prefix
    {
        RedDataString x1;

        x1 = "RedString";
        x1.DelPrefix("Red");
        if (x1 != "String") return kResultFail;

        x1 = "123456789abc";
        x1.DelPrefix("124");
        if (x1 != "123456789abc") return kResultFail;

        x1.DelSuffix("abc");
        if (x1 != "123456789") return kResultFail;
    }

    // Operators
    {
        RedDataString x1 = "abc";
        RedDataString x2;
        RedDataChar   c1 = '1';

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

RedResult RedTestCore::TestDataVariant(void)
{
    {
        RedDataVariant x;
        RedDataString str = "qwerty";

        x = str;
        if (x.Type() != kDataTypeStr) return kResultFail;

        RedDataString y = "1234";

        if (x.Type() == kDataTypeStr)
        {
            y = x.StringValue();
            if (y.Type() != kDataTypeStr) return kResultFail;
            if (y != str)                 return kResultFail;
        }
    }

    {
        RedDataVariant a;
        RedDataVariant b;
        RedDataVariant c;
        RedDataVariant exp;

        a = "hello";
        b = " world";
        c = "test-unassigned";
        exp = "hello world";

        if (c == exp) return kResultFail;
        c = a + b;
        if (c != exp) return kResultFail;
    }

    {
        RedDataVariant x(1);
        RedDataVariant y(2.2);
        RedDataVariant res("test");
        RedDataVariant exp(3.2);

        res = x + y;
        if ( res != exp ) return kResultFail;
    }

    {
        RedDataVariant x(1);

        if (!x.Type().IsNum())         return kResultFail;
        if (x.Type() != kDataTypeNum)  return kResultFail;

        RedDataString  xstr  = x.StringValue();
        RedDataNumber  xnum  = x.NumberValue();
        RedDataBoolean xbool = x.BoolValue();

        if (xstr != "1")        return kResultFail;
        if (xnum != 1)          return kResultFail;
        if (xbool != kBoolTRUE) return kResultFail;
    }

    {
        RedDataVariant trans1;
        trans1 = "123.456";

        RedDataNumber x = trans1.DoubleValue();
        RedDataNumber y = trans1.IntegerValue();

        if (!x.IsEqualTo(123.456)) return kResultFail;
        if (!y.IsEqualTo(123))     return kResultFail;

        trans1 = 123;
        RedDataString z = trans1.StringValue();
        if (z != "123") return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Parsing
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestTokens(void)
{
    {
        RedDataString strTest("+ = +=");

        RedTokenBuffer tokBuf;
        int iCreateResult = RedTokenFactory::CreateTokens(strTest, tokBuf);

        RedToken t1 = tokBuf.GetToken();
        if (!t1.Type().IsSymbol())               return kResultFail;
        if (!t1.Predef().IsSymbolOperatorPlus()) return kResultFail;

        RedToken t2 = tokBuf.GetToken();
        if (!t2.Type().IsSymbol())               return kResultFail;
        if (!t2.Predef().IsSymbolAssignEqual())  return kResultFail;

        RedToken t3 = tokBuf.GetToken();
        if (!t3.Type().IsSymbol())               return kResultFail;
        if (!t3.Predef().IsSymbolAssignPlus())   return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Time Classes
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestDate(void)
{
    {
        RedDate d(2021, 10, 10);

        unsigned x = d.EightDigitDate();
        if (x != 20211010) return kResultFail;

        unsigned x2 = d.SixDigitDate();
        if (x2 != 211010) return kResultFail;

        unsigned x3 = d.TwoDigitYear();
        if (x3 != 21) return kResultFail;

        RedDataString xstr = d.DateString();
        if (xstr != "2021/10/10") return kResultFail;

        RedDataString xstr2 = d.SixDigitDateString();
        if (xstr2 != "211010") return kResultFail;

        RedDataString xstr3 = d.EightDigitDateString();
        if (xstr3 != "20211010") return kResultFail;

        RedDate dateToday1 = RedDate::Today();
        RedDate dateToday2 = RedDate::Today();
        if (dateToday1 != dateToday2) return kResultFail;
    }

    {
        RedDate      d1(2022, 02, 28);
        RedDate Checkd1(2022, 03, 01);
        d1.NextDay();
        if (d1 != Checkd1) return kResultFail;
    }
    {
        RedDate      d1(2022, 12, 31);
        RedDate Checkd1(2023, 01, 01);
        d1.NextDay();
        if (d1 != Checkd1) return kResultFail;
    }
    {
        RedDate      d1(2022, 01, 01);
        RedDate Checkd1(2021, 12, 31);
        d1.PrevDay();
        if (d1 != Checkd1) return kResultFail;
    }
    {
        RedDate      d1(2020, 03, 01);
        RedDate Checkd1(2020, 02, 29);
        d1.PrevDay();
        if (d1 != Checkd1) return kResultFail;
    }
    {
        RedDate      d1(2000, 02, 02);
        RedDate Checkd1(2000, 02, 03);
        d1++;
        if (d1 != Checkd1) return kResultFail;
    }

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestTime(void)
{
    RedTime t1(12,  0,  0.0);
    RedTime t2( 1,  1,  1.1);

    RedDataString xstr = t1.TimeString();
    if (xstr != "12:00:00.00") return kResultFail;

    xstr = t1.SixDigitTimeString();
    if (xstr != "120000") return kResultFail;

    xstr = t2.SixDigitTimeString();
    if (xstr != "010101") return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Collections
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
    if (x != 1)              return kResultFail;

    if (l.FindLast(x) == 0) return kResultFail;
    if (x != 3)             return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Misc Classes
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTestCore::TestNumberRange(void)
{
    RedNumberRange DegreesLongitude(-180.0, 180.0);
    RedDataNumber x = 300;

    if (DegreesLongitude.IsInRange(x)) return kResultFail;

    DegreesLongitude.WrapNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return kResultFail;

    x = 300;
    DegreesLongitude.CropNumber(x);
    if (!DegreesLongitude.IsInRange(x)) return kResultFail;


    RedNumberRange FullCircleDegrees(0.0, 360.0);
    RedNumberRange FullCircleRadians(0.0, 2 * kPi);
    RedDataNumber angle = 90.0;

    RedDataNumber ftr(FullCircleDegrees.FractionThroughRange(angle));
    if (ftr != 0.25) return kResultFail;

    // RedDataNumber angleRads = RedNumberRange::RescaleNumber(angle, FullCircleDegrees, FullCircleRadians);
    // if (angleRads != half_pi) return kResultFail;

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

RedResult RedTestCore::TestEventLog(void)
{
    RedLog log;

    log.AddText("EventLogText1");
    log.AddText("EventLogText2");
    if (log.NumEvents() != 2) return kResultFail;
    if (log.ContainsError())  return kResultFail;

    RedLogEvent e(TEventLogType::eErrorEvent, "ErrorText1");
    log.AddEvent(e);
    if (log.NumEvents() != 3) return kResultFail;
    if (!log.ContainsError()) return kResultFail;

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
        outbuf.SetIndent(RedDataString("  "));

        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedDataString("aaabbb")) return kResultFail;
        outbuf.Empty();

        outbuf.Append("aaa");
        outbuf.SetIndentLevel(2);
        outbuf.WriteIndent();
        outbuf.Append("bbb");
        if (outbuf.ExtractData() != RedDataString("aaa    bbb")) return kResultFail;
        outbuf.Empty();

        RedDataString in = "111111\n222222";
        outbuf.SetIndentLevel(0);
        outbuf.Append("aaa");
        outbuf.IncreaseIndent();
        outbuf.AppendIndented(in);
        outbuf.DecreaseIndent();
        outbuf.AppendIndented("bbb");
        if (outbuf.ExtractData() != RedDataString("aaa\n  111111\n  222222\nbbb")) return kResultFail;
    }

    // Test stream operator
    {
        RedBufferOutput outbuf;
        RedDataNumber zz(12);
        RedDataString yy("qwqw");
        outbuf << 34 << "\n " << zz << " " << yy;
        if (outbuf.ExtractData() != RedDataString("34\n 12 qwqw")) return kResultFail;
    }
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Test
} // Red

