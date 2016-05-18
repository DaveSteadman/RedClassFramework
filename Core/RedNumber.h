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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Default tollerance on floating point equality statements
static const double kFloatCompTollerance = 0.0000001;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class representing a mutable number. Internally differentiates between int and float values.
class RedNumber : public RedType
{
public:

    RedNumber(void)                    { Init(); };
    RedNumber(const int iNum)          { Set(iNum); };
    RedNumber(const unsigned iNum)     { Set((int)iNum); };
    RedNumber(const double dblNum)     { Set(dblNum); };
    RedNumber(const RedNumber& objNum) { Set(objNum); };
    RedNumber(const RedString& cNewDecimalVal) { SetDecimalString(cNewDecimalVal); };
    ~RedNumber(void) { };

    // Inherited: RedType
    void          Init(void)        { eNumType=eInt; iIntVal=0; dblFloatVal=0.0; };
    RedDataType   Type(void) const  { return kDataTypeNum; };
    RedType*      Clone(void) const { RedNumber* newN = new RedNumber(*this); return (RedType*)newN; };

    // Class operations
    bool          IsZero(void)     const;
    bool          IsPositive(void) const;
    bool          IsInteger(void)  const { return (eNumType == eInt);   };
    bool          IsReal(void)     const { return (eNumType == eFloat); };
    bool          IsEqualTo(const RedNumber& CheckVal) const;
    bool          IsEqualToWithinTollerance(const RedNumber& CheckVal, const RedNumber& tollerance) const;

    RedString     DecimalString(void) const;
    RedString     DecimalStringWithDP(const unsigned decimalplaces) const;
    RedString     DecimalStringWithMinDigitsAndDP(const unsigned mindigits, const unsigned decimalplaces) const;
    RedChar       CharValue(void) const;
    int           IntegerValue(void) const;
    double        DoubleValue(void) const;

    void          Set(const RedNumber& cNewVal) { eNumType=cNewVal.eNumType; iIntVal=cNewVal.iIntVal; dblFloatVal=cNewVal.dblFloatVal; };
    void          Set(const double dblNewVal)   { eNumType=eFloat;           iIntVal=0;               dblFloatVal=dblNewVal; };
    void          Set(const int iNewVal)        { eNumType=eInt;             iIntVal=iNewVal;         dblFloatVal=0.0; };
    void          SetZero(void)                 { Init(); };
    void          SetDecimalString(const RedString& cNewDecimalVal);

    void          MakePositive(void);
    void          MakeNegative(void);

    RedNumber     IntegerPart(void) const;
    RedNumber     FractionalPart(void) const;
    RedNumber     DivisionQuotient(const RedNumber& d) const;
    RedNumber     DivisionRemainder(const RedNumber& d) const;

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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator ==(const RedNumber& lhs, const RedNumber& rhs);
bool operator !=(const RedNumber& lhs, const RedNumber& rhs);
bool operator >=(const RedNumber& lhs, const RedNumber& rhs);
bool operator <=(const RedNumber& lhs, const RedNumber& rhs);
bool operator  >(const RedNumber& lhs, const RedNumber& rhs);
bool operator  <(const RedNumber& lhs, const RedNumber& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedSmartPtr<RedNumber> RedNumberSmartPtr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedNumber kNumberOne                 = RedNumber(1);
static const RedNumber kNumberFloatCompTollerance = RedNumber(kFloatCompTollerance);
static const RedNumber kNumberZero                = RedNumber(0);
static const RedNumber kNumberMinusOne            = RedNumber(-1);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


