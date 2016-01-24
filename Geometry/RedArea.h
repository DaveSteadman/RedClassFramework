
#pragma once

#include "RedCoreNamespace.h"
#include "ConversionConstants.h"

namespace Red {
namespace Units {

    using namespace Red::Core;

    class RedArea : public RedNumber
    {
    public:
        void SetSquareMetres(const RedNumber& newval) { Set(newval); };
        void SetAcres(const RedNumber& newval)        { Set(newval * squaremetresPerAcre); };

        RedNumber SquareMetres(void) const            { RedNumber retval(*this); return retval; };
        RedNumber Acres(void) const                   { RedNumber retval(*this); retval *= acresPerSquaremetre; return retval; };

    };

} // Units
} // Red