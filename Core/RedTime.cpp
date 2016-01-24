

#include "RedCoreNamespace.h"

#include "RedTime.h"

#include <time.h>
#include <stdio.h>

namespace Red {
namespace Core {

using namespace Red::Core;

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

void RedTime::Now(void)
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

} // Time
} // Red


