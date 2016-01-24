
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSILibRoutine.h"
#include "RedVSIRoutineCallInterface.h"
#include "RedVSILibInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

class RedVSILibClass
{
public:

    typedef RedLinkedList<RedVSILibRoutine*>          RoutineListType;
    typedef RedLinkedListIterator<RedVSILibRoutine*>  RoutineIteratorType;

    // constructor
    RedVSILibClass(void)                           { cClassName = ""; cParentClassName=""; };
    RedVSILibClass(const RedString& cNewClassName) { cClassName=cNewClassName; cParentClassName=""; };

    void                SetClassName(const RedString& cNewClassName)             { cClassName = cNewClassName; };
    RedString           ClassName(void) const                                    { return cClassName; };

    void                SetParentClassName(const RedString& cNewParentClassName) { cParentClassName=cNewParentClassName; };
    RedString           ParentClassName(void) const                              { return cParentClassName; };
    int                 HasParentClass(void) const                               { return (!cParentClassName.IsEmpty()); };

    void                AddRoutine(RedVSILibRoutine* pNewRoutine);
    RedVSILibRoutine*   FindRoutine(RedVSIRoutineCallInterface& cSig);
    RoutineIteratorType GetRoutineIterator(void) { RoutineIteratorType cIt(&cRoutineList); return cIt; };
    
private:

    RedString        cClassName;
    RedString        cParentClassName;
    RoutineListType  cRoutineList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
