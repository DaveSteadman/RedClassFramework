
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSILibClass.h"
#include "RedVSILibInterface.h"
#include "RedVSILibRoutineInterface.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSILib : public RedVSILibInterface
{
public:
    typedef RedDoubleLinkedList<RedVSILibClass*>          ListType;
    typedef RedDoubleLinkedListIterator<RedVSILibClass*>  IteratorType;

    void       AddClass(RedVSILibClass* pNewClass);
    void       DelClass(RedString& cClassName);

    // inherited
    RedVSILibClass*            FindClass(RedString cClassName);
    RedVSILibRoutineInterface* FindRoutine(RedVSIRoutineCallInterface& cSig);

    const int NumClasses(void) const { return cClassList.NumItems(); };

private:

    IteratorType GetClassIterator(void) { IteratorType cIt(&cClassList); return cIt; };

    ListType cClassList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

