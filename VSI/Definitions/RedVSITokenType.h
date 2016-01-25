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

#include "RedCoreNamespace.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSITokenType
{
public:
	RedVSITokenType(void)                      { Init(); };
	
	void Init(void)                            { eState = eDefaultInvalid; };
	
	void SetNumber(void)                       { eState = eNumber; };
	void SetName(void)                         { eState = eName; };
	void SetStringLiteral(void)                { eState = eStringLiteral; };
	void SetNonPrintable(void)                 { eState = eNonPrintable; };
	void SetWhitespace(void)                   { eState = eWhitespace; };
	void SetPredefined(void)                   { eState = ePredefined; };
	
	int IsValid(void) const                    { return (eState != eDefaultInvalid); };
	int IsNumber(void) const                   { return (eState == eNumber); };
	int IsName(void) const                     { return (eState == eName); };
	int IsStringLiteral(void) const            { return (eState == eStringLiteral); };
	int IsNonPrintable(void) const             { return (eState == eNonPrintable); };
	int IsWhitespace(void) const               { return (eState == eWhitespace); };
	int IsPredefined(void) const               { return (eState == ePredefined); };
	
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
