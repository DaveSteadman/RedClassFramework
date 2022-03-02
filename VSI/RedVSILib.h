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

#include "RedCoreNamespace.h"

#include "RedVSILibClass.h"
#include "RedVSILibRoutineInterface.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// A VSI Code Library consists of a list of classes.
class RedVSILib
{
public:
    typedef RedDoubleLinkedList<RedVSILibClass*>          ListType;
    typedef RedDoubleLinkedListIterator<RedVSILibClass*>  IteratorType;

    void       AddClass(RedVSILibClass* pNewClass);
    void       DelClass(const RedDataString& cClassName);

    // Find routines not const, as they may lead to the library loading a class from file.
    RedVSILibClass*            FindClass(const RedDataString& cClassName);
    RedVSILibRoutineInterface* FindRoutine(const RedVSIRoutineCallInterface& cSig);
    RedVSILibRoutineInterface* FindRoutine(const RedDataString& cClassName, const RedDataString& cRoutineName);

    // Returns number of classes in library
    unsigned NumClasses(void) const { return cClassList.NumItems(); };

    void SetLibFilePath(const RedDataString& newlibpath) { LibFilePath = newlibpath; };

private:

    IteratorType GetClassIterator(void) { IteratorType cIt(&cClassList); return cIt; };

    bool DoesClassFileExist(const RedDataString& classname);

    ListType  cClassList;
    RedDataString LibFilePath;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

