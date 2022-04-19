// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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
#include "RedVSICollections.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class encapsulating a routine call. A container for a routine name and the parameters, as well
// as the initial class of object name.
class RedVSIRoutineCallInterface
{
public:

    // construction
    RedVSIRoutineCallInterface(void) { Init(); };
    ~RedVSIRoutineCallInterface()    { cParams.DelAll(); };

    void            Init(void) { cClassName.Init(); cObjName.Init(); cFuncName.Init(); cParams.DelAll(); };

    void            SetupObjectCall(const RedDataString& cNewObjName,   const RedDataString& cNewFuncName) { cObjName   = cNewObjName;   cFuncName = cNewFuncName; };
    void            SetupClassCall (const RedDataString& cNewClassName, const RedDataString& cNewFuncName) { cClassName = cNewClassName; cFuncName = cNewFuncName; };

    void            SetupCall(const RedDataString& cNewClassName, const RedDataString& cNewObjName, const RedDataString& cNewFuncName) { cClassName = cNewClassName; cObjName = cNewObjName; cFuncName = cNewFuncName; };


    void            SetClassName   (const RedDataString& cNewClassName)    { cClassName = cNewClassName;  };
    void            SetObjectName  (const RedDataString& cNewObjectName)   { cObjName   = cNewObjectName; };
    void            SetFuncName    (const RedDataString& cNewFuncName)     { cFuncName  = cNewFuncName;   };
    RedDataString   ClassName      (void)                            const { return cClassName; };
    RedDataString   ObjectName     (void)                            const { return cObjName;   };
    RedDataString   FuncName       (void)                            const { return cFuncName;  };

    const RedVSIVariantList* Params(void)                                  const { return &cParams; };
    void                   AddParam(const RedDataVariant& newParam)       { cParams.AddLast(newParam); };

    void operator =(const RedVSIRoutineCallInterface& cSig);

protected:

    RedDataString     cClassName;
    RedDataString     cObjName;
    RedDataString     cFuncName;
    RedVSIVariantList cParams;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

