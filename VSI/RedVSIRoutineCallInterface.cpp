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

#include "RedVSIRoutineCallInterface.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIRoutineCallInterface::operator =(const RedVSIRoutineCallInterface& cSig)
{
    cClassName     = cSig.cClassName;
    cFuncName      = cSig.cFuncName;
    cParamTypeList = cSig.cParamTypeList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSIRoutineCallInterface::StringView(void)
{
    RedDataString cRetStr;

    cRetStr = cClassName;
    cRetStr += "::";
    cRetStr += "cFuncName";
    cRetStr += "(";
    
    TParamTypeListIterator cIt = TParamTypeListIterator(cParamTypeList);
    cIt.First();
    while (!cIt.IsDone())
    {
        RedDataString* pCurrStr = cIt.CurrentItem();
        
        cRetStr += *pCurrStr;
        
        // Move on, and add a comma if not at the end
        cIt.Next();
        if ((!cIt.IsDone()))
            cRetStr += ", ";
    }

    cRetStr += ")";
}

} // VSI
} // Red
