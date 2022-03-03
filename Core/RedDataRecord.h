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

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedDataString.h"
#include "RedDataNumber.h"
#include "RedDataBoolean.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedDataRecord : public RedType
{
public:

    RedDataRecord(void)  { pAttribList = new RedDataStringDataMap; };
    ~RedDataRecord(void) { pAttribList->DelAll(); delete pAttribList; };

    // Inherited: RedType
    RedDataType Type(void) const { return RedDataType::Record(); };
    RedType*    Clone(void) const;
    void        Init(void) { pAttribList->DelAll(); };

    // Generic Add
    void        CloneAndAdd (const RedDataString& cNewAttribName, const RedType* pNewAttrib) { pAttribList->Add(cNewAttribName, pNewAttrib->Clone()); };
    void        AddByPtr(const RedDataString& cNewAttribName, RedType* pNewAttrib)           { pAttribList->Add(cNewAttribName, pNewAttrib); };

    // Generic add operations
    RedType*    CreateAddReturn(const RedDataString& cNewAttribName, const RedDataType& NewAttribType);
    RedType*    CreateAddReturn(const char* strNewAttribName,        const RedDataType& NewAttribType);

    // Shortcut add operations
    void        AddByValue(const RedDataString& cNewAttribName, const int iVal)     { pAttribList->Add(cNewAttribName, new RedDataNumber(iVal));  };
    void        AddByValue(const RedDataString& cNewAttribName, const char* strVal) { pAttribList->Add(cNewAttribName, new RedDataString(strVal)); };
    void        AddByValue(const RedDataString& cNewAttribName, const bool bVal)    { pAttribList->Add(cNewAttribName, new RedDataBoolean(bVal)); };

    // Locate
    bool        FindFieldPtr(const RedDataString& cAttribName, RedType*& pData) { return pAttribList->FindDataById(cAttribName, pData); };

    RedDataType TypeForName(const RedDataString& cAttribName);
    RedType*    PtrForName (const RedDataString& cAttribName);

    // Remove
    void        Del(const RedDataString& cNewAttribName)          { pAttribList->Del(cNewAttribName); };
    void        DelAll(void)                                      { pAttribList->DelAll(); };

    unsigned    NumItems(void) const { return pAttribList->NumItems(); };

    // Operators
    void operator =(const RedDataRecord& cNewVal);

private:

    typedef RedMapList<RedDataString, RedType*>           RedDataStringDataMap;
    typedef RedMapListIterator<RedDataString, RedType*>   RedDataStringDataMapIterator;

    // Attributes
    RedDataStringDataMap* pAttribList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
