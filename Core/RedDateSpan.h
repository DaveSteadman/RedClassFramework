
#pragma once

#include "RedNumber.h"
#include "RedDate.h"

namespace Red {
namespace Core {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedDateSpan
{
public:

      RedDateSpan(const RedDate& RedDate1, const RedDate& d2) : startdate(d2), enddate(d2) { };

      double SpanInDays(void) const;
      double SpanInHours(void) const;
      double SpanInSeconds(void) const;

      double DaysToStartOfYear(void) const;
      double DaysToEndOfYear(void) const;

      /// TODO Date: Days to start/end of year & Days in year. The span can get days and finer units.

private:
      RedDate startdate;
      RedDate enddate;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Time
} // Red



