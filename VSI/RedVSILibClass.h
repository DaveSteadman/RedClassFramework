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

#include "RedCoreNamespace.h"
#include "RedVSILibRoutine.h"
#include "RedVSIRoutineCallInterface.h"

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

// A VSI-Class consists of a Classname and a list of routines. Optionally, a VSI-Class may have a parent
// in which a routine call can continue to look for a routine signature.
class RedVSILibClass
{
public:

    typedef RedLinkedList<RedVSILibRoutine*>          RoutineListType;
    typedef RedLinkedListIterator<RedVSILibRoutine*>  RoutineIteratorType;

    // constructor
    RedVSILibClass(void)                               { cClassName = ""; cParentClassName=""; };
    RedVSILibClass(const RedDataString& cNewClassName) { cClassName=cNewClassName; cParentClassName=""; };

    void                SetClassName(const RedDataString& cNewClassName)             { cClassName = cNewClassName; };
    RedDataString       ClassName(void) const                                        { return cClassName; };

    void                SetParentClassName(const RedDataString& cNewParentClassName) { cParentClassName=cNewParentClassName; };
    RedDataString       ParentClassName(void) const                                  { return cParentClassName; };
    bool                HasParentClass(void) const                                   { return (!cParentClassName.IsEmpty()); };

    void                AddRoutine(RedVSILibRoutine* pNewRoutine);
    RedVSILibRoutine*   FindRoutine(const RedVSIRoutineCallInterface& cSig);
    RedVSILibRoutine*   FindRoutineByName(const RedDataString& cNewRoutineName);

    RoutineIteratorType GetRoutineIterator(void) { RoutineIteratorType cIt(&cRoutineList); return cIt; };

private:

    RedDataString    cClassName;
    RedDataString    cParentClassName;
    RoutineListType  cRoutineList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
