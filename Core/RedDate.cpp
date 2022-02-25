// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#define _CRT_SECURE_NO_WARNINGS

#include "RedDate.h"
#include "RedDataNumber.h"
#include "RedDataString.h"

#include <time.h>
#include <stdio.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDate::SetDate(const RedDataString& datestr)
{
    sscanf(datestr.TextPtr(), "%u/%u/%u", &year, &month, &date);
    
    // Dates are stored as absolute/4-digit numbers
    // 2 digit years are assumed to be in the 2000->2100 range
    if (year < 100) year += 2000;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDate RedDate::Today(void)
{
    RedDate RetDate;

    RetDate.SetToday();

    return RetDate;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDate::SetToday(void)
{
    time_t     rawtime;
    struct tm* timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    year  = 1900 + timeinfo->tm_year;
    month = timeinfo->tm_mon + 1; // +1 converts range from 0-11 to 1-12
    date  = timeinfo->tm_mday;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDate::DateString(void) const
{
    RedDataString retstr;

    RedDataNumber y(year);
    RedDataNumber m(month);
    RedDataNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append("/");
    retstr.Append(m.DecimalString());
    retstr.Append("/");
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDate::EightDigitDateString(void) const
{
    RedDataString retstr;

    RedDataNumber y(year);
    RedDataNumber m(month);
    RedDataNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append(m.DecimalString());
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDate::SixDigitDateString(void) const
{
    RedDataString retstr;

    RedDataNumber y(TwoDigitYear());
    RedDataNumber m(month);
    RedDataNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append(m.DecimalString());
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::EightDigitDate(void) const
{
    unsigned retdate = 0;

    retdate += year  * 10000;
    retdate += month * 100;
    retdate += date;

    return retdate;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::SixDigitDate(void) const
{
    unsigned retdate = 0;

    retdate += TwoDigitYear() * 10000;
    retdate += month * 100;
    retdate += date;

    return retdate;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysFromStartOfMonth(void) const
{
    return date;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysToEndOfMonth(void) const
{
    return (DaysInMonth(month, year) - date);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysFromStartOfYear(void) const
{
    unsigned retdays = 0;

    for (unsigned m=1; m<month; m++)
        retdays += DaysInMonth(m, year);

    retdays += date;

    return retdays;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysToEndOfYear(void) const
{
    return (DaysInYear(year) - DaysFromStartOfYear());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysInMonth(const unsigned ForMonth, const unsigned ForYear)
{
    // Validate params
    if ((ForMonth == 0) || (ForMonth > 12)) throw;

    if (ForMonth == 1) // January
        return 31;
    if (ForMonth == 2) // February
    {
        if (RedDate::IsLeapYear(ForYear))
            return 29;
        else
            return 28;
    }
    if (ForMonth == 3) // March
        return 31;
    if (ForMonth == 4) // April
        return 30;
    if (ForMonth == 5) // May
        return 31;
    if (ForMonth == 6) // June
        return 30;
    if (ForMonth == 7) // July
        return 31;
    if (ForMonth == 8) // August
        return 31;
    if (ForMonth == 9) // September
        return 30;
    if (ForMonth == 10) // October
        return 31;
    if (ForMonth == 11) // November
        return 30;
    if (ForMonth == 12) // December
        return 31;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDate::IsLeapYear(const unsigned ForYear)
{
    if ((ForYear % 400) == 0)
        return true;
    else if ((ForYear % 100) == 0)
        return true;
    else if ((ForYear % 4) == 0 )
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysInYear(const unsigned ForYear)
{
    if (IsLeapYear(ForYear))
        return 366;
    else
        return 365;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDate::operator =(const RedDate& cNewVal)
{
    year  = cNewVal.year;
    month = cNewVal.month;
    date  = cNewVal.date;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() == rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() != rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator >=(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() >= rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <=(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() <= rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator >(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() > rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <(const RedDate& lhs, const RedDate& rhs)
{
    if (lhs.EightDigitDate() < rhs.EightDigitDate())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


