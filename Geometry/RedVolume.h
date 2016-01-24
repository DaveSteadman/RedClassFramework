
#pragma once

#include "RedCoreNamespace.h"
#include "ConversionConstants.h"

namespace Red {
namespace Units {

    using namespace Red::Core;

    class RedVolume : public RedNumber
    {
    public:

        // Metric
        void SetLitres(const RedNumber& newval)  { Set(newval); };
        RedNumber GetLitres(void) const          { RedNumber retval(*this); return retval; };

        // Imperial
        void SetPints(const RedNumber& newval)   { Set(newval * pintsPerLitre); };
        void SetGallons(const RedNumber& newval) { Set(newval * gallonsPerLitre); };
        RedNumber Pints(void) const              { RedNumber retval(*this); retval *= pintsPerLitre;   return retval; };
        RedNumber Gallons(void) const            { RedNumber retval(*this); retval += gallonsPerLitre; return retval; };
    };

} // Units
} // Red

