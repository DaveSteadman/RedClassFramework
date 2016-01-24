#pragma once

#include "RedType.h"
#include "RedNumber.h"

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
        RedNumberRange(const RedNumber& l, const RedNumber& h) { SetRange(l, h); SetBehaviour(0); };
        RedNumberRange(const RedNumber& l, const RedNumber& h, const int b) { SetRange(l, h); SetBehaviour(b); };

        ~RedNumberRange() { };

        // Inherited: RedType
        void                Init(void)        { SetRange(0, 1); SetBehaviour(0); };
        const RedDataType   Type(void) const  { return kDataTypeBool; };
        RedType*            Clone(void) const { RedNumberRange* r = new RedNumberRange(cLow, cHigh); return (RedType*)r; };

        void          SetBehaviour(const int b);

        // simple set/get operations
        void          SetRange(const RedNumber& l, const RedNumber& h) { cLow=l; cHigh=h; };
        const int     IsInRange(const RedNumber& d) const;

        // Apply this objects range limits to a number
        void WrapNumber(RedNumber& n) const;
        void CropNumber(RedNumber& n) const;

        const RedNumber RangeMin(void) const;
        const RedNumber RangeMax(void) const;

    private:

        // Does the number wrap on the upper limit. ie, you can get 59.999 seconds, but 60.0 is considered 0.
        int iIsWrapOnUpperLimit;

        // Is the range made strictly of integer values
        int iIsIntegerOnly;

        RedNumber cLow;
        RedNumber cHigh;
    };

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

