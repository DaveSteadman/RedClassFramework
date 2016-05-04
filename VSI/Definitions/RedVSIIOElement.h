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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Definition of the Language IO Elements. This defines the tokens which are
// required to input a textual representations of the language.
// This type covers elements such as brackets and punctuation which are 
// removed in the translation to the internal RedVSILangElement type.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSIIOElement
{
public:

    // Constructor
    RedVSIIOElement(void) { Init(); };
    void Init(void);

    // Locations
    const bool             IsLocationKeyword(void) const;
    const bool             IsKeywordAttribute(void) const                 { return eType == eKeywordAttribute; };
    const bool             IsKeywordStack(void) const                     { return eType == eKeywordStack; };
    const bool             IsKeywordHeap(void) const                      { return eType == eKeywordHeap; };
    static RedVSIIOElement KeywordAttribute(void)                         { return RedVSIIOElement(eKeywordAttribute); };
    static RedVSIIOElement KeywordStack(void)                             { return RedVSIIOElement(eKeywordStack); };
    static RedVSIIOElement KeywordHeap(void)                              { return RedVSIIOElement(eKeywordHeap); };

    // Types
    const bool             IsTypeKeyword(void) const;
    const bool             IsKeywordArray(void) const                     { return eType == eKeywordArray; };
    const bool             IsKeywordBool(void) const                      { return eType == eKeywordBool; };
    const bool             IsKeywordChar(void) const                      { return eType == eKeywordChar; };
    const bool             IsKeywordNumber(void) const                    { return eType == eKeywordNumber; };
    const bool             IsKeywordString(void) const                    { return eType == eKeywordString; };
    static RedVSIIOElement KeywordArray(void)                             { return RedVSIIOElement(eKeywordArray); };
    static RedVSIIOElement KeywordBool(void)                              { return RedVSIIOElement(eKeywordBool); };
    static RedVSIIOElement KeywordChar(void)                              { return RedVSIIOElement(eKeywordChar); };
    static RedVSIIOElement KeywordNumber(void)                            { return RedVSIIOElement(eKeywordNumber); };
    static RedVSIIOElement KeywordString(void)                            { return RedVSIIOElement(eKeywordString); };

    // Commands
    const bool             IsCommandKeyword(void) const;
    const bool             IsKeywordNew(void) const                       { return eType == eKeywordNew; };
    const bool             IsKeywordLet(void) const                       { return eType == eKeywordLet; };
    const bool             IsKeywordIf(void) const                        { return eType == eKeywordIf; };
    const bool             IsKeywordThen(void) const                      { return eType == eKeywordThen; };
    const bool             IsKeywordElse(void) const                      { return eType == eKeywordElse; };
    const bool             IsKeywordEndif(void) const                     { return eType == eKeywordEndif; };
    const bool             IsKeywordWhile(void) const                     { return eType == eKeywordWhile; };
    const bool             IsKeywordLoop(void) const                      { return eType == eKeywordLoop; };
    const bool             IsKeywordEndloop(void) const                   { return eType == eKeywordEndloop; };
	const bool             IsKeywordPrint(void) const                     { return eType == eKeywordPrint; };
	const bool             IsKeywordReturn(void) const                    { return eType == eKeywordReturn; };
    static RedVSIIOElement KeywordNew(void)                               { return RedVSIIOElement(eKeywordNew); };
    static RedVSIIOElement KeywordLet(void)                               { return RedVSIIOElement(eKeywordLet); };
    static RedVSIIOElement KeywordIf(void)                                { return RedVSIIOElement(eKeywordIf); };
    static RedVSIIOElement KeywordThen(void)                              { return RedVSIIOElement(eKeywordThen); };
    static RedVSIIOElement KeywordElse(void)                              { return RedVSIIOElement(eKeywordElse); };
    static RedVSIIOElement KeywordEndif(void)                             { return RedVSIIOElement(eKeywordEndif); };
    static RedVSIIOElement KeywordWhile(void)                             { return RedVSIIOElement(eKeywordWhile); };
    static RedVSIIOElement KeywordLoop(void)                              { return RedVSIIOElement(eKeywordLoop); };
    static RedVSIIOElement KeywordEndloop(void)                           { return RedVSIIOElement(eKeywordEndloop); };
	static RedVSIIOElement KeywordPrint(void)                             { return RedVSIIOElement(eKeywordPrint); };
	static RedVSIIOElement KeywordReturn(void)                            { return RedVSIIOElement(eKeywordReturn); };

    // Bool values
    const bool             IsBoolKeyword(void) const;
    const bool             IsKeywordTrue(void) const                      { return eType == eKeywordBoolValueTrue; };
    const bool             IsKeywordFalse(void) const                     { return eType == eKeywordBoolValueFalse; };
    const bool             IsKeywordYes(void) const                       { return eType == eKeywordBoolValueYes; };
    const bool             IsKeywordNo(void) const                        { return eType == eKeywordBoolValueNo; };
    static RedVSIIOElement KeywordTrue(void)                              { return RedVSIIOElement(eKeywordBoolValueTrue); };
    static RedVSIIOElement KeywordFalse(void)                             { return RedVSIIOElement(eKeywordBoolValueFalse); };
    static RedVSIIOElement KeywordYes(void)                               { return RedVSIIOElement(eKeywordBoolValueYes); };
    static RedVSIIOElement KeywordNo(void)                                { return RedVSIIOElement(eKeywordBoolValueNo); };

    // Library
    const bool             IsLibraryKeyword(void) const;
    static RedVSIIOElement KeywordName(void)                              { return RedVSIIOElement(eKeywordName); };
    static RedVSIIOElement KeywordClass(void)                             { return RedVSIIOElement(eKeywordClass); };
    static RedVSIIOElement KeywordRoutine(void)                           { return RedVSIIOElement(eKeywordRoutine); };
    static RedVSIIOElement KeywordCode(void)                              { return RedVSIIOElement(eKeywordCode); };
    static RedVSIIOElement KeywordParams(void)                            { return RedVSIIOElement(eKeywordParams); };
    static RedVSIIOElement KeywordParent(void)                            { return RedVSIIOElement(eKeywordParent); };
    const bool             IsKeywordName(void) const                      { return eType == eKeywordName; };
    const bool             IsKeywordClass(void) const                     { return eType == eKeywordClass; };
    const bool             IsKeywordRoutine(void) const                   { return eType == eKeywordRoutine; };
    const bool             IsKeywordCode(void) const                      { return eType == eKeywordCode; };
    const bool             IsKeywordParams(void) const                    { return eType == eKeywordParams; };
    const bool             IsKeywordParent(void) const                    { return eType == eKeywordParent; };

    // Operators and separators
    const bool             IsOperatorSymbol(void) const;
    const bool             IsAssignOpSymbol(void) const;
    const bool             IsLogicOpSymbol(void) const;
    const bool             IsBinaryLogicOpSymbol(void) const;
    const bool             IsCompareOpSymbol(void) const;
    const bool             IsBinaryOpSymbol(void) const;
    const bool             IsSeparatorSymbol(void) const;

    const bool             IsSymbolAssignDivide(void) const               { return eType == eSymbolAssignDivide; };
    const bool             IsSymbolAssignEqual(void) const                { return eType == eSymbolAssignEqual; };
    const bool             IsSymbolAssignMinus(void) const                { return eType == eSymbolAssignMinus; };
    const bool             IsSymbolAssignMultiply(void) const             { return eType == eSymbolAssignMultiply; };
    const bool             IsSymbolAssignPlus(void) const                 { return eType == eSymbolAssignPlus; };
    const bool             IsSymbolCompareEqual(void) const               { return eType == eSymbolCompareEqual; };
    const bool             IsSymbolCompareNotEqual(void) const            { return eType == eSymbolCompareNotEqual; };
    const bool             IsSymbolCompareLessThan(void) const            { return eType == eSymbolCompareLessThan; };
    const bool             IsSymbolCompareGreaterThan(void) const         { return eType == eSymbolCompareGreaterThan; };
    const bool             IsSymbolCompareLessThanOrEqual(void) const     { return eType == eSymbolCompareLessThan; };
    const bool             IsSymbolCompareGreaterThanOrEqual (void) const { return eType == eSymbolCompareGreaterThan; };
    const bool             IsSymbolLogicAnd(void) const                   { return eType == eSymbolLogicAnd; };
    const bool             IsSymbolLogicOr(void) const                    { return eType == eSymbolLogicOr; };
    const bool             IsSymbolLogicNot(void) const                   { return eType == eSymbolLogicNot; };
    const bool             IsSymbolDivide(void) const                     { return eType == eSymbolDivide; };
    const bool             IsSymbolMinus(void) const                      { return eType == eSymbolMinus; };
    const bool             IsSymbolMultiply(void) const                   { return eType == eSymbolMultiply; };
    const bool             IsSymbolPlus(void) const                       { return eType == eSymbolPlus; };
    const bool             IsSymbolPower(void) const                      { return eType == eSymbolPower; };
    const bool             IsSymbolStringContent(void) const              { return eType == eSymbolStringContent; };
    const bool             IsSymbolOpenBracket(void) const                { return eType == eSymbolOpenBracket; };
    const bool             IsSymbolCloseBracket(void) const               { return eType == eSymbolCloseBracket; };
    const bool             IsSymbolComma(void) const                      { return eType == eSymbolComma; };
    const bool             IsSymbolPeriod(void) const                     { return eType == eSymbolPeriod; };
    const bool             IsSymbolDoubleColon(void) const                { return eType == eSymbolDoubleColon; };
    const bool             IsSymbolEOF(void) const                        { return eType == eSymbolEOF; };
    static RedVSIIOElement SymbolAssignDivide(void)                       { return RedVSIIOElement(eSymbolAssignDivide); };
    static RedVSIIOElement SymbolAssignEqual(void)                        { return RedVSIIOElement(eSymbolAssignEqual); };
    static RedVSIIOElement SymbolAssignMinus(void)                        { return RedVSIIOElement(eSymbolAssignMinus); };
    static RedVSIIOElement SymbolAssignMultiply(void)                     { return RedVSIIOElement(eSymbolAssignMultiply); };
    static RedVSIIOElement SymbolAssignPlus(void)                         { return RedVSIIOElement(eSymbolAssignPlus); };
    static RedVSIIOElement SymbolCompareEqual(void)                       { return RedVSIIOElement(eSymbolCompareEqual); };
    static RedVSIIOElement SymbolCompareNotEqual(void)                    { return RedVSIIOElement(eSymbolCompareNotEqual); };
    static RedVSIIOElement SymbolCompareLessThan(void)                    { return RedVSIIOElement(eSymbolCompareLessThan); };
    static RedVSIIOElement SymbolCompareGreaterThan(void)                 { return RedVSIIOElement(eSymbolCompareGreaterThan); };
    static RedVSIIOElement SymbolCompareLessThanOrEqual(void)             { return RedVSIIOElement(eSymbolCompareLessThanOrEqual); };
    static RedVSIIOElement SymbolCompareGreaterThanOrEqual(void)          { return RedVSIIOElement(eSymbolCompareGreaterThanOrEqual); };
    static RedVSIIOElement SymbolLogicAnd(void)                           { return RedVSIIOElement(eSymbolLogicAnd); };
    static RedVSIIOElement SymbolLogicOr(void)                            { return RedVSIIOElement(eSymbolLogicOr); };
    static RedVSIIOElement SymbolLogicNot(void)                           { return RedVSIIOElement(eSymbolLogicNot); };
    static RedVSIIOElement SymbolDivide(void)                             { return RedVSIIOElement(eSymbolDivide); };
    static RedVSIIOElement SymbolMinus(void)                              { return RedVSIIOElement(eSymbolMinus); };
    static RedVSIIOElement SymbolMultiply(void)                           { return RedVSIIOElement(eSymbolMultiply); };
    static RedVSIIOElement SymbolPlus(void)                               { return RedVSIIOElement(eSymbolPlus); };
    static RedVSIIOElement SymbolPower(void)                              { return RedVSIIOElement(eSymbolPower); };
    static RedVSIIOElement SymbolStringContent(void)                      { return RedVSIIOElement(eSymbolStringContent); };
    static RedVSIIOElement SymbolOpenBracket(void)                        { return RedVSIIOElement(eSymbolOpenBracket); };
    static RedVSIIOElement SymbolCloseBracket(void)                       { return RedVSIIOElement(eSymbolCloseBracket); };
    static RedVSIIOElement SymbolComma(void)                              { return RedVSIIOElement(eSymbolComma); };
    static RedVSIIOElement SymbolPeriod(void)                             { return RedVSIIOElement(eSymbolPeriod); };
    static RedVSIIOElement SymbolDoubleColon(void)                        { return RedVSIIOElement(eSymbolDoubleColon); };
    static RedVSIIOElement SymbolEOF(void)                                { return RedVSIIOElement(eSymbolEOF); };

    // Operators
    void operator =(const RedVSIIOElement cNewVal)                        { eType=cNewVal.eType; };

    const int iElem(void) const { return (int)eType; };

private:

    typedef enum TELangElem
    {
        eDefaultInvalid = 0,

        // Locations
        eKeywordAttribute,
        eKeywordStack,
        eKeywordHeap,

        // Types
        eKeywordArray,
        eKeywordBool,
        eKeywordChar,
        eKeywordNumber,
        eKeywordString,

        // Library
        eKeywordName,
        eKeywordClass,
        eKeywordRoutine,
        eKeywordCode,
        eKeywordParams,
        eKeywordParent,

        // Commands
        eKeywordNew,
        eKeywordLet,
        eKeywordIf,
        eKeywordThen,
        eKeywordElse,
        eKeywordEndif,
        eKeywordWhile,
        eKeywordLoop,
        eKeywordEndloop,
		eKeywordPrint,
        eKeywordReturn,

        // Bool Values
        eKeywordBoolValueTrue,
        eKeywordBoolValueFalse,
        eKeywordBoolValueYes,
        eKeywordBoolValueNo,

        // Operators and separators
        eSymbolAssignDivide,
        eSymbolAssignEqual,
        eSymbolAssignMinus,
        eSymbolAssignMultiply,
        eSymbolAssignPlus,
        eSymbolCompareEqual,
        eSymbolCompareNotEqual,
        eSymbolCompareLessThan,
        eSymbolCompareGreaterThan,
        eSymbolCompareLessThanOrEqual,
        eSymbolCompareGreaterThanOrEqual,
        eSymbolLogicAnd,
        eSymbolLogicOr,
        eSymbolLogicNot,
        eSymbolDivide,
        eSymbolMinus,
        eSymbolMultiply,
        eSymbolPlus,
        eSymbolPower,
        eSymbolStringContent,
        eSymbolOpenBracket,
        eSymbolCloseBracket,
        eSymbolComma,
        eSymbolPeriod,
        eSymbolDoubleColon,

        eSymbolEOF
    } TELangElem;
    
    RedVSIIOElement(TELangElem eNewType) { eType = eNewType; };

    TELangElem eType;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVSIIOElement& lhs, const RedVSIIOElement& rhs);
bool operator!=(const RedVSIIOElement& lhs, const RedVSIIOElement& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red




