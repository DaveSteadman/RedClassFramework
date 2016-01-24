
#pragma once

#include "RedCoreNamespace.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSITokenType
{
public:
	RedVSITokenType(void)       { Init(); };

	void Init(void)             { eState = eDefaultInvalid; };

    void SetNumber(void)        { eState = eNumber; };
    void SetName(void)          { eState = eName; };
    void SetStringLiteral(void) { eState = eStringLiteral; };
    void SetNonPrintable(void)  { eState = eNonPrintable; };
    void SetWhitespace(void)    { eState = eWhitespace; };
    void SetPredefined(void)    { eState = ePredefined; };

	int IsValid(void)           { return (eState != eDefaultInvalid); };
	int IsNumber(void)          { return (eState == eNumber); };
	int IsName(void)            { return (eState == eName); };
	int IsStringLiteral(void)   { return (eState == eStringLiteral); };
	int IsNonPrintable(void)    { return (eState == eNonPrintable); };
	int IsWhitespace(void)      { return (eState == eWhitespace); };
	int IsPredefined(void)      { return (eState == ePredefined); };

    static RedVSITokenType Number(void)        { return RedVSITokenType(eNumber); };
    static RedVSITokenType Name(void)          { return RedVSITokenType(eName); };
    static RedVSITokenType StringLiteral(void) { return RedVSITokenType(eStringLiteral); };
    static RedVSITokenType NonPrintable(void)  { return RedVSITokenType(eNonPrintable); };
    static RedVSITokenType Whitespace(void)    { return RedVSITokenType(eWhitespace); };
    static RedVSITokenType Predefined(void)    { return RedVSITokenType(ePredefined); };

protected:

    enum TETokenType
    {
        eDefaultInvalid, 
        eNumber, 
        eName,
        eStringLiteral,
        eNonPrintable,
        eWhitespace,
        ePredefined
    };

    RedVSITokenType(TETokenType eNewState) { eState = eNewState; };

private:
    int eState;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
