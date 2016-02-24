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

#include "RedCoreNamespace.h"
#include "RedVSICollections.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

/// Class encapsulating a routine call. A container for a routine name and the parameters, as well
/// as the initial class of object name.
class RedVSIRoutineCallInterface
{
public:

    // construction
    RedVSIRoutineCallInterface(void) { Init(); };
    ~RedVSIRoutineCallInterface()    { cParams.DelAll(); };

    void            Init(void) { cClassName.Init(); cObjName.Init(); cFuncName.Init(); cParams.DelAll(); };

    void            SetupObjectCall(const RedString& cNewObjName,   const RedString& cNewFuncName) { cObjName   = cNewObjName;   cFuncName = cNewFuncName; };
    void            SetupClassCall( const RedString& cNewClassName, const RedString& cNewFuncName) { cClassName = cNewClassName; cFuncName = cNewFuncName; };

    void            SetClassName (const RedString& cNewClassName)  { cClassName = cNewClassName;  };
    void            SetObjectName(const RedString& cNewObjectName) { cObjName   = cNewObjectName; };
    void            SetFuncName  (const RedString& cNewFuncName)   { cFuncName  = cNewFuncName;   };

    // Query
    //const int          IsInternalCall(void) const { return ( (cObjName.IsEmpty()) && (cClassName.IsEmpty()) ); };
    const RedString    ClassName(void)   const { return cClassName; };
    const RedString    ObjectName(void)  const { return cObjName;   };
    const RedString    FuncName(void)    const { return cFuncName;  };

    void               AppendParam(RedVariant& cNewParam) { cParams.AddLast(cNewParam); };
    const RedVSIDataList*    GetParams(void) const              { return &cParams; };

    void operator =(RedVSIRoutineCallInterface& cSig);
    
private:

    RedString         cClassName;
    RedString         cObjName;
    RedString         cFuncName;
    RedVSIDataList    cParams;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red



