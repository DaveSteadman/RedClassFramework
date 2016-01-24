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

#include "RedType.h"
#include "RedSmartPtr.h"
#include "RedString.h"
#include "RedChar.h"

#include "ConversionConstants.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

/// Constant describing the tollerance on floating point equality statements
static const double kFloatCompTollerance = 0.0000001;

/// Class representing a mutable number. Internally differentiates between int and float values.
class RedNumber : public RedType
{
public:

    RedNumber(void)                    { Init(); };
    RedNumber(const int iNum)          { Set(iNum); };
    RedNumber(const double dblNum)     { Set(dblNum); };
    RedNumber(const RedNumber& objNum) { Set(objNum); };
    RedNumber(const RedString& cNewDecimalVal) { SetDecimalString(cNewDecimalVal); };
    ~RedNumber(void) { };

    // Inherited: RedType
    void                Init(void)        { eNumType=eInt; iIntVal=0; dblFloatVal=0.0; };
    const RedDataType   Type(void) const  { return kDataTypeNum; };
    RedType*            Clone(void) const { RedNumber* newN = new RedNumber(*this); return (RedType*)newN; };

    // Class operations
    const int           IsZero(void) const;
    const int           IsPositive(void) const;
    const int           IsInteger(void) const  { return (eNumType == eInt); };
    const int           IsReal(void) const     { return (eNumType == eFloat); };
    const int           IsEqualTo(const RedNumber& CheckVal) const;
    const int           IsEqualToWithinTollerance(RedNumber CheckVal, RedNumber tollerance) const;

    const RedString     DecimalString(void) const;
    const RedString     DecimalStringWithDP(const int decimalplaces) const;
    const RedChar       CharValue(void) const;
    const int           IntegerValue(void) const;
    const double        DoubleValue(void) const;

    void                Set(const RedNumber& cNewVal) { eNumType=cNewVal.eNumType; iIntVal=cNewVal.iIntVal; dblFloatVal=cNewVal.dblFloatVal; };
    void                Set(const double dblNewVal)   { eNumType=eFloat;           iIntVal=0;               dblFloatVal=dblNewVal; };
    void                Set(const int iNewVal)        { eNumType=eInt;             iIntVal=iNewVal;         dblFloatVal=0.0; };
    void                SetZero(void)                 { Init(); };
    void                SetDecimalString(const RedString& cNewDecimalVal);

    void                MakePositive(void);
    void                MakeNegative(void);

    const RedNumber     IntegerPart(void) const;
    const RedNumber     FractionalPart(void) const;
    const RedNumber     DivisionQuotient(const RedNumber& d) const;
    const RedNumber     DivisionRemainder(const RedNumber& d) const;

    const int operator==(const RedNumber& rhs) const { if ( IsEqualToWithinTollerance(rhs, kFloatCompTollerance)) return 1; return 0; };
    const int operator!=(const RedNumber& rhs) const { if (!IsEqualToWithinTollerance(rhs, kFloatCompTollerance)) return 1; return 0; };

    const int operator >=(const RedNumber& n) const;
    const int operator <=(const RedNumber& n) const;
    const int operator  >(const RedNumber& n) const;
    const int operator  <(const RedNumber& n) const;

    // Arithemtic operators
    RedNumber operator  +(const RedNumber& n) const;
    RedNumber operator  -(const RedNumber& n) const;
    RedNumber operator  *(const RedNumber& n) const;
    RedNumber operator  /(const RedNumber& n) const;
    void      operator +=(const RedNumber& n);
    void      operator -=(const RedNumber& n);
    void      operator *=(const RedNumber& n);
    void      operator /=(const RedNumber& n);

    RedNumber& operator ++(); // Prefix
    RedNumber  operator ++(int); // Postfix

private:

    typedef enum {eFloat=1, eInt=2} TENumberType;

    TENumberType    eNumType;
    int             iIntVal;
    double          dblFloatVal;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedNumber> RedNumberSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedNumber kNumberPi       = RedNumber(Units::pi);
static const RedNumber kNumberOne      = RedNumber(1);
static const RedNumber kNumberZero     = RedNumber(0);
static const RedNumber kNumberMinusOne = RedNumber(-1);

} // Core
} // Red


