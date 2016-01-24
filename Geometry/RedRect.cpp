
#include "RedRect.h"

#include "math.h"

namespace Red {
namespace Geometry {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedRect::IsPointInRect(RedPoint2D p) const
{
    double minx = origin.X().DoubleValue();
    double miny = origin.Y().DoubleValue();
    double maxx = minx + size.Width().DoubleValue();
    double maxy = miny + size.Height().DoubleValue();

    double currx = p.X().DoubleValue();
    double curry = p.Y().DoubleValue();

    if ( (minx <= currx) && (currx <= maxx) &&
         (miny <= curry) && (curry <= maxy) )
    {
        return 1;
    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedRect::Inset(const RedNumber& i)
{
    // origin is bottom-left.
    // i is added to origin
    // j is subtraced from size, which defines top-right.
    RedNumber j = i * -2;

    origin.RelativeMove(i, i);
    size.Adjust(j, j);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red


