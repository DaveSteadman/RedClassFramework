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


