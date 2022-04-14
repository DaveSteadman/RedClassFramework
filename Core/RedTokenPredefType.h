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

#pragma once

namespace Red {
namespace Core {

// Definition of the Language IO Elements. This defines the tokens which are
// required to input a textual representations of the language.
// This type covers elements such as brackets and punctuation which are
// removed in the translation to the internal RedVSILangElement type.
class RedTokenPredefType
{
public:

    // Constructor
    RedTokenPredefType(void) { Init(); };
    void Init(void);

    bool                      IsInvalid(void) const { return eType == eDefaultInvalid; };
    bool                      IsValid(void) const   { return eType != eDefaultInvalid; };

    // Check for keyowrd within a set
    bool                      IsLocationKeyword(void) const;
    bool                      IsTypeKeyword(void) const;
    bool                      IsCommandKeyword(void) const;
    bool                      IsBoolKeyword(void) const;
    bool                      IsLibraryKeyword(void) const;
    bool                      IsShellAreaKeyword(void) const;
    bool                      IsShellActionKeyword(void) const;

    // Keywords Check
    bool                      IsKeywordAdd(void)  const                      { return eType == eKeywordAdd; };
    bool                      IsKeywordAttribute(void) const                 { return eType == eKeywordAttribute; };
    bool                      IsKeywordBool(void) const                      { return eType == eKeywordBool; };
    bool                      IsKeywordChar(void) const                      { return eType == eKeywordChar; };
    bool                      IsKeywordClass(void) const                     { return eType == eKeywordClass; };
    bool                      IsKeywordCode(void) const                      { return eType == eKeywordCode; };
    bool                      IsKeywordData(void) const                      { return eType == eKeywordData; };
    bool                      IsKeywordElse(void) const                      { return eType == eKeywordElse; };
    bool                      IsKeywordEndif(void) const                     { return eType == eKeywordEndif; };
    bool                      IsKeywordEndloop(void) const                   { return eType == eKeywordEndloop; };
    bool                      IsKeywordExit(void) const                      { return eType == eKeywordExit; };
    bool                      IsKeywordFalse(void) const                     { return eType == eKeywordBoolValueFalse; };
    bool                      IsKeywordHeap(void) const                      { return eType == eKeywordHeap; };
    bool                      IsKeywordHelp(void) const                      { return eType == eKeywordHelp; };
    bool                      IsKeywordIf(void) const                        { return eType == eKeywordIf; };
    bool                      IsKeywordInit(void) const                      { return eType == eKeywordInit; };
    bool                      IsKeywordLet(void) const                       { return eType == eKeywordLet; };
    bool                      IsKeywordLib(void)  const                      { return eType == eKeywordLib; };
    bool                      IsKeywordList(void) const                      { return eType == eKeywordList; };
    bool                      IsKeywordLog(void) const                       { return eType == eKeywordLog; };
    bool                      IsKeywordLoop(void) const                      { return eType == eKeywordLoop; };
    bool                      IsKeywordName(void) const                      { return eType == eKeywordName; };
    bool                      IsKeywordNew(void) const                       { return eType == eKeywordNew; };
    bool                      IsKeywordNumber(void) const                    { return eType == eKeywordNumber; };
    bool                      IsKeywordParams(void) const                    { return eType == eKeywordParams; };
    bool                      IsKeywordParent(void) const                    { return eType == eKeywordParent; };
    bool                      IsKeywordRecord(void) const                    { return eType == eKeywordRecord; };
    bool                      IsKeywordReturn(void) const                    { return eType == eKeywordReturn; };
    bool                      IsKeywordRoutine(void) const                   { return eType == eKeywordRoutine; };
    bool                      IsKeywordRun(void)  const                      { return eType == eKeywordRun; };
    bool                      IsKeywordStack(void) const                     { return eType == eKeywordStack; };
    bool                      IsKeywordString(void) const                    { return eType == eKeywordString; };
    bool                      IsKeywordThen(void) const                      { return eType == eKeywordThen; };
    bool                      IsKeywordTrue(void) const                      { return eType == eKeywordBoolValueTrue; };
    bool                      IsKeywordVariant(void) const                   { return eType == eKeywordVariant; };
    bool                      IsKeywordWhile(void) const                     { return eType == eKeywordWhile; };

