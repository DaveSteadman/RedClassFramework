// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILibRoutine.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

RedVSILibRoutine::RedVSILibRoutine(void)
{
    pCode = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSILibRoutine::IsMatching(RedVSIRoutineCallInterface& cSig)
{
    // Check the basics, that the routine name and the number of parameters match
    if (cName != cSig.FuncName()) return 0;
    if (cParamList.NumItems() != cSig.GetParams()->NumItems()) return 0;

    // Get the lists and iterators to perform the full param check
    
    RedVSIDataListIterator cCallParamIt(cSig.GetParams());
    RedVSIStringLangElementMapIterator cParamIt(&cParamList);
    cParamIt.First();
    cCallParamIt.First();

    // loop across all the parameters in both lists at the same time.
    // Stop looping when one of the iterators is done.    
    while ( (!cParamIt.IsDone()) && (!cCallParamIt.IsDone()))
    {
        // Get the type from the local parameter and the call parameter
        // return fail if they don't match.
        RedVSILangElement cCurrType      = cParamIt.CurrentData();
        RedVariant        cCurrCallParam = cCallParamIt.CurrentItem();

        RedVSILangElement cCurrCallParamType;
        if(cCurrCallParam.Type().IsBool()) cCurrCallParamType = kLangElementTypeBool;
        if(cCurrCallParam.Type().IsChar()) cCurrCallParamType = kLangElementTypeChar;
        if(cCurrCallParam.Type().IsStr())  cCurrCallParamType = kLangElementTypeString;
        if(cCurrCallParam.Type().IsNum())  cCurrCallParamType = kLangElementTypeNumber;

        // match the type of the current parameters
        if (cCurrCallParamType != cCurrType)
            return 0;

        // move thr iterators on
        cParamIt.Next();
        cCallParamIt.Next();
    }
    
    // the initial check guarantees the lists were the same length, so its
    // okay to return success at this point.
    return 1;    
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

