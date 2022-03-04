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


namespace Red {
namespace VSI {

// Definition of the Language IO Elements. This defines the tokens which are
// required to input a textual representations of the language.
// This type covers elements such as brackets and punctuation which are
// removed in the translation to the internal RedVSILangElement type.
class RedVSIIOElement
{
public:

    // Constructor
    RedVSIIOElement(void) { Init(); };
    void Init(void);

    // Locations
    bool                   IsLocationKeyword(void) const;
    bool                   IsKeywordAttribute(void) const                 { return eType == eKeywordAttribute; };
    bool                   IsKeywordStack(void) const                     { return eType == eKeywordStack; };
    bool                   IsKeywordHeap(void) const                      { return eType == eKeywordHeap; };
    static RedVSIIOElement KeywordAttribute(void)                         { return RedVSIIOElement(eKeywordAttribute); };
    static RedVSIIOElement KeywordStack(void)                             { return RedVSIIOElement(eKeywordStack); };
    static RedVSIIOElement KeywordHeap(void)                              { return RedVSIIOElement(eKeywordHeap); };

    // Types
    bool                   IsTypeKeyword(void) const;
    bool                   IsKeywordBool(void) const                      { return eType == eKeywordBool; };
    bool                   IsKeywordChar(void) const                      { return eType == eKeywordChar; };
    bool                   IsKeywordList(void) const                      { return eType == eKeywordList; };
    bool                   IsKeywordNumber(void) const                    { return eType == eKeywordNumber; };
    bool                   IsKeywordRecord(void) const                    { return eType == eKeywordRecord; };
    bool                   IsKeywordString(void) const                    { return eType == eKeywordString; };
    static RedVSIIOElement KeywordBool(void)                              { return RedVSIIOElement(eKeywordBool); };
    static RedVSIIOElement KeywordChar(void)                              { return RedVSIIOElement(eKeywordChar); };
    static RedVSIIOElement KeywordList(void)                              { return RedVSIIOElement(eKeywordList); };
    static RedVSIIOElement KeywordNumber(void)                            { return RedVSIIOElement(eKeywordNumber); };
    static RedVSIIOElement KeywordRecord(void)                            { return RedVSIIOElement(eKeywordRecord); };
    static RedVSIIOElement KeywordString(void)                            { return RedVSIIOElement(eKeywordString); };

    // Commands
    bool                   IsCommandKeyword(void) const;
    bool                   IsKeywordNew(void) const                       { return eType == eKeywordNew; };
    bool                   IsKeywordLet(void) const                       { return eType == eKeywordLet; };
    bool                   IsKeywordIf(void) const                        { return eType == eKeywordIf; };
    bool                   IsKeywordThen(void) const                      { return eType == eKeywordThen; };
    bool                   IsKeywordElse(void) const                      { return eType == eKeywordElse; };
    bool                   IsKeywordEndif(void) const                     { return eType == eKeywordEndif; };
    bool                   IsKeywordWhile(void) const                     { return eType == eKeywordWhile; };
    bool                   IsKeywordLoop(void) const                      { return eType == eKeywordLoop; };
    bool                   IsKeywordEndloop(void) const                   { return eType == eKeywordEndloop; };
    bool                   IsKeywordLog(void) const                       { return eType == eKeywordLog; };
    bool                   IsKeywordReturn(void) const                    { return eType == eKeywordReturn; };
    static RedVSIIOElement KeywordNew(void)                               { return RedVSIIOElement(eKeywordNew); };
    static RedVSIIOElement KeywordLet(void)                               { return RedVSIIOElement(eKeywordLet); };
    static RedVSIIOElement KeywordIf(void)                                { return RedVSIIOElement(eKeywordIf); };
    static RedVSIIOElement KeywordThen(void)                              { return RedVSIIOElement(eKeywordThen); };
    static RedVSIIOElement KeywordElse(void)                              { return RedVSIIOElement(eKeywordElse); };
    static RedVSIIOElement KeywordEndif(void)                             { return RedVSIIOElement(eKeywordEndif); };
    static RedVSIIOElement KeywordWhile(void)                             { return RedVSIIOElement(eKeywordWhile); };
    static RedVSIIOElement KeywordLoop(void)                              { return RedVSIIOElement(eKeywordLoop); };
    static RedVSIIOElement KeywordEndloop(void)                           { return RedVSIIOElement(eKeywordEndloop); };
    static RedVSIIOElement KeywordLog(void)                               { return RedVSIIOElement(eKeywordLog); };
    static RedVSIIOElement KeywordReturn(void)                            { return RedVSIIOElement(eKeywordReturn); };

