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

#include "RedRecord.h"
#include "RedBoolean.h"
#include "RedChar.h"
#include "RedNumber.h"
#include "RedString.h"
#include "RedVariant.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Construction
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedRecord::RedRecord(void)
{
    pAttribList = new RedStringDataMap();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inhertied
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedRecord::Clone(void) const 
{
    RedRecord* pNewObj = new RedRecord();

    // delete the attrib list, replacing it with a cloned one.
    delete[] pNewObj->pAttribList;
    pNewObj->pAttribList = pAttribList->Clone();

    return (RedType*)pNewObj;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedRecord::CreateAndAdd(const RedString& cNewAttribName, const RedDataType& NewAttribType)
{
    RedType* retData = CreateObjectOfType(NewAttribType);

    pAttribList->Add(cNewAttribName, retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedRecord::CreateAndAdd(const char* strNewAttribName, const RedDataType& NewAttribType)
{
    RedType* retData = CreateObjectOfType(NewAttribType);

    pAttribList->Add(RedString(strNewAttribName), retData);

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedType* RedRecord::CreateObjectOfType(const RedDataType& NewAttribType)
{
    RedType* retData = REDNULL;

    if      (NewAttribType.IsBool())    retData = new RedBoolean;
    else if (NewAttribType.IsChar())    retData = new RedChar;
    else if (NewAttribType.IsNum())     retData = new RedNumber;
    else if (NewAttribType.IsStr())     retData = new RedString;
    else if (NewAttribType.IsVariant()) retData = new RedVariant;

    return retData;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedRecord::operator =(const RedRecord& cNewVal)
{
    Init();

    delete pAttribList;
    pAttribList = cNewVal.pAttribList->Clone();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




