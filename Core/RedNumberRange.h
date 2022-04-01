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

#pragma once

#include "RedType.h"
#include "RedDataNumber.h"
#include "RedDataBoolean.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Bits defining a status value which can be passed into a constructor (or single setup-behaviour routine).
static const int kRedNumberRangeWrapOnUpper = 1;
static const int kRedNumberRangeIntOnly     = 2;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedNumberRange : public RedType
{
public:

    // constructors
    RedNumberRange() { Init(); };
    RedNumberRange(const double l, const double h) { cLow=l; cHigh=h; SetBehaviour(0); };
    RedNumberRange(const RedDataNumber& l, const RedDataNumber& h) { SetRange(l, h); SetBehaviour(0); };
    RedNumberRange(const RedDataNumber& l, const RedDataNumber& h, const int b) { SetRange(l, h); SetBehaviour(b); };

    ~RedNumberRange() { };

    // Inherited: RedType
    void          Init(void)        { SetRange(0, 1); SetBehaviour(0); };
    RedDataType   Type(void) const  { return kDataTypeBool; };
    RedType*      Clone(void) const { RedNumberRange* r = new RedNumberRange(cLow, cHigh); return (RedType*)r; };

    void          SetBehaviour(const int b);

    // simple set/get operations
    void             SetRange(const RedDataNumber& l, const RedDataNumber& h) { cLow=l; cHigh=h; };
    const bool IsInRange(const RedDataNumber& d) const;

    // Calculations
    const RedDataNumber FractionThroughRange(const RedDataNumber& d) const;
    static RedDataNumber RescaleNumber(const RedDataNumber& SourceNumber, const RedNumberRange& SourceRange, const RedNumberRange& DestRange);

    // Apply this objects range limits to a number
    void WrapNumber(RedDataNumber& n) const;
    void CropNumber(RedDataNumber& n) const;

    const RedDataNumber RangeMin(void) const;
    const RedDataNumber RangeMax(void) const;

private:

    // Does the number wrap on the upper limit. ie, you can get 59.999 seconds, but 60.0 is considered 0.
    int iIsWrapOnUpperLimit;

    // Is the range made strictly of integer values
    int iIsIntegerOnly;

    RedDataNumber cLow;
    RedDataNumber cHigh;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