    // Bool values
    bool                   IsBoolKeyword(void) const;
    bool                   IsKeywordTrue(void) const                      { return eType == eKeywordBoolValueTrue; };
    bool                   IsKeywordFalse(void) const                     { return eType == eKeywordBoolValueFalse; };
    static RedVSIIOElement KeywordTrue(void)                              { return RedVSIIOElement(eKeywordBoolValueTrue); };
    static RedVSIIOElement KeywordFalse(void)                             { return RedVSIIOElement(eKeywordBoolValueFalse); };

    // Library
    bool                   IsLibraryKeyword(void) const;
    static RedVSIIOElement KeywordName(void)                              { return RedVSIIOElement(eKeywordName); };
    static RedVSIIOElement KeywordClass(void)                             { return RedVSIIOElement(eKeywordClass); };
    static RedVSIIOElement KeywordRoutine(void)                           { return RedVSIIOElement(eKeywordRoutine); };
    static RedVSIIOElement KeywordCode(void)                              { return RedVSIIOElement(eKeywordCode); };
    static RedVSIIOElement KeywordParams(void)                            { return RedVSIIOElement(eKeywordParams); };
    static RedVSIIOElement KeywordParent(void)                            { return RedVSIIOElement(eKeywordParent); };
    bool                   IsKeywordName(void) const                      { return eType == eKeywordName; };
    bool                   IsKeywordClass(void) const                     { return eType == eKeywordClass; };
    bool                   IsKeywordRoutine(void) const                   { return eType == eKeywordRoutine; };
    bool                   IsKeywordCode(void) const                      { return eType == eKeywordCode; };
    bool                   IsKeywordParams(void) const                    { return eType == eKeywordParams; };
    bool                   IsKeywordParent(void) const                    { return eType == eKeywordParent; };

    // Operators and separators
    bool                   IsOperatorSymbol(void) const;
    bool                   IsAssignOpSymbol(void) const;
    bool                   IsLogicOpSymbol(void) const;
    bool                   IsBinaryLogicOpSymbol(void) const;
    bool                   IsCompareOpSymbol(void) const;
    bool                   IsBinaryOpSymbol(void) const;
    bool                   IsSeparatorSymbol(void) const;

    bool                   IsSymbolAssignDivide(void) const               { return eType == eSymbolAssignDivide; };
    bool                   IsSymbolAssignEqual(void) const                { return eType == eSymbolAssignEqual; };
    bool                   IsSymbolAssignMinus(void) const                { return eType == eSymbolAssignMinus; };
    bool                   IsSymbolAssignMultiply(void) const             { return eType == eSymbolAssignMultiply; };
    bool                   IsSymbolAssignPlus(void) const                 { return eType == eSymbolAssignPlus; };

    bool                   IsSymbolBracketOpen(void) const                { return eType == eSymbolBracketOpen; };
    bool                   IsSymbolBracketClose(void) const               { return eType == eSymbolBracketClose; };
    bool                   IsSymbolBracketOpenCurly(void) const           { return eType == eSymbolBracketOpenCurly; };
    bool                   IsSymbolBracketCloseCurly(void) const          { return eType == eSymbolBracketCloseCurly; };
    bool                   IsSymbolBracketOpenSquare(void) const          { return eType == eSymbolBracketOpenSquare; };
    bool                   IsSymbolBracketCloseSquare(void) const         { return eType == eSymbolBracketCloseSquare; };

