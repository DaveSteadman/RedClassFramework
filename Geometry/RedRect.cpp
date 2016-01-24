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


