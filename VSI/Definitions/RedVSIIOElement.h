
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
    const int              IsLocationKeyword(void) const;
    const int              IsKeywordAttribute(void) const                 { return eType == eKeywordAttribute; };
    const int              IsKeywordStack(void) const                     { return eType == eKeywordStack; };
    const int              IsKeywordHeap(void) const                      { return eType == eKeywordHeap; };
    static RedVSIIOElement KeywordAttribute(void)                         { return RedVSIIOElement(eKeywordAttribute); };
    static RedVSIIOElement KeywordStack(void)                             { return RedVSIIOElement(eKeywordStack); };
    static RedVSIIOElement KeywordHeap(void)                              { return RedVSIIOElement(eKeywordHeap); };

    // Types
    const int              IsTypeKeyword(void) const;
    const int              IsKeywordArray(void) const                     { return eType == eKeywordArray; };
    const int              IsKeywordBool(void) const                      { return eType == eKeywordBool; };
    const int              IsKeywordChar(void) const                      { return eType == eKeywordChar; };
    const int              IsKeywordNumber(void) const                    { return eType == eKeywordNumber; };
    const int              IsKeywordString(void) const                    { return eType == eKeywordString; };
    static RedVSIIOElement KeywordArray(void)                             { return RedVSIIOElement(eKeywordArray); };
    static RedVSIIOElement KeywordBool(void)                              { return RedVSIIOElement(eKeywordBool); };
    static RedVSIIOElement KeywordChar(void)                              { return RedVSIIOElement(eKeywordChar); };
    static RedVSIIOElement KeywordNumber(void)                            { return RedVSIIOElement(eKeywordNumber); };
    static RedVSIIOElement KeywordString(void)                            { return RedVSIIOElement(eKeywordString); };

    // Commands
    const int              IsCommandKeyword(void) const;
    const int              IsKeywordNew(void) const                       { return eType == eKeywordNew; };
    const int              IsKeywordLet(void) const                       { return eType == eKeywordLet; };
    const int              IsKeywordIf(void) const                        { return eType == eKeywordIf; };
    const int              IsKeywordThen(void) const                      { return eType == eKeywordThen; };
    const int              IsKeywordElse(void) const                      { return eType == eKeywordElse; };
    const int              IsKeywordEndif(void) const                     { return eType == eKeywordEndif; };
    const int              IsKeywordWhile(void) const                     { return eType == eKeywordWhile; };
    const int              IsKeywordLoop(void) const                      { return eType == eKeywordLoop; };
    const int              IsKeywordEndloop(void) const                   { return eType == eKeywordEndloop; };
    const int              IsKeywordReturn(void) const                    { return eType == eKeywordReturn; };
    static RedVSIIOElement KeywordNew(void)                               { return RedVSIIOElement(eKeywordNew); };
    static RedVSIIOElement KeywordLet(void)                               { return RedVSIIOElement(eKeywordLet); };
    static RedVSIIOElement KeywordIf(void)                                { return RedVSIIOElement(eKeywordIf); };
    static RedVSIIOElement KeywordThen(void)                              { return RedVSIIOElement(eKeywordThen); };
    static RedVSIIOElement KeywordElse(void)                              { return RedVSIIOElement(eKeywordElse); };
    static RedVSIIOElement KeywordEndif(void)                             { return RedVSIIOElement(eKeywordEndif); };
    static RedVSIIOElement KeywordWhile(void)                             { return RedVSIIOElement(eKeywordWhile); };
    static RedVSIIOElement KeywordLoop(void)                              { return RedVSIIOElement(eKeywordLoop); };
    static RedVSIIOElement KeywordEndloop(void)                           { return RedVSIIOElement(eKeywordEndloop); };
    static RedVSIIOElement KeywordReturn(void)                            { return RedVSIIOElement(eKeywordReturn); };

    // Library
    const int              IsLibraryKeyword(void) const;
    static RedVSIIOElement KeywordName(void)                              { return RedVSIIOElement(eKeywordName); };
    static RedVSIIOElement KeywordClass(void)                             { return RedVSIIOElement(eKeywordClass); };
    static RedVSIIOElement KeywordRoutine(void)                           { return RedVSIIOElement(eKeywordRoutine); };
    static RedVSIIOElement KeywordCode(void)                              { return RedVSIIOElement(eKeywordCode); };
    static RedVSIIOElement KeywordParams(void)                            { return RedVSIIOElement(eKeywordParams); };
    static RedVSIIOElement KeywordParent(void)                            { return RedVSIIOElement(eKeywordParent); };
    const int              IsKeywordName(void) const                      { return eType == eKeywordName; };
    const int              IsKeywordClass(void) const                     { return eType == eKeywordClass; };
    const int              IsKeywordRoutine(void) const                   { return eType == eKeywordRoutine; };
    const int              IsKeywordCode(void) const                      { return eType == eKeywordCode; };
    const int              IsKeywordParams(void) const                    { return eType == eKeywordParams; };
    const int              IsKeywordParent(void) const                    { return eType == eKeywordParent; };

    // Operators and separators
    const int              IsOperatorSymbol(void) const;
    const int              IsAssignOpSymbol(void) const;
    const int              IsLogicOpSymbol(void) const;
    const int              IsBinaryLogicOpSymbol(void) const;
    const int              IsCompareOpSymbol(void) const;
    const int              IsBinaryOpSymbol(void) const;
    const int              IsSeparatorSymbol(void) const;

    const int              IsSymbolAssignDivide(void) const               { return eType == eSymbolAssignDivide; };
    const int              IsSymbolAssignEqual(void) const                { return eType == eSymbolAssignEqual; };
    const int              IsSymbolAssignMinus(void) const                { return eType == eSymbolAssignMinus; };
    const int              IsSymbolAssignMultiply(void) const             { return eType == eSymbolAssignMultiply; };
    const int              IsSymbolAssignPlus(void) const                 { return eType == eSymbolAssignPlus; };
    const int              IsSymbolCompareEqual(void) const               { return eType == eSymbolCompareEqual; };
    const int              IsSymbolCompareNotEqual(void) const            { return eType == eSymbolCompareNotEqual; };
    const int              IsSymbolCompareLessThan(void) const            { return eType == eSymbolCompareLessThan; };
    const int              IsSymbolCompareGreaterThan(void) const         { return eType == eSymbolCompareGreaterThan; };
    const int              IsSymbolCompareLessThanOrEqual(void) const     { return eType == eSymbolCompareLessThan; };
    const int              IsSymbolCompareGreaterThanOrEqual (void) const { return eType == eSymbolCompareGreaterThan; };
    const int              IsSymbolLogicAnd(void) const                   { return eType == eSymbolLogicAnd; };
    const int              IsSymbolLogicOr(void) const                    { return eType == eSymbolLogicOr; };
    const int              IsSymbolLogicNot(void) const                   { return eType == eSymbolLogicNot; };
    const int              IsSymbolDivide(void) const                     { return eType == eSymbolDivide; };
    const int              IsSymbolMinus(void) const                      { return eType == eSymbolMinus; };
    const int              IsSymbolMultiply(void) const                   { return eType == eSymbolMultiply; };
    const int              IsSymbolPlus(void) const                       { return eType == eSymbolPlus; };
    const int              IsSymbolPower(void) const                      { return eType == eSymbolPower; };
    const int              IsSymbolStringContent(void) const              { return eType == eSymbolStringContent; };
    const int              IsSymbolOpenBracket(void) const                { return eType == eSymbolOpenBracket; };
    const int              IsSymbolCloseBracket(void) const               { return eType == eSymbolCloseBracket; };
    const int              IsSymbolComma(void) const                      { return eType == eSymbolComma; };
    const int              IsSymbolPeriod(void) const                     { return eType == eSymbolPeriod; };
    const int              IsSymbolDoubleColon(void) const                { return eType == eSymbolDoubleColon; };
    const int              IsSymbolEOF(void) const                        { return eType == eSymbolEOF; };
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
        eKeywordReturn,

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




