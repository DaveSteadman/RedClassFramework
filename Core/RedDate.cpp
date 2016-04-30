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

#include "RedDate.h"
#include "RedNumber.h"
#include "RedString.h"

#include <time.h>
#include <stdio.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDate::SetDate(const RedString& datestr)
{
    sscanf(datestr.TextPtr(), "%u/%u/%u", &year, &month, &date);
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

const RedString RedDate::DateString(void) const
{
    RedString retstr;

    RedNumber y(year);
    RedNumber m(month);
    RedNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append("/");
    retstr.Append(m.DecimalString());
    retstr.Append("/");
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedDate::EightDigitDateString(void) const
{
    RedString retstr;

    RedNumber y(year);
    RedNumber m(month);
    RedNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append(m.DecimalString());
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedDate::SixDigitDateString(void) const
{
    RedString retstr;

    RedNumber y(TwoDigitYear());
    RedNumber m(month);
    RedNumber d(date);

    retstr.Append(y.DecimalString());
    retstr.Append(m.DecimalString());
    retstr.Append(d.DecimalString());

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const unsigned RedDate::EightDigitDate(void) const
{
    unsigned retdate = 0;

    retdate += year  * 10000;
    retdate += month * 100;
    retdate += date;

    return retdate;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const unsigned RedDate::SixDigitDate(void) const
{
	unsigned retdate = 0;

	retdate += TwoDigitYear() * 10000;
	retdate += month * 100;
	retdate += date;

	return retdate;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedDate::DaysInMonth(const unsigned ForMonth, const unsigned ForYear)
{
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