    bool                   IsSymbolCompareEqual(void) const               { return eType == eSymbolCompareEqual; };
    bool                   IsSymbolCompareNotEqual(void) const            { return eType == eSymbolCompareNotEqual; };
    bool                   IsSymbolCompareLessThan(void) const            { return eType == eSymbolCompareLessThan; };
    bool                   IsSymbolCompareGreaterThan(void) const         { return eType == eSymbolCompareGreaterThan; };
    bool                   IsSymbolCompareLessThanOrEqual(void) const     { return eType == eSymbolCompareLessThan; };
    bool                   IsSymbolCompareGreaterThanOrEqual (void) const { return eType == eSymbolCompareGreaterThan; };
    
    bool                   IsSymbolLogicAnd(void) const                   { return eType == eSymbolLogicAnd; };
    bool                   IsSymbolLogicOr(void) const                    { return eType == eSymbolLogicOr; };
    bool                   IsSymbolLogicNot(void) const                   { return eType == eSymbolLogicNot; };

    bool                   IsSymbolOperatorDivide(void) const             { return eType == eSymbolOperatorDivide; };
    bool                   IsSymbolOperatorMinus(void) const              { return eType == eSymbolOperatorMinus; };
    bool                   IsSymbolOperatorMultiply(void) const           { return eType == eSymbolOperatorMultiply; };
    bool                   IsSymbolOperatorPlus(void) const               { return eType == eSymbolOperatorPlus; };
    bool                   IsSymbolOperatorPower(void) const              { return eType == eSymbolOperatorPower; };
    
    bool                   IsSymbolComma(void) const                      { return eType == eSymbolComma; };
    bool                   IsSymbolPeriod(void) const                     { return eType == eSymbolPeriod; };
    bool                   IsSymbolDoubleColon(void) const                { return eType == eSymbolDoubleColon; };
    bool                   IsSymbolStringContent(void) const              { return eType == eSymbolStringContent; };
    bool                   IsSymbolEOF(void) const                        { return eType == eSymbolEOF; };

    static RedVSIIOElement SymbolAssignDivide(void)                       { return RedVSIIOElement(eSymbolAssignDivide); };
    static RedVSIIOElement SymbolAssignEqual(void)                        { return RedVSIIOElement(eSymbolAssignEqual); };
    static RedVSIIOElement SymbolAssignMinus(void)                        { return RedVSIIOElement(eSymbolAssignMinus); };
    static RedVSIIOElement SymbolAssignMultiply(void)                     { return RedVSIIOElement(eSymbolAssignMultiply); };
    static RedVSIIOElement SymbolAssignPlus(void)                         { return RedVSIIOElement(eSymbolAssignPlus); };

    static RedVSIIOElement SymbolBracketOpen(void)                        { return RedVSIIOElement(eSymbolBracketOpen); };
    static RedVSIIOElement SymbolBracketClose(void)                       { return RedVSIIOElement(eSymbolBracketClose); };
    static RedVSIIOElement SymbolBracketOpenCurly(void)                   { return RedVSIIOElement(eSymbolBracketOpenCurly); };
    static RedVSIIOElement SymbolBracketCloseCurly(void)                  { return RedVSIIOElement(eSymbolBracketCloseCurly); };
    static RedVSIIOElement SymbolBracketOpenSquare(void)                  { return RedVSIIOElement(eSymbolBracketOpenSquare); };
    static RedVSIIOElement SymbolBracketCloseSquare(void)                 { return RedVSIIOElement(eSymbolBracketCloseSquare); };

