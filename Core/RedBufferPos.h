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

#include "RedDataNumber.h"
#include "RedDataString.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class for the position within a buffer. Generates a small string for logging.
class RedBufferPos
{
public:

    RedBufferPos(void) { iRow=0; iCol=0; };
    RedBufferPos(const unsigned iNewRow, const unsigned iNewCol) { iRow=iNewRow; iCol=iNewCol; };

    void Init(void) { iRow = 0; iCol = 0; };

    unsigned Row(void) const { return iRow.IntegerValue(); };
    unsigned Col(void) const { return iCol.IntegerValue(); };

    RedDataString PosText(void) { RedDataString x="(row:" + iRow.DecimalString() + ", col:" + iCol.DecimalString() + ")"; return x; };

    void operator =(const RedBufferPos cNewPos) { iRow = cNewPos.iRow; iCol = cNewPos.iCol; };

private:
    RedDataNumber iRow;
    RedDataNumber iCol;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
} // Core
} // Red