    // Keywords Setup
    static RedTokenPredefType KeywordAdd(void)                               { return RedTokenPredefType(eKeywordAdd); }
    static RedTokenPredefType KeywordAttribute(void)                         { return RedTokenPredefType(eKeywordAttribute); };
    static RedTokenPredefType KeywordBool(void)                              { return RedTokenPredefType(eKeywordBool); };
    static RedTokenPredefType KeywordChar(void)                              { return RedTokenPredefType(eKeywordChar); };
    static RedTokenPredefType KeywordClass(void)                             { return RedTokenPredefType(eKeywordClass); };
    static RedTokenPredefType KeywordCode(void)                              { return RedTokenPredefType(eKeywordCode); };
    static RedTokenPredefType KeywordData(void)                              { return RedTokenPredefType(eKeywordData); }
    static RedTokenPredefType KeywordElse(void)                              { return RedTokenPredefType(eKeywordElse); };
    static RedTokenPredefType KeywordEndif(void)                             { return RedTokenPredefType(eKeywordEndif); };
    static RedTokenPredefType KeywordEndloop(void)                           { return RedTokenPredefType(eKeywordEndloop); };
    static RedTokenPredefType KeywordExit(void)                              { return RedTokenPredefType(eKeywordExit); }
    static RedTokenPredefType KeywordFalse(void)                             { return RedTokenPredefType(eKeywordBoolValueFalse); };
    static RedTokenPredefType KeywordStack(void)                             { return RedTokenPredefType(eKeywordStack); };
    static RedTokenPredefType KeywordHeap(void)                              { return RedTokenPredefType(eKeywordHeap); };
    static RedTokenPredefType KeywordHelp(void)                              { return RedTokenPredefType(eKeywordHelp); };
    static RedTokenPredefType KeywordInit(void)                              { return RedTokenPredefType(eKeywordInit); }
    static RedTokenPredefType KeywordIf(void)                                { return RedTokenPredefType(eKeywordIf); };
    static RedTokenPredefType KeywordLet(void)                               { return RedTokenPredefType(eKeywordLet); };
    static RedTokenPredefType KeywordLib(void)                               { return RedTokenPredefType(eKeywordLib); }
    static RedTokenPredefType KeywordList(void)                              { return RedTokenPredefType(eKeywordList); };
    static RedTokenPredefType KeywordLog(void)                               { return RedTokenPredefType(eKeywordLog); };
    static RedTokenPredefType KeywordLoop(void)                              { return RedTokenPredefType(eKeywordLoop); };
    static RedTokenPredefType KeywordName(void)                              { return RedTokenPredefType(eKeywordName); };
    static RedTokenPredefType KeywordNew(void)                               { return RedTokenPredefType(eKeywordNew); };
    static RedTokenPredefType KeywordNumber(void)                            { return RedTokenPredefType(eKeywordNumber); };
    static RedTokenPredefType KeywordParams(void)                            { return RedTokenPredefType(eKeywordParams); };
    static RedTokenPredefType KeywordParent(void)                            { return RedTokenPredefType(eKeywordParent); };
    static RedTokenPredefType KeywordRecord(void)                            { return RedTokenPredefType(eKeywordRecord); };
    static RedTokenPredefType KeywordReturn(void)                            { return RedTokenPredefType(eKeywordReturn); };
    static RedTokenPredefType KeywordRoutine(void)                           { return RedTokenPredefType(eKeywordRoutine); };
    static RedTokenPredefType KeywordRun(void)                               { return RedTokenPredefType(eKeywordRun); }
    static RedTokenPredefType KeywordString(void)                            { return RedTokenPredefType(eKeywordString); };
    static RedTokenPredefType KeywordThen(void)                              { return RedTokenPredefType(eKeywordThen); };
    static RedTokenPredefType KeywordTrue(void)                              { return RedTokenPredefType(eKeywordBoolValueTrue); };
    static RedTokenPredefType KeywordVariant(void)                           { return RedTokenPredefType(eKeywordVariant); };
    static RedTokenPredefType KeywordWhile(void)                             { return RedTokenPredefType(eKeywordWhile); };

    // Operators and separators
    bool                      IsOperatorSymbol(void) const;
    bool                      IsAssignOpSymbol(void) const;
    bool                      IsLogicOpSymbol(void) const;
    bool                      IsBinaryLogicOpSymbol(void) const;
    bool                      IsCompareOpSymbol(void) const;
    bool                      IsBinaryOpSymbol(void) const;
    bool                      IsSeparatorSymbol(void) const;

