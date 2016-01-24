
#pragma once

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedResult
{
public:

    RedResult(void)        { Init(); };

    void Init(void)        { eState = eNoResult; };

    void SetSuccess(void)  { eState = eSuccess; };
    void SetNoResult(void) { eState = eNoResult; };
    void SetFail(void)     { eState = eFail; };

    const int IsSuccess(void) const   { return (eState == eSuccess); };
    const int IsNoResult(void) const  { return (eState == eNoResult); };
    const int IsFail(void) const      { return (eState == eFail); };

    static RedResult Success(void)  { return RedResult(eSuccess); };
    static RedResult NoResult(void) { return RedResult(eNoResult); };
    static RedResult Fail(void)     { return RedResult(eFail);};

    const int iState(void) const { return (int)eState; };

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

} // Core
} // Red



