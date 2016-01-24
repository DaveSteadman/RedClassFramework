
#pragma once

#include "RedNumber.h"
#include "RedString.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class for the position within a buffer.
class RedBufferPos
{
public:

    RedBufferPos(void) { iRow=0; iCol=0; };
    RedBufferPos(int iNewRow, int iNewCol) { iRow=iNewRow; iCol=iNewCol; };

    int GetRow(void) { return iRow.IntegerValue(); };
    int GetCol(void) { return iCol.IntegerValue(); };

    RedString PosText(void) { RedString x="(row:" + iRow.DecimalString() + ", col:" + iCol.DecimalString() + ")"; return x; };

    void operator =(const RedBufferPos cNewPos) { iRow = cNewPos.iRow; iCol = cNewPos.iCol; };

private:
    RedNumber iRow;
    RedNumber iCol;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
} // Core
} // Red


