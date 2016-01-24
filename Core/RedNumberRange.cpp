
#include "RedNumberRange.h"

#include <time.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumberRange::SetBehaviour(const int b)
{
    if (b & kRedNumberRangeIntOnly)
        iIsIntegerOnly = 1;
    else
        iIsIntegerOnly = 0;

    if (b & kRedNumberRangeWrapOnUpper)
        iIsWrapOnUpperLimit = 1;
    else
        iIsWrapOnUpperLimit = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedNumberRange::IsInRange(const RedNumber& d) const 
{
    if ((cLow <= d) && (d <= cHigh))
        return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumberRange::WrapNumber(RedNumber& n) const
{
    if ((cLow < n) || (n < cHigh))
    {
        RedNumber range         = cHigh - cLow;
        RedNumber ZeroAdjustedN = n - cLow;
        RedNumber wrapped       = ZeroAdjustedN.DivisionRemainder(range);

        wrapped += cLow;
        n = wrapped;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumberRange::CropNumber(RedNumber& n) const
{
    if (n > cHigh) n = cHigh;
    if (n < cLow)  n = cLow;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedNumberRange::RangeMin(void) const
{
    return cLow;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedNumberRange::RangeMax(void) const
{
    // If we have a floating point number, wrapping on the upper limit, we need to reduce it
    if (iIsWrapOnUpperLimit && !iIsIntegerOnly)
        return (cHigh - kFloatCompTollerance);

    return cHigh;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


