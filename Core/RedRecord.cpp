
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




