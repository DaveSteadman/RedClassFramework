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

#include "RedVSIRoutineSignature.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::Init(void)
{ 
    cClassName.Init();
    cFuncName.Init();

    cDynamicParamList.DelAll();

    sigType = TESignatureType::eStatic;

    cStaticParamList.DelAll();
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::SetDynamic(void)
{
    if (sigType == TESignatureType::eStatic)
    {
        cDynamicParamList.DelAll();
        cStaticParamList.DelAll();

        sigType = TESignatureType::eDynamic;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::SetStatic(void)
{
    if (sigType == TESignatureType::eDynamic)
    {
        cDynamicParamList.DelAll();
        cStaticParamList.DelAll();

        sigType = TESignatureType::eStatic;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::AddStaticParam(RedDataType cType, RedDataString cName)
{
    if (sigType == TESignatureType::eStatic)
    {
        cStaticParamList.Add(cName, cType);
    }
    else
    {
        throw; // Exception, shouldn't be doing this.
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::AddDynamicParam(RedData* cValue)
{
    if (sigType == TESignatureType::eDynamic)
    {
        cDynamicParamList.CloneAndAdd(cValue);
    }
    else
    {
        throw; // Exception, shouldn't be doing this.
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedVSIRoutineSignature::NumParams(void)
{
    if (sigType == TESignatureType::eDynamic)
        return cDynamicParamList.NumItems();
    else
        return cStaticParamList.NumItems();

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSIRoutineSignature::StringView(void)
{
    RedDataString cRetStr;

    cRetStr = cClassName;
    cRetStr += "::";
    cRetStr += cFuncName;
    cRetStr += "(";
    
    if (sigType == TESignatureType::eStatic)
    {
        TStaticParamTypeListIterator cIt(&cStaticParamList);
        cIt.First();
        while (!cIt.IsDone())
        {
            RedDataString cCurrName     = cIt.CurrentId();
            RedDataType   cCurrDataType = cIt.CurrentData();

            cRetStr += RedDataActions::StringFromType(cCurrDataType);
            cRetStr += " ";
            cRetStr += cCurrName;

            // Move on, and add a comma if not at the end
            cIt.Next();
            if ((!cIt.IsDone()))
                cRetStr += ", ";
        }
    }
    else
    {
        const unsigned iFirst = cDynamicParamList.FirstIndex();
        const unsigned iLast  = cDynamicParamList.LastIndex();

        for(unsigned i=iFirst; i<=iLast; i++)
        {
            RedData* pCurrData = cDynamicParamList.PtrForIndex(i);
            if (pCurrData != NULL)
                cRetStr += RedDataActions::StringFromType(pCurrData->Type());
            else
                cRetStr += "<NULLPTR>";

            // Add the comma if not the last item
            if (i <iLast ) cRetStr += ", ";
        }
    }

    // Finish and return
    cRetStr += ")";
    return cRetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSIRoutineSignature::CallComparison(RedVSIRoutineSignature& cStaticSig, RedVSIRoutineSignature& cDynamicSig)
{
    // Basic setup check
    if (cStaticSig.IsDynamic()) return false;
    if (cDynamicSig.IsStatic()) return false;

    // Name check
    if (cStaticSig.cClassName != cDynamicSig.cClassName) return false;
    if (cStaticSig.cFuncName  != cDynamicSig.cFuncName)  return false;

    // Param numbers
    if (cStaticSig.NumParams() != cDynamicSig.NumParams()) return false;

    // param type compare
    const unsigned nump = cStaticSig.NumParams();

    const unsigned iFirst = cDynamicSig.cDynamicParamList.FirstIndex();
    const unsigned iLast  = cDynamicSig.cDynamicParamList.LastIndex();
    RedDataType cStaticParamType;
    bool readSuccess = false;

    for(unsigned i=iFirst; i<=iLast; i++)
    {
        RedData* pCurrDynamic = cDynamicSig.cDynamicParamList.PtrForIndex(i);
        readSuccess = cStaticSig.cStaticParamList.FindDataByIndex(i, cStaticParamType);

        // If we read params okay
        if ((readSuccess) && (pCurrDynamic != NULL))
        {
            // If the param types don't match, we fail
            if (pCurrDynamic->Type() != cStaticParamType)
                return false;
        }
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineSignature::operator =(const RedVSIRoutineSignature& cSig)
{
    cClassName     = cSig.cClassName;
    cFuncName      = cSig.cFuncName;
    //cParamTypeList = cSig.cParamTypeList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
