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

#pragma once

#include "RedNumber.h"
#include "RedNumberRange.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Time is strictly formatted in a 24hour HH:MM:SS format. 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedNumber kTimeSecondsInDay    = RedNumber(86400);
static const RedNumber kTimeSecondsInHour   = RedNumber(3600);
static const RedNumber kTimeSecondsInMinute = RedNumber(60);
static const RedNumber kTimeMinutesInDay    = RedNumber(1440);
static const RedNumber kTimeMinutesInHour   = RedNumber(60);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTime
{
public:

    RedTime(void) { Init(); };
    RedTime(const unsigned h, const unsigned m, const double& s) { hour=h; minute=m; seconds=s; };

    void Init(void) { hour=0; minute=0; seconds=0; };

    void SetTime(const unsigned h, const unsigned m, const double& s)        { hour=h; minute=m; seconds=s; };
    void SetTime(const RedNumber& h, const RedNumber& m, const RedNumber& s) { hour=h.IntegerValue(); minute=m.IntegerValue(); seconds=s.DoubleValue(); };
    void SetTime(const RedString& timestr);

    void SetNow(void);

    // Time Presentation
    const RedString TimeString(void) const;
    const int       SixDigitInt(void) const;

	// Simple Access Routines
    const RedNumber Hours     (void) const                  { return hour;    };
    const RedNumber Minutes   (void) const                  { return minute;  };
    const RedNumber Seconds   (void) const                  { return seconds; };
    void            SetHours  (const RedNumber& NewHours)   { hour    = NewHours;   };
    void            SetMinutes(const RedNumber& NewMinutes) { minute  = NewMinutes; };
    void            SetSeconds(const RedNumber& NewSeconds) { seconds = NewSeconds; };

    // Seconds In Day Routines
    const RedNumber SecondsElapsedInDay(void) const { return (hour*kTimeSecondsInHour) + (minute*kTimeSecondsInMinute) + seconds; };
    const RedNumber SecondsLeftInDay(void)    const { return kTimeSecondsInDay - SecondsElapsedInDay(); };
    void            SetTimeFromElapsedSeconds(const RedNumber& DayElapsedSeconds);

private:

    RedNumber hour;
    RedNumber minute;
    RedNumber seconds;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedTime kTimeStartOfDay = RedTime(0,   0,  0.0);
static const RedTime kTimeEndOfDay   = RedTime(24, 60, 60.0);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Time
} // Red
