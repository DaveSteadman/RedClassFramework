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

#define _CRT_SECURE_NO_WARNINGS

#include "RedString.h"
#include "RedNumber.h"
#include "RedTime.h"

#include <time.h>
#include <stdio.h>
#include <math.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTime::SetTime(const RedString& timestr)
{
    unsigned h;
	unsigned m;
    double   s;

    sscanf(timestr.TextPtr(), "%u:%u:%lf", &h, &m, &s);

    hour    = h;
    minute  = m;
    seconds = s;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Returns a string formatted: hh:mm:ss
const RedString RedTime::TimeString(void) const
{
    RedString retstr;

    RedNumber h(hour);
    RedNumber m(minute);
    RedNumber s(seconds);

    retstr.Append(h.DecimalStringWithMinDigitsAndDP(2, 0));
    retstr.Append(":");
    retstr.Append(m.DecimalStringWithMinDigitsAndDP(2, 0));
    retstr.Append(":");
    retstr.Append(s.DecimalStringWithMinDigitsAndDP(5, 2));

    return retstr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Returns an unsigned number, fomatted: hhmmss
const unsigned RedTime::SixDigitTime(void) const 
{
    unsigned rettime = 0;

    rettime += hour   * 10000;
    rettime += minute * 100;
    rettime += (unsigned)floor(seconds);

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

RedTime RedTime::Now(void)
{
    RedTime RetTime;

    RetTime.SetNow();

    return RetTime;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTime::SetTimeFromElapsedSeconds(const double& DayElapsedSeconds)
{
	Init();

	double DecrementingSeconds = DayElapsedSeconds;

	while (DecrementingSeconds > kTimeSecondsInHour)
    {
        hour++;
        DecrementingSeconds -= kTimeSecondsInHour;
	}
	while (DecrementingSeconds > kTimeSecondsInMinute)
	{
		minute++;
		DecrementingSeconds -= kTimeSecondsInMinute;
	}
	seconds = DecrementingSeconds;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
