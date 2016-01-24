
#include "RedLatLong.h"
#include "RedLatLongBox.h"

#include <stdio.h>


namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedLatLongBox::IsLatLongInBox(const RedLatLong& p) const
{
    // Simple lat/long checks. Will eventually need expanding to cover date line issues.

    if (p.Lat() < topleft.Lat()) return 0;
    if (p.Lat() > bottomright.Lat()) return 0;

    if (p.Lon() < topleft.Lon()) return 0;
    if (p.Lon() > bottomright.Lon()) return 0;

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


