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

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class encapsulating a routine call. A container for a routine name and the parameters, as well
// as the initial class of object name.
class RedVSIRoutineSignature
{
public:

    // construction
    RedVSIRoutineSignature(void) { Init(); };
    ~RedVSIRoutineSignature()    { Init(); };
    void Init(void);

    // Signature Type
    void SetDynamic(void);
    void SetStatic(void);
    bool IsDynamic(void) const { return (sigType == TESignatureType::eDynamic); };
    bool IsStatic(void)  const { return (sigType == TESignatureType::eStatic);  };

    // Names
    void SetClassName(RedDataString cName)                    { cClassName = cName; };
    void SetFunctionName(RedDataString cName)                 { cFuncName  = cName; };
    void SetNames(RedDataString cCName, RedDataString cFName) { cClassName = cCName; cFuncName  = cFName; };
    RedDataString SetClassName(void) const                    { return cClassName; };
    RedDataString FunctionName(void) const                    { return cFuncName; };

    // Params
    void AddStaticParam(RedDataType cType, RedDataString cName);
    void AddDynamicParam(RedData* cValue);
    

    // String Output
    RedDataString StringView(void);

    // Operators
    void operator =(const RedVSIRoutineSignature& cSig);

private:

    enum class TESignatureType { eDynamic, eStatic };

    typedef RedLinkedList<RedData*>         TDynamicParamTypeList;
    typedef RedLinkedListIterator<RedData*> TDynamicParamTypeListIterator;

    typedef RedMapList<RedDataString, RedDataType>          TStaticParamTypeList;
    typedef RedMapListIterator<RedDataString, RedDataType>  TStaticParamTypeListIterator;

    RedDataString     cClassName;
    RedDataString     cFuncName;

    TESignatureType sigType = TESignatureType::eStatic;

    TDynamicParamTypeList   cDynamicParamList;
    TStaticParamTypeList    cStaticParamList;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

