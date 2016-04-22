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

#include "RedString.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class for dates formatted in YYYYMMDD format, ie 2013/10/20. Component values are all unsigned.
class RedDate
{
public:

    RedDate(void) { Init(); };
    RedDate(const unsigned y, const unsigned m, const unsigned d) { SetDate(y,m,d); };
    void Init(void) { SetDate(2000, 01, 01); };

    void SetDate(const unsigned y, const unsigned m, const unsigned d) { year=y; month=m; date=d; };
    void SetDate(const RedString& datestr);
    void Today(void);

	// Simple Accessors
	void           SetYear(const unsigned y)  { year  = y; };
	void           SetMonth(const unsigned m) { month = m; };
	void           SetDate(const unsigned d)  { date  = d; };
	const unsigned Year(void) const           { return year; };
	const unsigned Month(void) const          { return month; };
    const unsigned Date(void) const           { return date; };

	// Involved Accessors
    const unsigned TwoDigitYear(void) const   { return (year % 100); }
	const unsigned EightDigitDate(void) const;
	const unsigned SixDigitDate(void) const;

	// String output
	const RedString DateString(void) const;
	const RedString EightDigitDateString(void) const { RedString r; r.Append(EightDigitDate()); return r; };
	const RedString SixDigitDateString(void)   const { RedString r; r.Append(SixDigitDate());   return r; };

private:

    unsigned    year;
    unsigned    month;
    unsigned    date;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedDate& lhs, const RedDate& rhs);
bool operator!=(const RedDate& lhs, const RedDate& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDate kDateZero = RedDate(0000, 01, 01);
static const RedDate kDate2000 = RedDate(2000, 01, 01);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



