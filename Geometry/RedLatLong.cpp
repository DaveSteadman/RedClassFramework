
#include "RedLatLong.h"

#include <stdio.h>


namespace Red {
namespace Geometry {

static const double kLatLongDecPlaces = 5; // The number of decimal places to resolve a lat/long to 1metre.

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedLatLong::StringOfObject(void) const
{
    RedString retStr;

    retStr  = lat.DecimalStringWithDP(kLatLongDecPlaces);
    retStr += ", ";
    retStr += lon.DecimalStringWithDP(kLatLongDecPlaces);

    return retStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedLatLong::PopulateFromString(const RedString& str)
{
    double la = 0.0;
    double lo = 0.0;

    int ret = scanf(str.TextPtr(), "%f, %f", &la, &lo);

    if (ret > 0)
    {
        lat = la;
        lon = lo;
    }

    return ret;
}

} // Geometry
} // Red


