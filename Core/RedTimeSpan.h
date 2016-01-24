
#pragma once

#include "RedNumber.h"
#include "RedTime.h"

namespace Red {
namespace Core {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTimeSpan
{
public:

    RedTimeSpan(const RedTime& t1, const RedTime& t2) : starttime(t1), endtime(t2) { };

    const double SpanInDays(void) const;
    const double SpanInHours(void) const;
    const double SpanInSeconds(void) const;

    void   SetStartAtStartOfDay(void) { starttime.InitStartOfDay(); };
    void   SetEndAtEndOfDay(void)     { endtime.InitEndOfDay();     };

private:
    RedTime starttime;
    RedTime endtime;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Time
} // Red


