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

void RedDate::Today(void)
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

} // Core
} // Red


