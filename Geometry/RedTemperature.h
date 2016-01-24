

#pragma once

#include "RedCoreNamespace.h"
#include "ConversionConstants.h"

namespace Red {
namespace Units {

    using namespace Red::Core;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    class RedTemperature : public RedNumber
    {
    public:

        // Metric
        void SetKelvin(const RedNumber& newval)   { Set(newval); };
        void SetCelsius(const RedNumber& newval)  { Set(newval + absoluteZeroInCelsius); };
        RedNumber Kelvin(void) const              { RedNumber retval(*this); return retval; };
        RedNumber Celsius(void) const             { RedNumber retval(*this); retval += absoluteZeroInCelsius; return retval; };
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Units
} // Red