
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


