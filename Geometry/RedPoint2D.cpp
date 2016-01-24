
#include "RedPoint2D.h"
#include "math.h"

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedPoint2D::DistanceTo(const RedPoint2D& newpos) const
{
    double dx = x.DoubleValue() - newpos.x.DoubleValue();
    double dy = y.DoubleValue() - newpos.y.DoubleValue();

    double dist = sqrt(dx*dx + dy*dy);

    return dist;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedVector2D RedPoint2D::VectorTo(const RedPoint2D& newpos) const
{
    RedVector2D v(newpos.x - x, newpos.y - y);

    return v;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


