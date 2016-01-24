
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