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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedType.h"
#include "RedString.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedRecord : public RedType
{
public:

    RedRecord(void);
    ~RedRecord(void) { delete pAttribList; };

    // Inherited: RedType
    RedDataType Type(void) const { return RedDataType::Record(); };
    RedType*          Clone(void) const;
    void              Init(void) { pAttribList->DelAll(); };

    // Create And Add
    void        CloneAndAdd (const RedString& cNewAttribName, const RedType* pNewAttrib) { pAttribList->Add(cNewAttribName,              pNewAttrib->Clone()); };
    void        CloneAndAdd (const char* strNewAttribName,    const RedType* pNewAttrib) { pAttribList->Add(RedString(strNewAttribName), pNewAttrib->Clone()); };
    void        Add         (const RedString& cNewAttribName, RedType* pNewAttrib)       { pAttribList->Add(cNewAttribName,              pNewAttrib); };
    void        Add         (const char* strNewAttribName,    RedType* pNewAttrib)       { pAttribList->Add(RedString(strNewAttribName), pNewAttrib); };
    RedType*    CreateAndAdd(const RedString& cNewAttribName, const RedDataType& NewAttribType);
    RedType*    CreateAndAdd(const char* strNewAttribName,    const RedDataType& NewAttribType);

    // Locate
    bool        Find(const RedString& cAttribName, RedType*& pData)       { return pAttribList->Find(cAttribName, pData); };

    // Remove
    void        Del(const RedString& cNewAttribName)                      { pAttribList->Del(cNewAttribName); };
    void        DelAll(void)                                              { pAttribList->DelAll(); };

    unsigned    NumItems(void) const { return pAttribList->NumItems(); };

    // Operators
    void operator =(const RedRecord& cNewVal);

private:

    RedType* CreateObjectOfType(const RedDataType& NewAttribType);

    typedef RedMapList<RedString, RedType*>           RedStringDataMap;
    typedef RedMapListIterator<RedString, RedType*>   RedStringDataMapIterator;

    // Attributes
    RedStringDataMap* pAttribList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
