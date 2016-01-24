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

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Time is strictly formatted in an HH:MM:SS format. 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedNumberRange kSecondsInDay    = RedNumberRange(0, 86400, kRedNumberRangeWrapOnUpper);
static const RedNumberRange kSecondsInMinute = RedNumberRange(0, 60,    kRedNumberRangeWrapOnUpper);
static const RedNumberRange kMinutesInHour   = RedNumberRange(0, 60,    kRedNumberRangeWrapOnUpper);
static const RedNumberRange kHoursInDay      = RedNumberRange(0, 24,    kRedNumberRangeWrapOnUpper);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTime
{
public:

    RedTime(void) { Init(); };

    void Init(void)           { hour=kHoursInDay.RangeMin(); minute=kMinutesInHour.RangeMin(); seconds=kSecondsInMinute.RangeMin(); };
    void InitStartOfDay(void) { hour=kHoursInDay.RangeMin(); minute=kMinutesInHour.RangeMin(); seconds=kSecondsInMinute.RangeMin(); };
    void InitEndOfDay(void)   { hour=kHoursInDay.RangeMax(); minute=kMinutesInHour.RangeMax(); seconds=kSecondsInMinute.RangeMax(); };

    void SetTime(const int h, const int m, const double& s) { hour=h; minute=m; seconds=s; };
    void SetTime(const RedString& timestr);

    const RedString TimeString(void) const;
    const int       SixDigitInt(void) const;

    void Now(void);

    const RedNumber& Hour(void) const { return hour; };

private:

    RedNumber hour;
    RedNumber minute;
    RedNumber seconds;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Time
} // Red


