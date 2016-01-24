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


