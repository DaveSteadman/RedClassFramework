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

    sigType = TESignatureType::eStatic;

    cDynamicParamList.DelAll();
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
        cDynamicParamList.AddLast(cValue->Clone());
    }
    else
    {
        throw; // Exception, shouldn't be doing this.
    }
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

        TDynamicParamTypeListIterator cIt(&cDynamicParamList);
        cIt.First();
        while (!cIt.IsDone())
        {
            RedData* pCurrData = cIt.CurrentItem();

            cRetStr += RedDataActions::StringFromType(pCurrData->Type());

            // Move on, and add a comma if not at the end
            cIt.Next();
            if ((!cIt.IsDone()))
                cRetStr += ", ";
        }

    }
    //
    //cIt.First();
    //while (!cIt.IsDone())
    //{
    //    RedDataType* pCurrDataType = cIt.CurrentItem();
    //    
    //    cRetStr += RedDataActions::StringFromType(*pCurrDataType);
    //    
    //    // Move on, and add a comma if not at the end
    //    cIt.Next();
    //    if ((!cIt.IsDone()))
    //        cRetStr += ", ";
    //}

    cRetStr += ")";

    return cRetStr;
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