    bool                      IsSymbolAssignDivide(void) const               { return eType == eSymbolAssignDivide; };
    bool                      IsSymbolAssignEqual(void) const                { return eType == eSymbolAssignEqual; };
    bool                      IsSymbolAssignMinus(void) const                { return eType == eSymbolAssignMinus; };
    bool                      IsSymbolAssignMultiply(void) const             { return eType == eSymbolAssignMultiply; };
    bool                      IsSymbolAssignPlus(void) const                 { return eType == eSymbolAssignPlus; };

    bool                      IsSymbolBracketOpen(void) const                { return eType == eSymbolBracketOpen; };
    bool                      IsSymbolBracketClose(void) const               { return eType == eSymbolBracketClose; };
    bool                      IsSymbolBracketOpenCurly(void) const           { return eType == eSymbolBracketOpenCurly; };
    bool                      IsSymbolBracketCloseCurly(void) const          { return eType == eSymbolBracketCloseCurly; };
    bool                      IsSymbolBracketOpenSquare(void) const          { return eType == eSymbolBracketOpenSquare; };
    bool                      IsSymbolBracketCloseSquare(void) const         { return eType == eSymbolBracketCloseSquare; };

    bool                      IsSymbolCompareEqual(void) const               { return eType == eSymbolCompareEqual; };
    bool                      IsSymbolCompareNotEqual(void) const            { return eType == eSymbolCompareNotEqual; };
    bool                      IsSymbolCompareLessThan(void) const            { return eType == eSymbolCompareLessThan; };
    bool                      IsSymbolCompareGreaterThan(void) const         { return eType == eSymbolCompareGreaterThan; };
    bool                      IsSymbolCompareLessThanOrEqual(void) const     { return eType == eSymbolCompareLessThan; };
    bool                      IsSymbolCompareGreaterThanOrEqual (void) const { return eType == eSymbolCompareGreaterThan; };
    
    bool                      IsSymbolLogicAnd(void) const                   { return eType == eSymbolLogicAnd; };
    bool                      IsSymbolLogicOr(void) const                    { return eType == eSymbolLogicOr; };
    bool                      IsSymbolLogicNot(void) const                   { return eType == eSymbolLogicNot; };

    bool                      IsSymbolOperatorDivide(void) const             { return eType == eSymbolOperatorDivide; };
    bool                      IsSymbolOperatorMinus(void) const              { return eType == eSymbolOperatorMinus; };
    bool                      IsSymbolOperatorMultiply(void) const           { return eType == eSymbolOperatorMultiply; };
    bool                      IsSymbolOperatorPlus(void) const               { return eType == eSymbolOperatorPlus; };
    bool                      IsSymbolOperatorPower(void) const              { return eType == eSymbolOperatorPower; };
    
    bool                      IsSymbolComma(void) const                      { return eType == eSymbolComma; };
    bool                      IsSymbolPeriod(void) const                     { return eType == eSymbolPeriod; };
    bool                      IsSymbolDoubleColon(void) const                { return eType == eSymbolDoubleColon; };
    bool                      IsSymbolStringContent(void) const              { return eType == eSymbolStringContent; };
    bool                      IsSymbolEOF(void) const                        { return eType == eSymbolEOF; };

    static RedTokenPredefType SymbolAssignDivide(void)                       { return RedTokenPredefType(eSymbolAssignDivide); };
    static RedTokenPredefType SymbolAssignEqual(void)                        { return RedTokenPredefType(eSymbolAssignEqual); };
    static RedTokenPredefType SymbolAssignMinus(void)                        { return RedTokenPredefType(eSymbolAssignMinus); };
    static RedTokenPredefType SymbolAssignMultiply(void)                     { return RedTokenPredefType(eSymbolAssignMultiply); };
    static RedTokenPredefType SymbolAssignPlus(void)                         { return RedTokenPredefType(eSymbolAssignPlus); };

    static RedTokenPredefType SymbolBracketOpen(void)                        { return RedTokenPredefType(eSymbolBracketOpen); };
    static RedTokenPredefType SymbolBracketClose(void)                       { return RedTokenPredefType(eSymbolBracketClose); };
    static RedTokenPredefType SymbolBracketOpenCurly(void)                   { return RedTokenPredefType(eSymbolBracketOpenCurly); };
    static RedTokenPredefType SymbolBracketCloseCurly(void)                  { return RedTokenPredefType(eSymbolBracketCloseCurly); };
    static RedTokenPredefType SymbolBracketOpenSquare(void)                  { return RedTokenPredefType(eSymbolBracketOpenSquare); };
    static RedTokenPredefType SymbolBracketCloseSquare(void)                 { return RedTokenPredefType(eSymbolBracketCloseSquare); };

