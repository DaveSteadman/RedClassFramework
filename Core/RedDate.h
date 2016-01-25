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

namespace Red {
namespace Core {

class RedString;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class for dates formatted in YYYYMMDD format, ie 2013/10/10. Component values are all unsigned.
class RedDate
{
public:

    RedDate(void) { Init(); };
    RedDate(const unsigned y, const unsigned m, const unsigned d) { SetDate(y,m,d); };
    void Init(void) { SetDate(2000, 01, 01); };

    void SetDate(const unsigned y, const unsigned m, const unsigned d) { year=y; month=m; date=d; };
    void SetDate(const RedString& datestr);
    void Now(void);

    const RedString DateString(void) const;
    const int       EightDigitInt(void) const;

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



