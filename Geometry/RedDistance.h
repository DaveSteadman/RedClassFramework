
#pragma once

#include "RedCoreNamespace.h"
#include "ConversionConstants.h"

namespace Red {
namespace Units {

    using namespace Red::Core;

    class RedDistance : public RedNumber
    {
    public:

        RedDistance(void)                            { Init(); };
        RedDistance(const RedNumber& val)            { Set(val); };
        RedDistance(const RedDistance& dist)         { Set(dist.Metres()); };

        // Metric
        void SetKilometres(const RedNumber& newval)  { Set(newval * metresPerKilometre); };
        void SetMetres(const RedNumber& newval)      { Set(newval); };
        void SetCentimetres(const RedNumber& newval) { Set(newval * metresPerCentimetre); };
        void SetMillimetres(const RedNumber& newval) { Set(newval * metresPerMillimetre); };
        RedNumber Kilometres(void) const             { RedNumber retval(*this); retval *= kilometresPerMetre; return retval; };
        RedNumber Metres(void) const                 { RedNumber retval(*this); return retval; };
        RedNumber Centimetres(void) const            { RedNumber retval(*this); retval *= centimetresPerMetre; return retval; };
        RedNumber Millimetres(void) const            { RedNumber retval(*this); retval *= millimetresPerMetre; return retval; };

        // Imperial
        void SetMiles(const RedNumber& newval)       { Set(newval * metresPerMile); };
        void SetYards(const RedNumber& newval)       { Set(newval * metresPerYard); };
        void SetFeet(const RedNumber& newval)        { Set(newval * metresPerFoot); };
        void SetInches(const RedNumber& newval)      { Set(newval * metresPerInch); };
        RedNumber Miles(void) const                  { RedNumber retval(*this); retval *= milesPerMetre;  return retval; };
        RedNumber Yards(void) const                  { RedNumber retval(*this); retval *= yardsPerMetre;  return retval; };
        RedNumber Feet(void) const                   { RedNumber retval(*this); retval *= feetPerMetre;   return retval; };
        RedNumber Inches(void) const                 { RedNumber retval(*this); retval *= inchesPerMetre; return retval; };
    };

} // Units
} // Red



