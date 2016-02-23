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

using namespace Red::Core;

namespace Red {
namespace Geometry {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Geometry
} // Red
