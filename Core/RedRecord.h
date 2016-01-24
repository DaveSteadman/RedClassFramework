
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
    const RedDataType Type(void) const { return RedDataType::Record(); };
    RedType*          Clone(void) const;
    void              Init(void) { pAttribList->DelAll(); };

    // Create And Add
    void        CloneAndAdd (const RedString& cNewAttribName, RedType* pNewAttrib) { pAttribList->Add(cNewAttribName,              pNewAttrib->Clone()); };
    void        CloneAndAdd (const char* strNewAttribName,    RedType* pNewAttrib) { pAttribList->Add(RedString(strNewAttribName), pNewAttrib->Clone()); };
    void        Add         (const RedString& cNewAttribName, RedType* pNewAttrib) { pAttribList->Add(cNewAttribName,              pNewAttrib); };
    void        Add         (const char* strNewAttribName,    RedType* pNewAttrib) { pAttribList->Add(RedString(strNewAttribName), pNewAttrib); };
    RedType*    CreateAndAdd(const RedString& cNewAttribName, const RedDataType& NewAttribType);
    RedType*    CreateAndAdd(const char* strNewAttribName,    const RedDataType& NewAttribType);
    RedType*    CreateObjectOfType(const RedDataType& NewAttribType);

    // Locate
    int         Find(const RedString& cAttribName, RedType*& pData)       { return pAttribList->Find(cAttribName, pData); };

    // Remove
    void        Del(const RedString& cNewAttribName)                      { pAttribList->Del(cNewAttribName); };
    void        DelAll(void)                                              { pAttribList->DelAll(); };

    // Operators
    void operator =(const RedRecord& cNewVal);

private:

    typedef RedMapList<RedString, RedType*>           RedStringDataMap;
    typedef RedMapListIterator<RedString, RedType*>   RedStringDataMapIterator;

    // Attributes
    RedStringDataMap* pAttribList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