    static RedTokenPredefType SymbolCompareEqual(void)                       { return RedTokenPredefType(eSymbolCompareEqual); };
    static RedTokenPredefType SymbolCompareNotEqual(void)                    { return RedTokenPredefType(eSymbolCompareNotEqual); };
    static RedTokenPredefType SymbolCompareLessThan(void)                    { return RedTokenPredefType(eSymbolCompareLessThan); };
    static RedTokenPredefType SymbolCompareGreaterThan(void)                 { return RedTokenPredefType(eSymbolCompareGreaterThan); };
    static RedTokenPredefType SymbolCompareLessThanOrEqual(void)             { return RedTokenPredefType(eSymbolCompareLessThanOrEqual); };
    static RedTokenPredefType SymbolCompareGreaterThanOrEqual(void)          { return RedTokenPredefType(eSymbolCompareGreaterThanOrEqual); };

    static RedTokenPredefType SymbolLogicAnd(void)                           { return RedTokenPredefType(eSymbolLogicAnd); };
    static RedTokenPredefType SymbolLogicOr(void)                            { return RedTokenPredefType(eSymbolLogicOr); };
    static RedTokenPredefType SymbolLogicNot(void)                           { return RedTokenPredefType(eSymbolLogicNot); };

    static RedTokenPredefType SymbolOperatorPlus(void)                       { return RedTokenPredefType(eSymbolOperatorPlus); };
    static RedTokenPredefType SymbolOperatorMinus(void)                      { return RedTokenPredefType(eSymbolOperatorMinus); };
    static RedTokenPredefType SymbolOperatorMultiply(void)                   { return RedTokenPredefType(eSymbolOperatorMultiply); };
    static RedTokenPredefType SymbolOperatorDivide(void)                     { return RedTokenPredefType(eSymbolOperatorDivide); };
    static RedTokenPredefType SymbolOperatorPower(void)                      { return RedTokenPredefType(eSymbolOperatorPower); };
 
    static RedTokenPredefType SymbolComma(void)                              { return RedTokenPredefType(eSymbolComma); };
    static RedTokenPredefType SymbolPeriod(void)                             { return RedTokenPredefType(eSymbolPeriod); };
    static RedTokenPredefType SymbolDoubleColon(void)                        { return RedTokenPredefType(eSymbolDoubleColon); };
    static RedTokenPredefType SymbolStringContent(void)                      { return RedTokenPredefType(eSymbolStringContent); };

    static RedTokenPredefType SymbolEOF(void)                                { return RedTokenPredefType(eSymbolEOF); };

    // Operators
    void operator =(const RedTokenPredefType cNewVal)                        { eType=cNewVal.eType; };

    int iElem(void) const { return (int)eType; };

private:

    typedef enum TELangElem
    {
        eDefaultInvalid = 0,

        eKeywordAdd,
        eKeywordAttribute,
        eKeywordBool,
        eKeywordChar,
        eKeywordClass,
        eKeywordCode,
        eKeywordData,
        eKeywordElse,
        eKeywordEndif,
        eKeywordEndloop,
        eKeywordExit,
        eKeywordHeap,
        eKeywordHelp,
        eKeywordIf,
        eKeywordInit,
        eKeywordLet,
        eKeywordLib,
        eKeywordList,
        eKeywordLog,
        eKeywordLoop,
        eKeywordName,
        eKeywordNew,
        eKeywordNumber,
        eKeywordParams,
        eKeywordParent,
        eKeywordRecord,
        eKeywordReturn,
        eKeywordRoutine,
        eKeywordRun,
        eKeywordStack,
        eKeywordString,
        eKeywordThen,
        eKeywordVariant,
        eKeywordWhile,

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
        eSymbolBracketOpenCurly,
        eSymbolBracketOpenSquare,
        eSymbolBracketClose,
        eSymbolBracketCloseCurly,
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
    
    RedTokenPredefType(TELangElem eNewType) { eType = eNewType; };

    TELangElem eType;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs);
bool operator!=(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

