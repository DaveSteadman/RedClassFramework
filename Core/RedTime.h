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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Time is formatted in 24hour HH:MM:SS

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const unsigned kTimeSecondsInMinute = 60;
static const unsigned kTimeMinutesInHour   = 60;
static const unsigned kTimeHoursInDay      = 24;
static const unsigned kTimeSecondsInHour   = kTimeSecondsInMinute * kTimeMinutesInHour;
static const unsigned kTimeMinutesInDay    = kTimeMinutesInHour * kTimeHoursInDay;
static const unsigned kTimeSecondsInDay    = kTimeSecondsInHour * kTimeHoursInDay;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTime
{
public:

    RedTime(void) { Init(); };
    RedTime(const unsigned h, const unsigned m, const double& s) { hour=h; minute=m; seconds=s; };

    void Init(void) { hour=0; minute=0; seconds=0.0; };

    void SetTime(const unsigned h, const unsigned m, const double& s) { hour=h; minute=m; seconds=s; };
    void SetTime(const RedString& timestr);
    void SetNow(void);

    static RedTime Now(void);

    // Time Presentation
    const RedString TimeString(void) const;   // hh:mm:ss
    const unsigned  SixDigitTime(void) const; // hhmmss

	// Simple Access Routines
    const unsigned Hours     (void) const                  { return hour;    };
    const unsigned Minutes   (void) const                  { return minute;  };
    const double   Seconds   (void) const                  { return seconds; };
    void           SetHours  (const unsigned& NewHours)    { hour    = NewHours;   };
    void           SetMinutes(const unsigned& NewMinutes)  { minute  = NewMinutes; };
    void           SetSeconds(const double& NewSeconds)    { seconds = NewSeconds; };

    // Seconds In Day Routines
    const double SecondsElapsedInDay(void) const { return (hour*kTimeSecondsInHour) + (minute*kTimeSecondsInMinute) + seconds; };
    const double SecondsLeftInDay(void)    const { return kTimeSecondsInDay - SecondsElapsedInDay(); };
    void         SetTimeFromElapsedSeconds(const double& DayElapsedSeconds);

private:

	unsigned hour;
	unsigned minute;
	double   seconds;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedTime kTimeStartOfDay = RedTime(0,   0,  0.0);
static const RedTime kTimeMidday     = RedTime(12,  0,  0.0);
static const RedTime kTimeEndOfDay   = RedTime(24, 60, 60.0);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
