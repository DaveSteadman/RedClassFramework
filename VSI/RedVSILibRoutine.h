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

#include "RedDataString.h"
#include "RedVSICmd.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// A VSI-Routine consists of a Routine-name, and a list of parameters which together make up its signature.
class RedVSILibRoutine
{
public:

    RedVSILibRoutine(void);
    void Init(void);
    bool IsValid(void) const;

    unsigned                    NumParams(void) { return cParamList.NumItems(); };
    RedVSIStringLangElementMap* Params(void) { return &cParamList; };
    void                        AddParam(const RedDataString& cParamName, RedVSILangElement cType) { cParamList.Add(cParamName, cType); };

    void    SetCode (RedVSICmd* pNewCode) { pCode = pNewCode; };
    RedVSICmd* FirstCommand(void) { return pCode; };

    void GetDetails(RedDataString& cOutName, RedVSIStringLangElementMap& cOutParamList, RedVSICmd*& pOutCode);

    bool    IsMatching(const RedVSIRoutineCallInterface& cSig);

public: 
    RedDataString               cName = "";

protected:
    
    RedVSIStringLangElementMap  cParamList;
    RedVSICmd*         pCode = NULL;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

