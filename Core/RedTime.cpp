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

#include "RedString.h"
#include "RedNumber.h"
#include "RedTime.h"

#include <time.h>
#include <stdio.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTime::SetTime(const RedString& timestr)
{
    int    h;
    int    m;
    double s;

    sscanf(timestr.TextPtr(), "%d:%d:%lf", &h, &m, &s);

    hour    = h;
    minute  = m;
    seconds = s;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedTime::TimeString(void) const
{
    RedString retstr;

    retstr.Append(hour.IntegerValue());
    retstr.Append(":");
    retstr.Append(minute.IntegerValue());
    retstr.Append(":");

    RedNumber ds = seconds;
    retstr.Append(ds.DecimalStringWithDP(3));

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedTime::SixDigitInt(void) const
{
    int rettime = 0;

    rettime += hour.IntegerValue()   * 10000;
    rettime += minute.IntegerValue() * 100;
    rettime += seconds.IntegerValue();

    return rettime;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTime::SetNow(void)
{
    time_t     rawtime;
    struct tm* timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    hour    = timeinfo->tm_hour;
    minute  = timeinfo->tm_min;
    seconds = timeinfo->tm_sec;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTime::SetTimeFromElapsedSeconds(const RedNumber& DayElapsedSeconds)
{
	Init();

	RedNumber DecrementingSeconds = DayElapsedSeconds;

	while (DecrementingSeconds > kSecondsInHour)
    {
        hour++;
        DecrementingSeconds -= kSecondsInHour;
	}
	while (DecrementingSeconds > kSecondsInMinute)
	{
		minute++;
		DecrementingSeconds -= kSecondsInMinute;
	}
	seconds = DecrementingSeconds;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Time
} // Red
