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

#include "RedDataActions.h"
#include "RedTokenPredefMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromType(RedDataType cType)
{
    if (cType.IsBool())    return kIOStringKeywordBool;
    if (cType.IsChar())    return kIOStringKeywordChar;
    if (cType.IsList())    return kIOStringKeywordList;
    if (cType.IsNum())     return kIOStringKeywordNumber;
    if (cType.IsRecord())  return kIOStringKeywordRecord;
    if (cType.IsStr())     return kIOStringKeywordString;
    if (cType.IsVariant()) return kIOStringKeywordVariant;
    if (cType.IsVoid())    return kIOStringKeywordVoid;

    return "<Undefined>";
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromNumber(RedDataNumber cNum)
{
    if (cNum.IsInteger())
        return RedDataActions::StringFromInt(cNum.IntegerValue());
    else
        return RedDataActions::StringFromDouble(cNum.DoubleValue());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromInt(int iNum)
{
    const int       iStrLen = 32;
    RedDataString   cRetStr;
    char            pChrBuf[iStrLen];

    // Initialise the string we're going to be using
    for (int i = 0; i < iStrLen; i++)
        pChrBuf[i] = '\0';

    // Assign the string depending on the type of the number
    snprintf(pChrBuf, iStrLen, "%d", iNum);

    // Copy the string into the output core string object
    cRetStr = pChrBuf;
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromIntWithMinDigits(int iNum, unsigned mindigits)
{
    RedDataString cRetStr;

    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];

    snprintf(formatstr, iStrLen, "%%0%dd", mindigits);
    snprintf(numstr, iStrLen, formatstr, iNum);
    cRetStr = numstr;

    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromDouble(double dblNum)
{
    const int       iStrLen = 32;
    RedDataString   cRetStr;
    char            pChrBuf[iStrLen];

    // Initialise the string we're going to be using
    for (int i = 0; i < iStrLen; i++)
        pChrBuf[i] = '\0';

    // Assign the string depending on the type of the number
    snprintf(pChrBuf, iStrLen, "%f", dblNum);

    // Copy the string into the output core string object
    cRetStr = pChrBuf;
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::StringFromDoubleWithDP(double dblNum, unsigned dp)
{
    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];
    RedDataString  cRetStr;

    if (dp > 0)
    {
        snprintf(formatstr, iStrLen, "%%.%df", dp);
        snprintf(numstr, iStrLen, formatstr, dblNum);
        cRetStr = numstr;
    }
    else
    {
        cRetStr = StringFromInt((int)round(dblNum));
    }
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// mindigits = number of numbers ahead of the '.'
// dp = number of numbers after the '.'
// so (13.5, 3, 3) = 013.500
// for snprintf thats %07.3. 7 = the 3+3 + a 1

RedDataString RedDataActions::StringFromDoubleWithMinDigitsAndDP(double dblNum, unsigned mindigits, unsigned dp)
{
    const int      iStrLen = 32;
    char           formatstr[iStrLen];
    char           numstr[iStrLen];
    RedDataString  cRetStr;

    const unsigned digits = mindigits + dp + 1;

    if (dp > 0)
    {
        snprintf(formatstr, iStrLen, "%%0%d.%df", digits, dp);
        snprintf(numstr, iStrLen, formatstr, dblNum);
        cRetStr = numstr;
    }
    else
    {
        cRetStr = StringFromIntWithMinDigits((int)round(dblNum), mindigits);
    }
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::HexadecimalStringFromInt(unsigned iNum)
{
    RedDataString  cRetStr;

    const int  iStrLen = 32;
    char       numstr[iStrLen];

    snprintf(numstr, iStrLen, "0x%x", iNum);
    cRetStr = numstr;

    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedDataActions::HexadecimalStringFromIntWithMinDigits(unsigned iNum, unsigned mindigits)
{
    RedDataString cRetStr;

    const int  iStrLen = 32;
    char       formatstr[iStrLen];
    char       numstr[iStrLen];

    snprintf(formatstr, iStrLen, "0x%%0%dx", mindigits);
    snprintf(numstr, iStrLen, formatstr, iNum);
    cRetStr = numstr;

    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// String To Number
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataNumber RedDataActions::NumberFromString(RedDataString cStrNum)
{
    const char* txtptr = cStrNum.TextPtr();
    RedDataNumber cRetNum;

    if (cStrNum.IsCharInString('.'))
        cRetNum = atof(txtptr);
    else
        cRetNum = atoi(txtptr);

    return cRetNum;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

