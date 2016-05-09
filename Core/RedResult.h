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

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class to represent a pass/fail of unknown tri-state value.
class RedResult
{
public:

    RedResult(void) { Init(); };

    void             Init(void)              { eState = eNoResult; };
    void             SetSuccess(void)        { eState = eSuccess;  };
    void             SetNoResult(void)       { eState = eNoResult; };
    void             SetFail(void)           { eState = eFail;     };

    bool             IsSuccess(void) const   { return (eState == eSuccess);  };
    bool             IsNoResult(void) const  { return (eState == eNoResult); };
    bool             IsFail(void) const      { return (eState == eFail);     };

    static RedResult Success(void)           { return RedResult(eSuccess);   };
    static RedResult NoResult(void)          { return RedResult(eNoResult);  };
    static RedResult Fail(void)              { return RedResult(eFail);      };

    const int        iState(void) const      { return (int)eState;           };

protected:

    typedef enum TEResult {
        eNoResult = 0,
        eSuccess,
        eFail
    } TEResult;

    RedResult(TEResult eNewState) { eState = eNewState; };

private:
    TEResult eState;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedResult& lhs, const RedResult& rhs);
bool operator!=(const RedResult& lhs, const RedResult& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedResult kResultSuccess  = RedResult::Success();
static const RedResult kResultNoResult = RedResult::NoResult();
static const RedResult kResultFail     = RedResult::Fail();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



