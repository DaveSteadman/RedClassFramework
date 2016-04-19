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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "RedNumber.h"

namespace Red {
namespace Core {

// =================================================================================================
// Class Operations
// =================================================================================================

/// Query operation, determining if the int number is zero, or the float number is within kFloatCompTollerance of zero.
const bool RedNumber::IsZero(void) const
{
    if (eNumType == eInt)
        return (iIntVal == 0);
    else
        return ( fabs(dblFloatVal) < kFloatCompTollerance );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedNumber::IsPositive(void) const
{
    if (eNumType == eInt)
        return (iIntVal > 0);
    else
        return (dblFloatVal > 0.0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedNumber::IsEqualTo(const RedNumber& CheckVal) const
{
    // If Integers, just compare, no tollerance
    if ( IsInteger() && CheckVal.IsInteger() )
    {
        if (iIntVal == CheckVal.iIntVal)
            return true;
    }
    else
    {
        const double dVal      = DoubleValue();

        // Add / Subtract the tollerance to create the bounds
        const double dUpperBounds = CheckVal.DoubleValue() + kFloatCompTollerance;
        const double dLowerBounds = CheckVal.DoubleValue() - kFloatCompTollerance;

        if ( (dLowerBounds < dVal) && (dVal < dUpperBounds) )
            return true;
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedNumber::IsEqualToWithinTollerance(const RedNumber& CheckVal, const RedNumber& tollerance) const
{
    // If Integers, just compare, no tollerance
    if ( IsInteger() && CheckVal.IsInteger() )
    {
        if (iIntVal == CheckVal.iIntVal)
            return true;
    }
    else
    {
        // Else, convert both values to double
        const double dVal      = DoubleValue();
        const double checkdVal = CheckVal.DoubleValue();
        const double dToll     = tollerance.DoubleValue();

        // Add / Subtract the tollerance to create the bounds
        const double dUpperBounds = checkdVal + dToll;
        const double dLowerBounds = checkdVal - dToll;

        if ( (dLowerBounds < dVal) && (dVal < dUpperBounds) )
            return true;
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedNumber::DecimalString(void) const
{
    const int   iStrLen = 32;
    RedString   cRetStr;
    char        pChrBuf[iStrLen];

    // initialise the string we're going to be using
    for(int i=0;i<iStrLen;i++) 
        pChrBuf[i] = '\0';

    // assign the string depending on the type of the number
    if (eNumType == eInt)
        snprintf(pChrBuf, iStrLen, "%d", iIntVal);
    else
        snprintf(pChrBuf, iStrLen, "%f", dblFloatVal);

    // copy the string into the output core string object
    cRetStr = pChrBuf;
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedString RedNumber::DecimalStringWithDP(const int decimalplaces) const
{
    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];
    RedString  cRetStr;


    if (eNumType == eInt)
    {
        snprintf(numstr, iStrLen, "%d", iIntVal);
    }
    else
    {
        snprintf(formatstr, iStrLen, "%%.%d%s", decimalplaces, "f");
        snprintf(numstr, iStrLen, formatstr, dblFloatVal);
    }

    // copy the string into the output core string object
    cRetStr = numstr;
    return cRetStr;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedChar RedNumber::CharValue(void) const
{
    // define return value, self-initialised to \0
    RedChar cRetChar;

    if (eNumType == eInt)
    {
        if ((iIntVal > 0) && (iIntVal < 256))
            cRetChar.Set( (char)iIntVal );
    }

    return cRetChar;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedNumber::IntegerValue(void) const
{
    int iRetVal = 0;

    if (eNumType == eInt)
        iRetVal = iIntVal;
    else
        iRetVal = (int)dblFloatVal;

    return iRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const double RedNumber::DoubleValue(void) const
{
    double dblRetVal = 0.0;

    if (eNumType == eInt)
        dblRetVal = (double)iIntVal;
    else
        dblRetVal = dblFloatVal;

    return dblRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::MakePositive(void)
{
    if (eNumType == eInt)
        iIntVal = abs(iIntVal);
    else
        dblFloatVal = fabs(dblFloatVal);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::MakeNegative(void)
{
    if (eNumType == eInt)
    {
        if (iIntVal > 0)
            iIntVal *= -1;
    }
    else
    {
        if (dblFloatVal > 0.0)
            dblFloatVal *= -1.0;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedNumber::IntegerPart(void) const
{
    RedNumber r;
 
    if (eNumType == eInt)
    {
        r = iIntVal;
    }
    else
    {
        double param, intpart;
 
        param = dblFloatVal;
        modf (param , &intpart);
 
        r = intpart;
    }
    return r;   
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedNumber RedNumber::FractionalPart(void) const
{
    RedNumber r;

    if (eNumType == eInt)
    {
        r = 0;
    }
    else
    {
        double param, fractpart, intpart;
 
       param = dblFloatVal;
        fractpart = modf (param , &intpart);
 
        r = fractpart;
    }
    return r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Return the integer part from the division of this number with another.
/// Example: This = 3.14 & d = 2. Division Remainder returns 1.

const RedNumber RedNumber::DivisionQuotient(const RedNumber& d) const
{
    RedNumber r;
 
    double param, intpart;
 
    double numerator   = dblFloatVal;
    double denominator = d.DoubleValue();
    param = numerator / denominator;
 
    modf (param , &intpart);
    r = intpart;
 
    return r;
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Return the remainder from the division of this number with another.
/// Example: This = 3.14 & d = 2. Division Remainder returns 1.14.

const RedNumber RedNumber::DivisionRemainder(const RedNumber& d) const
{
    RedNumber r;
 
    double numerator   = dblFloatVal;
    double denominator = d.DoubleValue();
    double remainder   = 0.0;
 
    remainder = fmod(numerator, denominator);
    r = remainder;
 
    return r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::SetDecimalString(const RedString& cNewDecimalVal)
{

    const char* txtptr = cNewDecimalVal.TextPtr();

    if (cNewDecimalVal.IsCharInString('.'))
    {
        eNumType    = eFloat;
        dblFloatVal = atof(txtptr);
        iIntVal     = 0;
    }
    else
    {
        eNumType    = eInt;
        iIntVal     = atoi(txtptr);
        dblFloatVal = 0.0;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Arithmetic Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber RedNumber::operator +(const RedNumber& n) const 
{
    RedNumber cReturnVal;

    if ((eNumType == eFloat) || (n.eNumType == eFloat))
    {
        cReturnVal.eNumType = eFloat;

        if (eNumType == eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = (double)iIntVal;

        if (n.eNumType == eFloat)
            cReturnVal.dblFloatVal += n.dblFloatVal;
        else
            cReturnVal.dblFloatVal += n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = eInt;
        cReturnVal.iIntVal  = iIntVal + n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber RedNumber::operator -(const RedNumber& n) const 
{
    RedNumber cReturnVal;

    if ((eNumType == eFloat) || (n.eNumType == eFloat))
    {
        cReturnVal.eNumType = eFloat;

        if (eNumType == eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == eFloat)
            cReturnVal.dblFloatVal -= n.dblFloatVal;
        else
            cReturnVal.dblFloatVal -= n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = eInt;
        cReturnVal.iIntVal  = iIntVal - n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber RedNumber::operator *(const RedNumber& n) const 
{
    RedNumber cReturnVal;

    if ((eNumType == eFloat) || (n.eNumType == eFloat))
    {
        cReturnVal.eNumType = eFloat;

        if (eNumType == eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == eFloat)
            cReturnVal.dblFloatVal *= n.dblFloatVal;
        else
            cReturnVal.dblFloatVal *= n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = eInt;
        cReturnVal.iIntVal  = iIntVal * n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber RedNumber::operator /(const RedNumber& n) const 
{
    RedNumber cReturnVal;

    if ((eNumType == eFloat) || (n.eNumType == eFloat))
    {
        cReturnVal.eNumType = eFloat;

        if (eNumType == eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == eFloat)
            cReturnVal.dblFloatVal /= n.dblFloatVal;
        else
            cReturnVal.dblFloatVal /= n.iIntVal;
    }
    else
    {
        // if the two numbers are integer and produce an integer result, do it,
        // else produce a floating point result.
        if ((iIntVal % n.iIntVal) == 0)
        {
            cReturnVal.eNumType = eInt;
            cReturnVal.iIntVal  = iIntVal / n.iIntVal;
        }
        else
        {
            cReturnVal.eNumType = eFloat;
            cReturnVal.dblFloatVal  = ((double)iIntVal) / ((double)n.iIntVal);
        }
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::operator +=(const RedNumber& n)
{
    RedNumber cRes = *this + n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::operator -=(const RedNumber& n)
{
    RedNumber cRes = *this - n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::operator *=(const RedNumber& n)
{
    RedNumber cRes = *this * n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedNumber::operator /=(const RedNumber& n)
{
    RedNumber cRes = *this / n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber& RedNumber::operator ++() // Prefix
{
    if (eNumType == eInt)
        iIntVal++;
    else
        dblFloatVal++;

    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedNumber RedNumber::operator ++(int) // Postfix
{
    if (eNumType == eInt)
        iIntVal++;
    else
        dblFloatVal++;

    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedNumber& lhs, const RedNumber& rhs)
{
    if (lhs.IsEqualTo(rhs))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedNumber& lhs, const RedNumber& rhs)
{
    if (!lhs.IsEqualTo(rhs))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator >=(const RedNumber& lhs, const RedNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() >= rhs.IntegerValue());

    return (lhs.DoubleValue() >= rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <=(const RedNumber& lhs, const RedNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() <= rhs.IntegerValue());

    return (lhs.DoubleValue() <= rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator  >(const RedNumber& lhs, const RedNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() > rhs.IntegerValue());

    return (lhs.DoubleValue() > rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator  <(const RedNumber& lhs, const RedNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() < rhs.IntegerValue());

    return (lhs.DoubleValue() < rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
