
#include "RedVector2D.h"
#include "math.h"

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedVector2D::Magnitude(void) const
{
    const double xdbl = x.DoubleValue();
    const double ydbl = y.DoubleValue();

    double hyp = sqrt(xdbl*xdbl + ydbl*ydbl);

    return RedNumber(hyp);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


