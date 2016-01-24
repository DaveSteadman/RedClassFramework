
#include "RedBufferOutput.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Loop through each character in the new string, adding each character in turn.
// Wherever we see a crlf, we'll also insert the current indentation level.

void RedBufferOutput::AppendIndented(const RedString& cStr)
{
    const int NumLines = cStr.NumLines();

    // Check we have a multi-line input
    WriteNewLineWithIndent();

    RedString currLineStr;
    for (int currLineindex=1; currLineindex<=NumLines; currLineindex++)
    {
        cStr.LineAtNum(currLineindex, currLineStr);

        cStrBuffer.Append(currLineStr);

        // Write newlines and indents up to the last line
        if (currLineindex<NumLines) WriteNewLineWithIndent();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


