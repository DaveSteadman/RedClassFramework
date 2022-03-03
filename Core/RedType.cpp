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

#include "RedType.h"

#include "RedDataBoolean.h"
#include "RedDataChar.h"
#include "RedDataList.h"
#include "RedDataNumber.h"
#include "RedDataRecord.h"
#include "RedDataString.h"
#include "RedDataVariant.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedType::NewRedObj(const RedDataType eType)
{
    RedType* retData = NULL;

    if      (eType.IsBool())    retData = new RedDataBoolean;
    else if (eType.IsChar())    retData = new RedDataChar;
    else if (eType.IsList())    retData = new RedDataList;
    else if (eType.IsNum())     retData = new RedDataNumber;
    else if (eType.IsRecord())  retData = new RedDataRecord;
    else if (eType.IsStr())     retData = new RedDataString;
    else if (eType.IsVariant()) retData = new RedDataVariant;

    return retData;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




