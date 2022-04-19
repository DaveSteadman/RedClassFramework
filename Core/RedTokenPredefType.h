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

    bool                      IsInvalid(void) const { return eType == TEPredef::eDefaultInvalid; };
    bool                      IsValid(void) const   { return eType != TEPredef::eDefaultInvalid; };

    // Check for keyowrd within a set
    bool                      IsLocationKeyword(void) const;
    bool                      IsTypeKeyword(void) const;
    bool                      IsCommandKeyword(void) const;
    bool                      IsBoolKeyword(void) const;
    bool                      IsLibraryKeyword(void) const;
    bool                      IsShellAreaKeyword(void) const;
    bool                      IsShellActionKeyword(void) const;

    // Keywords Check
    bool                      IsKeywordAdd(void)  const                      { return eType == TEPredef::eKeywordAdd; };
    bool                      IsKeywordAttribute(void) const                 { return eType == TEPredef::eKeywordAttribute; };
    bool                      IsKeywordBool(void) const                      { return eType == TEPredef::eKeywordBool; };
    bool                      IsKeywordChar(void) const                      { return eType == TEPredef::eKeywordChar; };
    bool                      IsKeywordClass(void) const                     { return eType == TEPredef::eKeywordClass; };
    bool                      IsKeywordCode(void) const                      { return eType == TEPredef::eKeywordCode; };
    bool                      IsKeywordData(void) const                      { return eType == TEPredef::eKeywordData; };
    bool                      IsKeywordElse(void) const                      { return eType == TEPredef::eKeywordElse; };
    bool                      IsKeywordEndif(void) const                     { return eType == TEPredef::eKeywordEndif; };
    bool                      IsKeywordEndloop(void) const                   { return eType == TEPredef::eKeywordEndloop; };
    bool                      IsKeywordExit(void) const                      { return eType == TEPredef::eKeywordExit; };
    bool                      IsKeywordFalse(void) const                     { return eType == TEPredef::eKeywordBoolValueFalse; };
    bool                      IsKeywordHeap(void) const                      { return eType == TEPredef::eKeywordHeap; };
    bool                      IsKeywordHelp(void) const                      { return eType == TEPredef::eKeywordHelp; };
    bool                      IsKeywordIf(void) const                        { return eType == TEPredef::eKeywordIf; };
    bool                      IsKeywordInit(void) const                      { return eType == TEPredef::eKeywordInit; };
    bool                      IsKeywordLet(void) const                       { return eType == TEPredef::eKeywordLet; };
    bool                      IsKeywordLib(void)  const                      { return eType == TEPredef::eKeywordLib; };
    bool                      IsKeywordList(void) const                      { return eType == TEPredef::eKeywordList; };
    bool                      IsKeywordLog(void) const                       { return eType == TEPredef::eKeywordLog; };
    bool                      IsKeywordLoop(void) const                      { return eType == TEPredef::eKeywordLoop; };
    bool                      IsKeywordName(void) const                      { return eType == TEPredef::eKeywordName; };
    bool                      IsKeywordNew(void) const                       { return eType == TEPredef::eKeywordNew; };
    bool                      IsKeywordNumber(void) const                    { return eType == TEPredef::eKeywordNumber; };
    bool                      IsKeywordParams(void) const                    { return eType == TEPredef::eKeywordParams; };
    bool                      IsKeywordParent(void) const                    { return eType == TEPredef::eKeywordParent; };
    bool                      IsKeywordRecord(void) const                    { return eType == TEPredef::eKeywordRecord; };
    bool                      IsKeywordReturn(void) const                    { return eType == TEPredef::eKeywordReturn; };
    bool                      IsKeywordRoutine(void) const                   { return eType == TEPredef::eKeywordRoutine; };
    bool                      IsKeywordRun(void)  const                      { return eType == TEPredef::eKeywordRun; };
    bool                      IsKeywordStack(void) const                     { return eType == TEPredef::eKeywordStack; };
    bool                      IsKeywordString(void) const                    { return eType == TEPredef::eKeywordString; };
    bool                      IsKeywordThen(void) const                      { return eType == TEPredef::eKeywordThen; };
    bool                      IsKeywordTrue(void) const                      { return eType == TEPredef::eKeywordBoolValueTrue; };
    bool                      IsKeywordVariant(void) const                   { return eType == TEPredef::eKeywordVariant; };
    bool                      IsKeywordWhile(void) const                     { return eType == TEPredef::eKeywordWhile; };

    // Keywords Setup
    static RedTokenPredefType DefaultInvalid(void)                           { return RedTokenPredefType(TEPredef::eDefaultInvalid); };

    static RedTokenPredefType KeywordAdd(void)                               { return RedTokenPredefType(TEPredef::eKeywordAdd); }
    static RedTokenPredefType KeywordAttribute(void)                         { return RedTokenPredefType(TEPredef::eKeywordAttribute); };
    static RedTokenPredefType KeywordBool(void)                              { return RedTokenPredefType(TEPredef::eKeywordBool); };
    static RedTokenPredefType KeywordChar(void)                              { return RedTokenPredefType(TEPredef::eKeywordChar); };
    static RedTokenPredefType KeywordClass(void)                             { return RedTokenPredefType(TEPredef::eKeywordClass); };
    static RedTokenPredefType KeywordCode(void)                              { return RedTokenPredefType(TEPredef::eKeywordCode); };
    static RedTokenPredefType KeywordData(void)                              { return RedTokenPredefType(TEPredef::eKeywordData); }
    static RedTokenPredefType KeywordElse(void)                              { return RedTokenPredefType(TEPredef::eKeywordElse); };
    static RedTokenPredefType KeywordEndif(void)                             { return RedTokenPredefType(TEPredef::eKeywordEndif); };
    static RedTokenPredefType KeywordEndloop(void)                           { return RedTokenPredefType(TEPredef::eKeywordEndloop); };
    static RedTokenPredefType KeywordExit(void)                              { return RedTokenPredefType(TEPredef::eKeywordExit); }
    static RedTokenPredefType KeywordFalse(void)                             { return RedTokenPredefType(TEPredef::eKeywordBoolValueFalse); };
    static RedTokenPredefType KeywordStack(void)                             { return RedTokenPredefType(TEPredef::eKeywordStack); };
    static RedTokenPredefType KeywordHeap(void)                              { return RedTokenPredefType(TEPredef::eKeywordHeap); };
    static RedTokenPredefType KeywordHelp(void)                              { return RedTokenPredefType(TEPredef::eKeywordHelp); };
    static RedTokenPredefType KeywordInit(void)                              { return RedTokenPredefType(TEPredef::eKeywordInit); }
    static RedTokenPredefType KeywordIf(void)                                { return RedTokenPredefType(TEPredef::eKeywordIf); };
    static RedTokenPredefType KeywordLet(void)                               { return RedTokenPredefType(TEPredef::eKeywordLet); };
    static RedTokenPredefType KeywordLib(void)                               { return RedTokenPredefType(TEPredef::eKeywordLib); }
    static RedTokenPredefType KeywordList(void)                              { return RedTokenPredefType(TEPredef::eKeywordList); };
    static RedTokenPredefType KeywordLog(void)                               { return RedTokenPredefType(TEPredef::eKeywordLog); };
    static RedTokenPredefType KeywordLoop(void)                              { return RedTokenPredefType(TEPredef::eKeywordLoop); };
    static RedTokenPredefType KeywordName(void)                              { return RedTokenPredefType(TEPredef::eKeywordName); };
    static RedTokenPredefType KeywordNew(void)                               { return RedTokenPredefType(TEPredef::eKeywordNew); };
    static RedTokenPredefType KeywordNumber(void)                            { return RedTokenPredefType(TEPredef::eKeywordNumber); };
    static RedTokenPredefType KeywordParams(void)                            { return RedTokenPredefType(TEPredef::eKeywordParams); };
    static RedTokenPredefType KeywordParent(void)                            { return RedTokenPredefType(TEPredef::eKeywordParent); };
    static RedTokenPredefType KeywordRecord(void)                            { return RedTokenPredefType(TEPredef::eKeywordRecord); };
    static RedTokenPredefType KeywordReturn(void)                            { return RedTokenPredefType(TEPredef::eKeywordReturn); };
    static RedTokenPredefType KeywordRoutine(void)                           { return RedTokenPredefType(TEPredef::eKeywordRoutine); };
    static RedTokenPredefType KeywordRun(void)                               { return RedTokenPredefType(TEPredef::eKeywordRun); }
    static RedTokenPredefType KeywordString(void)                            { return RedTokenPredefType(TEPredef::eKeywordString); };
    static RedTokenPredefType KeywordThen(void)                              { return RedTokenPredefType(TEPredef::eKeywordThen); };
    static RedTokenPredefType KeywordTrue(void)                              { return RedTokenPredefType(TEPredef::eKeywordBoolValueTrue); };
    static RedTokenPredefType KeywordVariant(void)                           { return RedTokenPredefType(TEPredef::eKeywordVariant); };
    static RedTokenPredefType KeywordWhile(void)                             { return RedTokenPredefType(TEPredef::eKeywordWhile); };

    // Operators and separators
    bool                      IsOperatorSymbol(void) const;
    bool                      IsAssignOpSymbol(void) const;
    bool                      IsLogicOpSymbol(void) const;
    bool                      IsBinaryLogicOpSymbol(void) const;
    bool                      IsCompareOpSymbol(void) const;
    bool                      IsBinaryOpSymbol(void) const;
    bool                      IsSeparatorSymbol(void) const;

    bool                      IsSymbolAssignDivide(void) const               { return eType == TEPredef::eSymbolAssignDivide; };
    bool                      IsSymbolAssignEqual(void) const                { return eType == TEPredef::eSymbolAssignEqual; };
    bool                      IsSymbolAssignMinus(void) const                { return eType == TEPredef::eSymbolAssignMinus; };
    bool                      IsSymbolAssignMultiply(void) const             { return eType == TEPredef::eSymbolAssignMultiply; };
    bool                      IsSymbolAssignPlus(void) const                 { return eType == TEPredef::eSymbolAssignPlus; };

    bool                      IsSymbolBracketOpen(void) const                { return eType == TEPredef::eSymbolBracketOpen; };
    bool                      IsSymbolBracketClose(void) const               { return eType == TEPredef::eSymbolBracketClose; };
    bool                      IsSymbolBracketOpenCurly(void) const           { return eType == TEPredef::eSymbolBracketOpenCurly; };
    bool                      IsSymbolBracketCloseCurly(void) const          { return eType == TEPredef::eSymbolBracketCloseCurly; };
    bool                      IsSymbolBracketOpenSquare(void) const          { return eType == TEPredef::eSymbolBracketOpenSquare; };
    bool                      IsSymbolBracketCloseSquare(void) const         { return eType == TEPredef::eSymbolBracketCloseSquare; };

    bool                      IsSymbolCompareEqual(void) const               { return eType == TEPredef::eSymbolCompareEqual; };
    bool                      IsSymbolCompareNotEqual(void) const            { return eType == TEPredef::eSymbolCompareNotEqual; };
    bool                      IsSymbolCompareLessThan(void) const            { return eType == TEPredef::eSymbolCompareLessThan; };
    bool                      IsSymbolCompareGreaterThan(void) const         { return eType == TEPredef::eSymbolCompareGreaterThan; };
    bool                      IsSymbolCompareLessThanOrEqual(void) const     { return eType == TEPredef::eSymbolCompareLessThan; };
    bool                      IsSymbolCompareGreaterThanOrEqual (void) const { return eType == TEPredef::eSymbolCompareGreaterThan; };
    
    bool                      IsSymbolLogicAnd(void) const                   { return eType == TEPredef::eSymbolLogicAnd; };
    bool                      IsSymbolLogicOr(void) const                    { return eType == TEPredef::eSymbolLogicOr; };
    bool                      IsSymbolLogicNot(void) const                   { return eType == TEPredef::eSymbolLogicNot; };

    bool                      IsSymbolOperatorDivide(void) const             { return eType == TEPredef::eSymbolOperatorDivide; };
    bool                      IsSymbolOperatorMinus(void) const              { return eType == TEPredef::eSymbolOperatorMinus; };
    bool                      IsSymbolOperatorMultiply(void) const           { return eType == TEPredef::eSymbolOperatorMultiply; };
    bool                      IsSymbolOperatorPlus(void) const               { return eType == TEPredef::eSymbolOperatorPlus; };
    bool                      IsSymbolOperatorPower(void) const              { return eType == TEPredef::eSymbolOperatorPower; };
    
    bool                      IsSymbolComma(void) const                      { return eType == TEPredef::eSymbolComma; };
    bool                      IsSymbolPeriod(void) const                     { return eType == TEPredef::eSymbolPeriod; };
    bool                      IsSymbolDoubleColon(void) const                { return eType == TEPredef::eSymbolDoubleColon; };
    bool                      IsSymbolStringContent(void) const              { return eType == TEPredef::eSymbolStringContent; };
    bool                      IsSymbolEOF(void) const                        { return eType == TEPredef::eSymbolEOF; };

    static RedTokenPredefType SymbolAssignDivide(void)                       { return RedTokenPredefType(TEPredef::eSymbolAssignDivide); };
    static RedTokenPredefType SymbolAssignEqual(void)                        { return RedTokenPredefType(TEPredef::eSymbolAssignEqual); };
    static RedTokenPredefType SymbolAssignMinus(void)                        { return RedTokenPredefType(TEPredef::eSymbolAssignMinus); };
    static RedTokenPredefType SymbolAssignMultiply(void)                     { return RedTokenPredefType(TEPredef::eSymbolAssignMultiply); };
    static RedTokenPredefType SymbolAssignPlus(void)                         { return RedTokenPredefType(TEPredef::eSymbolAssignPlus); };

    static RedTokenPredefType SymbolBracketOpen(void)                        { return RedTokenPredefType(TEPredef::eSymbolBracketOpen); };
    static RedTokenPredefType SymbolBracketClose(void)                       { return RedTokenPredefType(TEPredef::eSymbolBracketClose); };
    static RedTokenPredefType SymbolBracketOpenCurly(void)                   { return RedTokenPredefType(TEPredef::eSymbolBracketOpenCurly); };
    static RedTokenPredefType SymbolBracketCloseCurly(void)                  { return RedTokenPredefType(TEPredef::eSymbolBracketCloseCurly); };
    static RedTokenPredefType SymbolBracketOpenSquare(void)                  { return RedTokenPredefType(TEPredef::eSymbolBracketOpenSquare); };
    static RedTokenPredefType SymbolBracketCloseSquare(void)                 { return RedTokenPredefType(TEPredef::eSymbolBracketCloseSquare); };

    static RedTokenPredefType SymbolCompareEqual(void)                       { return RedTokenPredefType(TEPredef::eSymbolCompareEqual); };
    static RedTokenPredefType SymbolCompareNotEqual(void)                    { return RedTokenPredefType(TEPredef::eSymbolCompareNotEqual); };
    static RedTokenPredefType SymbolCompareLessThan(void)                    { return RedTokenPredefType(TEPredef::eSymbolCompareLessThan); };
    static RedTokenPredefType SymbolCompareGreaterThan(void)                 { return RedTokenPredefType(TEPredef::eSymbolCompareGreaterThan); };
    static RedTokenPredefType SymbolCompareLessThanOrEqual(void)             { return RedTokenPredefType(TEPredef::eSymbolCompareLessThanOrEqual); };
    static RedTokenPredefType SymbolCompareGreaterThanOrEqual(void)          { return RedTokenPredefType(TEPredef::eSymbolCompareGreaterThanOrEqual); };

    static RedTokenPredefType SymbolLogicAnd(void)                           { return RedTokenPredefType(TEPredef::eSymbolLogicAnd); };
    static RedTokenPredefType SymbolLogicOr(void)                            { return RedTokenPredefType(TEPredef::eSymbolLogicOr); };
    static RedTokenPredefType SymbolLogicNot(void)                           { return RedTokenPredefType(TEPredef::eSymbolLogicNot); };

    static RedTokenPredefType SymbolOperatorPlus(void)                       { return RedTokenPredefType(TEPredef::eSymbolOperatorPlus); };
    static RedTokenPredefType SymbolOperatorMinus(void)                      { return RedTokenPredefType(TEPredef::eSymbolOperatorMinus); };
    static RedTokenPredefType SymbolOperatorMultiply(void)                   { return RedTokenPredefType(TEPredef::eSymbolOperatorMultiply); };
    static RedTokenPredefType SymbolOperatorDivide(void)                     { return RedTokenPredefType(TEPredef::eSymbolOperatorDivide); };
    static RedTokenPredefType SymbolOperatorPower(void)                      { return RedTokenPredefType(TEPredef::eSymbolOperatorPower); };
 
    static RedTokenPredefType SymbolComma(void)                              { return RedTokenPredefType(TEPredef::eSymbolComma); };
    static RedTokenPredefType SymbolPeriod(void)                             { return RedTokenPredefType(TEPredef::eSymbolPeriod); };
    static RedTokenPredefType SymbolDoubleColon(void)                        { return RedTokenPredefType(TEPredef::eSymbolDoubleColon); };
    static RedTokenPredefType SymbolStringContent(void)                      { return RedTokenPredefType(TEPredef::eSymbolStringContent); };

    static RedTokenPredefType SymbolEOF(void)                                { return RedTokenPredefType(TEPredef::eSymbolEOF); };

    // Operators
    void operator =(const RedTokenPredefType cNewVal)                        { eType=cNewVal.eType; };

    int iElem(void) const { return (int)eType; };

private:

    enum class TEPredef
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
    };
    
    RedTokenPredefType(TEPredef eNewType) { eType = eNewType; };

    TEPredef eType = TEPredef::eDefaultInvalid;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs);
bool operator!=(const RedTokenPredefType& lhs, const RedTokenPredefType& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

