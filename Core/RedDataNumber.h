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

#include "RedData.h"
#include "RedDataString.h"
#include "RedDataChar.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Default tollerance on floating point equality statements
static const double kDefaultFloatCompareTollerance = 0.0000001;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class representing a mutable number. Internally differentiates between int and float values.
class RedDataNumber : public RedData
{
public:

    RedDataNumber(void)                    { Init(); };
    RedDataNumber(const int iNum)          { Set(iNum); };
    RedDataNumber(const unsigned iNum)     { Set((int)iNum); };
    RedDataNumber(const double dblNum)     { Set(dblNum); };
    RedDataNumber(const RedDataNumber& objNum) { Set(objNum); };
    RedDataNumber(const RedDataString& cNewDecimalVal) { SetDecimalString(cNewDecimalVal); };
    ~RedDataNumber(void) { };

    // Inherited: RedData
    void          Init(void)        { eNumType=TENumberType::eInt; iIntVal=0; dblFloatVal=0.0; };
    RedDataType   Type(void) const  { return kDataTypeNum; };
    RedData*      Clone(void) const { RedDataNumber* newN = new RedDataNumber(*this); return (RedData*)newN; };

    // Class operations
    bool          IsZero(void)     const;
    bool          IsPositive(void) const;
    bool          IsInteger(void)  const { return (eNumType == TENumberType::eInt);   };
    bool          IsReal(void)     const { return (eNumType == TENumberType::eFloat); };
    bool          IsEqualTo(const RedDataNumber& CheckVal) const;
    bool          IsEqualToWithinTollerance(const RedDataNumber& CheckVal, const RedDataNumber& tollerance) const;

    RedDataString DecimalString(void) const;
    RedDataString DecimalStringWithDP(const unsigned decimalplaces) const;
    RedDataString DecimalStringWithMinDigitsAndDP(const unsigned mindigits, const unsigned decimalplaces) const;
    RedDataString HexadecimalString(void) const;
    RedDataString HexadecimalStringWithMinDigits(const unsigned mindigits) const;

    RedDataChar   CharValue(void) const;
    int           IntegerValue(void) const;
    double        DoubleValue(void) const;

    void          Set(const RedDataNumber& cNewVal) { eNumType=cNewVal.eNumType; iIntVal=cNewVal.iIntVal; dblFloatVal=cNewVal.dblFloatVal; };
    void          Set(const double dblNewVal)       { eNumType=TENumberType::eFloat; iIntVal=0; dblFloatVal=dblNewVal; };
    void          Set(const int iNewVal)            { eNumType=TENumberType::eInt; iIntVal=iNewVal; dblFloatVal=0.0; };
    void          SetZero(void)                     { Init(); };
    void          SetDecimalString(const RedDataString& cNewDecimalVal);

    void          MakePositive(void);
    void          MakeNegative(void);

    RedDataNumber IntegerPart(void) const;
    RedDataNumber FractionalPart(void) const;
    RedDataNumber DivisionQuotient(const RedDataNumber& d) const;
    RedDataNumber DivisionRemainder(const RedDataNumber& d) const;

    // Arithemtic operators
    RedDataNumber operator  +(const RedDataNumber& n) const;
    RedDataNumber operator  -(const RedDataNumber& n) const;
    RedDataNumber operator  *(const RedDataNumber& n) const;
    RedDataNumber operator  /(const RedDataNumber& n) const;
    void          operator +=(const RedDataNumber& n);
    void          operator -=(const RedDataNumber& n);
    void          operator *=(const RedDataNumber& n);
    void          operator /=(const RedDataNumber& n);

    RedDataNumber& operator ++(); // Prefix
    RedDataNumber  operator ++(int); // Postfix

private:

    enum class TENumberType {eFloat=1, eInt=2};

    TENumberType    eNumType;
    int             iIntVal;
    double          dblFloatVal;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator ==(const RedDataNumber& lhs, const RedDataNumber& rhs);
bool operator !=(const RedDataNumber& lhs, const RedDataNumber& rhs);
bool operator >=(const RedDataNumber& lhs, const RedDataNumber& rhs);
bool operator <=(const RedDataNumber& lhs, const RedDataNumber& rhs);
bool operator  >(const RedDataNumber& lhs, const RedDataNumber& rhs);
bool operator  <(const RedDataNumber& lhs, const RedDataNumber& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDataNumber kNumberOne                 = RedDataNumber(1);
static const RedDataNumber kNumberFloatCompTollerance = RedDataNumber(kDefaultFloatCompareTollerance);
static const RedDataNumber kNumberZero                = RedDataNumber(0);
static const RedDataNumber kNumberMinusOne            = RedDataNumber(-1);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


