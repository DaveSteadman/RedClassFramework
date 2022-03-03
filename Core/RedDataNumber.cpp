// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedDataNumber.h"

namespace Red {
namespace Core {

// =================================================================================================
// Class Operations
// =================================================================================================

// Query operation, determining if the int number is zero, or the float number is within a tollerance of zero.
bool RedDataNumber::IsZero(void) const
{
    if (eNumType == TENumberType::eInt)
        return (iIntVal == 0);
    else
        return ( fabs(dblFloatVal) < kDefaultFloatCompareTollerance);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataNumber::IsPositive(void) const
{
    if (eNumType == TENumberType::eInt)
        return (iIntVal > 0);
    else
        return (dblFloatVal > 0.0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataNumber::IsEqualTo(const RedDataNumber& CheckVal) const
{
    // If Integers, just compare, no tollerance
    if ( IsInteger() && CheckVal.IsInteger() )
    {
        if (iIntVal == CheckVal.iIntVal)
            return true;
    }
    else
    {
        const double dVal = DoubleValue();

        // Add / Subtract the tollerance to create the bounds
        const double dUpperBounds = CheckVal.DoubleValue() + kDefaultFloatCompareTollerance;
        const double dLowerBounds = CheckVal.DoubleValue() - kDefaultFloatCompareTollerance;

        if ( (dLowerBounds < dVal) && (dVal < dUpperBounds) )
            return true;
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedDataNumber::IsEqualToWithinTollerance(const RedDataNumber& CheckVal, const RedDataNumber& tollerance) const
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

RedDataString RedDataNumber::DecimalString(void) const
{
    const int   iStrLen = 32;
    RedDataString   cRetStr;
    char        pChrBuf[iStrLen];

    // Initialise the string we're going to be using
    for(int i=0;i<iStrLen;i++) 
        pChrBuf[i] = '\0';

    // Assign the string depending on the type of the number
    if (eNumType == TENumberType::eInt)
        snprintf(pChrBuf, iStrLen, "%d", iIntVal);
    else
        snprintf(pChrBuf, iStrLen, "%f", dblFloatVal);

    // Copy the string into the output core string object
    cRetStr = pChrBuf;
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// @brief Convert the number into a string with specific formatting
// @param decimalplaces The number of characters after the decimal place.
RedDataString RedDataNumber::DecimalStringWithDP(const unsigned decimalplaces) const
{
    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];
    RedDataString  cRetStr;

    double     dblVal = 0.0;
    if (eNumType == TENumberType::eInt)
        dblVal = (double)iIntVal;
    else
        dblVal = dblFloatVal;

    snprintf(formatstr, iStrLen, "%%.%d%s", decimalplaces, "f");
    snprintf(numstr, iStrLen, formatstr, dblVal);

    // copy the string into the output core string object
    cRetStr = numstr;
    return cRetStr;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Convert the number into a string with specific formatting
// @param minchars      The minimum number of characters to make up the output string, including a decimal place.
// @param decimalplaces The number of characters after the decimal place.
RedDataString RedDataNumber::DecimalStringWithMinDigitsAndDP(const unsigned minchars, const unsigned decimalplaces) const
{
    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];
    RedDataString  cRetStr;

    double     dblVal = 0.0;
    if (eNumType == TENumberType::eInt)
        dblVal = (double)iIntVal;
    else
        dblVal = dblFloatVal;

    snprintf(formatstr, iStrLen, "%%0%d.%df", minchars, decimalplaces);
    snprintf(numstr, iStrLen, formatstr, dblVal);

    // copy the string into the output core string object
    cRetStr = numstr;
    return cRetStr;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataChar RedDataNumber::CharValue(void) const
{
    // define return value, self-initialised to \0
    RedDataChar cRetChar;

    if (eNumType == TENumberType::eInt)
    {
        if ((iIntVal > 0) && (iIntVal < 256))
            cRetChar.Set( (char)iIntVal );
    }

    return cRetChar;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedDataNumber::IntegerValue(void) const
{
    int iRetVal = 0;

    if (eNumType == TENumberType::eInt)
        iRetVal = iIntVal;
    else
        iRetVal = (int)dblFloatVal;

    return iRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

double RedDataNumber::DoubleValue(void) const
{
    double dblRetVal = 0.0;

    if (eNumType == TENumberType::eInt)
        dblRetVal = (double)iIntVal;
    else
        dblRetVal = dblFloatVal;

    return dblRetVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::MakePositive(void)
{
    if (eNumType == TENumberType::eInt)
        iIntVal = abs(iIntVal);
    else
        dblFloatVal = fabs(dblFloatVal);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::MakeNegative(void)
{
    if (eNumType == TENumberType::eInt)
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

RedDataNumber RedDataNumber::IntegerPart(void) const
{
    RedDataNumber r;
 
    if (eNumType == TENumberType::eInt)
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

RedDataNumber RedDataNumber::FractionalPart(void) const
{
    RedDataNumber r;

    if (eNumType == TENumberType::eInt)
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

// Return the integer part from the division of this number with another.
// Example: This = 3.14 & d = 2. Division Remainder returns 1.

RedDataNumber RedDataNumber::DivisionQuotient(const RedDataNumber& d) const
{
    RedDataNumber r;
 
    double param, intpart;
 
    double numerator   = dblFloatVal;
    double denominator = d.DoubleValue();
    param = numerator / denominator;
 
    modf (param , &intpart);
    r = intpart;
 
    return r;
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Return the remainder from the division of this number with another.
// Example: This = 3.14 & d = 2. Division Remainder returns 1.14.

RedDataNumber RedDataNumber::DivisionRemainder(const RedDataNumber& d) const
{
    RedDataNumber r;
 
    double numerator   = dblFloatVal;
    double denominator = d.DoubleValue();
    double remainder   = 0.0;
 
    remainder = fmod(numerator, denominator);
    r = remainder;
 
    return r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::SetDecimalString(const RedDataString& cNewDecimalVal)
{

    const char* txtptr = cNewDecimalVal.TextPtr();

    if (cNewDecimalVal.IsCharInString('.'))
    {
        eNumType    = TENumberType::eFloat;
        dblFloatVal = atof(txtptr);
        iIntVal     = 0;
    }
    else
    {
        eNumType    = TENumberType::eInt;
        iIntVal     = atoi(txtptr);
        dblFloatVal = 0.0;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Arithmetic Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataNumber::operator +(const RedDataNumber& n) const 
{
    RedDataNumber cReturnVal;

    if ((eNumType == TENumberType::eFloat) || (n.eNumType == TENumberType::eFloat))
    {
        cReturnVal.eNumType = TENumberType::eFloat;

        if (eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = (double)iIntVal;

        if (n.eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal += n.dblFloatVal;
        else
            cReturnVal.dblFloatVal += n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = TENumberType::eInt;
        cReturnVal.iIntVal  = iIntVal + n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataNumber::operator -(const RedDataNumber& n) const 
{
    RedDataNumber cReturnVal;

    if ((eNumType == TENumberType::eFloat) || (n.eNumType == TENumberType::eFloat))
    {
        cReturnVal.eNumType = TENumberType::eFloat;

        if (eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal -= n.dblFloatVal;
        else
            cReturnVal.dblFloatVal -= n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = TENumberType::eInt;
        cReturnVal.iIntVal  = iIntVal - n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataNumber::operator *(const RedDataNumber& n) const 
{
    RedDataNumber cReturnVal;

    if ((eNumType == TENumberType::eFloat) || (n.eNumType == TENumberType::eFloat))
    {
        cReturnVal.eNumType = TENumberType::eFloat;

        if (eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal *= n.dblFloatVal;
        else
            cReturnVal.dblFloatVal *= n.iIntVal;
    }
    else
    {
        cReturnVal.eNumType = TENumberType::eInt;
        cReturnVal.iIntVal  = iIntVal * n.iIntVal;
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataNumber::operator /(const RedDataNumber& n) const 
{
    RedDataNumber cReturnVal;

    if ((eNumType == TENumberType::eFloat) || (n.eNumType == TENumberType::eFloat))
    {
        cReturnVal.eNumType = TENumberType::eFloat;

        if (eNumType == TENumberType::eFloat)
            cReturnVal.dblFloatVal = dblFloatVal;
        else
            cReturnVal.dblFloatVal = iIntVal;

        if (n.eNumType == TENumberType::eFloat)
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
            cReturnVal.eNumType = TENumberType::eInt;
            cReturnVal.iIntVal  = iIntVal / n.iIntVal;
        }
        else
        {
            cReturnVal.eNumType = TENumberType::eFloat;
            cReturnVal.dblFloatVal  = ((double)iIntVal) / ((double)n.iIntVal);
        }
    }

    return cReturnVal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::operator +=(const RedDataNumber& n)
{
    RedDataNumber cRes = *this + n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::operator -=(const RedDataNumber& n)
{
    RedDataNumber cRes = *this - n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::operator *=(const RedDataNumber& n)
{
    RedDataNumber cRes = *this * n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedDataNumber::operator /=(const RedDataNumber& n)
{
    RedDataNumber cRes = *this / n;
    *this = cRes;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber& RedDataNumber::operator ++() // Prefix
{
    if (eNumType == TENumberType::eInt)
        iIntVal++;
    else
        dblFloatVal++;

    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataNumber::operator ++(int) // Postfix
{
    if (eNumType == TENumberType::eInt)
        iIntVal++;
    else
        dblFloatVal++;

    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (lhs.IsEqualTo(rhs))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (!lhs.IsEqualTo(rhs))
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator >=(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() >= rhs.IntegerValue());

    return (lhs.DoubleValue() >= rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator <=(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() <= rhs.IntegerValue());

    return (lhs.DoubleValue() <= rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator  >(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() > rhs.IntegerValue());

    return (lhs.DoubleValue() > rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator  <(const RedDataNumber& lhs, const RedDataNumber& rhs)
{
    if (lhs.IsInteger() && rhs.IsInteger())
        return (lhs.IntegerValue() < rhs.IntegerValue());

    return (lhs.DoubleValue() < rhs.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
