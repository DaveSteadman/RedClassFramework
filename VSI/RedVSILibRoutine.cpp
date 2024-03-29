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

#include "RedVSILibRoutine.h"
#include "RedVSIRoutineSignature.h"

namespace Red {
namespace VSI {

RedVSILibRoutine::RedVSILibRoutine(void)
{
    pCode = NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibRoutine::Init(void)
{
    cName.Init();
    cParamList.DelAll();
    delete pCode;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSILibRoutine::ParamTypeString(void) 
{ 
    RedDataString retStr = "(";

    const unsigned firstindex = cParamList.FirstIndex();
    const unsigned lastindex  = cParamList.FirstIndex();

    for (unsigned CurrParamIndex = firstindex; CurrParamIndex <= lastindex; CurrParamIndex++)
    {
        RedDataString CurrLibParamName;
        RedDataType   CurrLibDataType;

        cParamList.FindIdByIndex(CurrParamIndex, CurrLibParamName);
        cParamList.FindDataByIndex(CurrParamIndex, CurrLibDataType);
        
        retStr += RedDataActions::StringFromType(CurrLibDataType);
        retStr += " ";
        retStr += CurrLibParamName;

        // if not last element, add a comma
        if (CurrParamIndex < lastindex)
            retStr += ", ";
    }
    retStr += ")";

    return retStr;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedVSILibRoutine::IsMatching(const RedVSIRoutineSignature& cSig)
{
    //if (cName != cSig.cFuncName)
    //    return false;

    //RedVSIStringLangElementMap* LibParamList  = Params();
    //const RedVSIRoutineSignature::TParamTypeList*    CallParamList = cSig.cParamTypeList;

    //if (LibParamList->NumItems() != CallParamList->NumItems())
    //    return false;

    //unsigned CallParamIndex = CallParamList->FirstIndex();

    //RedDataString         CurrLibParamName;
    //RedVSILangElement CurrLibDataType;
    //RedDataVariant        CurrCallParam;

    //for (unsigned LibParamIndex = LibParamList->FirstIndex(); LibParamIndex <= LibParamList->LastIndex(); LibParamIndex++)
    //{
    //    LibParamList->FindIdByIndex(LibParamIndex,   CurrLibParamName);
    //    LibParamList->FindDataByIndex(LibParamIndex, CurrLibDataType);

    //    CallParamList->FindElementAtIndex(CallParamIndex, CurrCallParam);
    //}

//    // Check the basics, that the routine name and the number of parameters match
//    if (cName != cSig.FuncName()) return 0;
//    if (cParamList.NumItems() != cSig.GetParams()->NumItems()) return 0;
//
//    // Get the lists and iterators to perform the full param check
//    
//    RedVSIVariantListIterator cCallParamIt(cSig.GetParams());
//    RedVSIStringLangElementMapIterator cParamIt(&cParamList);
//    cParamIt.First();
//    cCallParamIt.First();
//
//    // loop across all the parameters in both lists at the same time.
//    // Stop looping when one of the iterators is done.    
//    while ( (!cParamIt.IsDone()) && (!cCallParamIt.IsDone()))
//    {
//        // Get the type from the local parameter and the call parameter
//        // return fail if they don't match.
//        RedVSILangElement cCurrType      = cParamIt.CurrentData();
//        RedDataVariant        cCurrCallParam = cCallParamIt.CurrentItem();
//
//        RedVSILangElement cCurrCallParamType;
//        if (cCurrCallParam.Type().IsBool()) cCurrCallParamType = kLangElementTypeBool;
//        if (cCurrCallParam.Type().IsChar()) cCurrCallParamType = kLangElementTypeChar;
//        if (cCurrCallParam.Type().IsStr())  cCurrCallParamType = kLangElementTypeString;
//        if (cCurrCallParam.Type().IsNum())  cCurrCallParamType = kLangElementTypeNumber;
//
//        // match the type of the current parameters
//        if (cCurrCallParamType != cCurrType)
//            return 0;
//
//        // move thr iterators on
//        cParamIt.Next();
//        cCallParamIt.Next();
//    }
//    
//    // the initial check guarantees the lists were the same length, so its
//    // okay to return success at this point.
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibRoutine::GetDetails(RedDataString& cOutName, RedVSIParamTypeList& cOutParamList, RedVSICmd*& pOutCode)
{
    cOutName      = cName;
    cOutParamList = cParamList;
    pOutCode      = pCode;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