    static RedVSIIOElement SymbolCompareEqual(void)                       { return RedVSIIOElement(eSymbolCompareEqual); };
    static RedVSIIOElement SymbolCompareNotEqual(void)                    { return RedVSIIOElement(eSymbolCompareNotEqual); };
    static RedVSIIOElement SymbolCompareLessThan(void)                    { return RedVSIIOElement(eSymbolCompareLessThan); };
    static RedVSIIOElement SymbolCompareGreaterThan(void)                 { return RedVSIIOElement(eSymbolCompareGreaterThan); };
    static RedVSIIOElement SymbolCompareLessThanOrEqual(void)             { return RedVSIIOElement(eSymbolCompareLessThanOrEqual); };
    static RedVSIIOElement SymbolCompareGreaterThanOrEqual(void)          { return RedVSIIOElement(eSymbolCompareGreaterThanOrEqual); };

    static RedVSIIOElement SymbolLogicAnd(void)                           { return RedVSIIOElement(eSymbolLogicAnd); };
    static RedVSIIOElement SymbolLogicOr(void)                            { return RedVSIIOElement(eSymbolLogicOr); };
    static RedVSIIOElement SymbolLogicNot(void)                           { return RedVSIIOElement(eSymbolLogicNot); };

    static RedVSIIOElement SymbolOperatorPlus(void)                       { return RedVSIIOElement(eSymbolOperatorPlus); };
    static RedVSIIOElement SymbolOperatorMinus(void)                      { return RedVSIIOElement(eSymbolOperatorMinus); };
    static RedVSIIOElement SymbolOperatorMultiply(void)                   { return RedVSIIOElement(eSymbolOperatorMultiply); };
    static RedVSIIOElement SymbolOperatorDivide(void)                     { return RedVSIIOElement(eSymbolOperatorDivide); };
    static RedVSIIOElement SymbolOperatorPower(void)                      { return RedVSIIOElement(eSymbolOperatorPower); };
 
    static RedVSIIOElement SymbolComma(void)                              { return RedVSIIOElement(eSymbolComma); };
    static RedVSIIOElement SymbolPeriod(void)                             { return RedVSIIOElement(eSymbolPeriod); };
    static RedVSIIOElement SymbolDoubleColon(void)                        { return RedVSIIOElement(eSymbolDoubleColon); };
    static RedVSIIOElement SymbolStringContent(void)                      { return RedVSIIOElement(eSymbolStringContent); };

    static RedVSIIOElement SymbolEOF(void)                                { return RedVSIIOElement(eSymbolEOF); };

    // Operators
    void operator =(const RedVSIIOElement cNewVal)                        { eType=cNewVal.eType; };

    int iElem(void) const { return (int)eType; };

private:

    typedef enum TELangElem
    {
        eDefaultInvalid = 0,

        // Locations
        eKeywordAttribute,
        eKeywordStack,
        eKeywordHeap,

        // Types
        eKeywordBool,
        eKeywordChar,
        eKeywordList,
        eKeywordNumber,
        eKeywordRecord,
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
        eKeywordLog,
        eKeywordReturn,

        // Bool Values
        eKeywordBoolValueTrue,
        eKeywordBoolValueFalse,

        // Operators and separators
        eSymbolAssignDivide,
        eSymbolAssignEqual,
        eSymbolAssignMinus,
        eSymbolAssignMultiply,
        eSymbolAssignPlus,

        eSymbolBracketOpen,
        eSymbolBracketClose,
        eSymbolBracketOpenCurly,
        eSymbolBracketCloseCurly,
        eSymbolBracketOpenSquare,
        eSymbolBracketCloseSquare,

        eSymbolCompareEqual,
        eSymbolCompareNotEqual,
        eSymbolCompareLessThan,
        eSymbolCompareGreaterThan,
        eSymbolCompareLessThanOrEqual,
        eSymbolCompareGreaterThanOrEqual,
        
        eSymbolLogicAnd,
        eSymbolLogicOr,
        eSymbolLogicNot,
        
        eSymbolOperatorDivide,
        eSymbolOperatorMinus,
        eSymbolOperatorMultiply,
        eSymbolOperatorPlus,
        eSymbolOperatorPower,

        eSymbolComma,
        eSymbolPeriod,
        eSymbolDoubleColon,
        eSymbolStringContent,

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

