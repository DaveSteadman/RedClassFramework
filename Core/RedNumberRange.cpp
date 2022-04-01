// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

const bool RedNumberRange::IsInRange(const RedDataNumber& d) const 
{
    if ((cLow <= d) && (d <= cHigh))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedDataNumber RedNumberRange::FractionThroughRange(const RedDataNumber& d) const
{
    RedDataNumber base(d - cLow);
    RedDataNumber r(cHigh - cLow);
    return base / r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumberRange::WrapNumber(RedDataNumber& n) const
{
    if ((cLow < n) || (n < cHigh))
    {
        RedDataNumber range         = cHigh - cLow;
        RedDataNumber ZeroAdjustedN = n - cLow;
        RedDataNumber wrapped       = ZeroAdjustedN.DivisionRemainder(range);

        wrapped += cLow;
        n = wrapped;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumberRange::CropNumber(RedDataNumber& n) const
{
    if (n > cHigh) n = cHigh;
    if (n < cLow)  n = cLow;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedDataNumber RedNumberRange::RangeMin(void) const
{
    return cLow;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedDataNumber RedNumberRange::RangeMax(void) const
{
    // If we have a floating point number, wrapping on the upper limit, we need to reduce it
    if (iIsWrapOnUpperLimit && !iIsIntegerOnly)
        return (cHigh - kDefaultFloatCompareTollerance);

    return cHigh;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedNumberRange::RescaleNumber(const RedDataNumber& SourceNumber, const RedNumberRange& SourceRange, const RedNumberRange& DestRange)
{
    return RedDataNumber(0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


