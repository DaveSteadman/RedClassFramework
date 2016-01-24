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

#pragma once

#include "RedCoreNamespace.h"
#include "ConversionConstants.h"

namespace Red {
namespace Units {

    using namespace Red::Core;

    static const RedNumberRange kDegreesFullCircle  = RedNumberRange(0, 360,      kRedNumberRangeWrapOnUpper); // wrap, so exact 360 isn't possible
    static const RedNumberRange kRadiansFullCircle  = RedNumberRange(0, 2.0 * pi, kRedNumberRangeWrapOnUpper); // wrap, so exact 360 isn't possible

    class RedAngle : public RedNumber
    {
    public:
        void      SetRadians(const RedNumber& newval) { Set(newval); };
        void      SetDegrees(const RedNumber& newval) { Set(newval * radiansPerDegree); };
        RedNumber Radians(void) const                 { RedNumber retval(*this); return retval; };
        RedNumber Degrees(void) const                 { RedNumber retval(*this); retval *= degreesPerRadian; return retval; };
    };

} // Units
} // Red