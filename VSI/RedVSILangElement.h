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

#include "RedDataType.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// Definition of the Language Elements. This is an internal type, which does
// not get affected by external issues such as textual or graphical
// representations of the language.
class RedVSILangElement
{
public:

    // Constructor
    RedVSILangElement(void) { eType = eDefaultInvalid; };
    void Init(void)         { eType = eDefaultInvalid; };

    // Command types
    bool                     IsCommand(void) const;
    bool                     IsCommandIf(void) const                         { return eType == eCommandIf; };
    bool                     IsCommandLet(void) const                        { return eType == eCommandLet; };
    bool                     IsCommandLoadCode(void) const                   { return eType == eCommandLoadCode; };
    bool                     IsCommandLog(void) const                        { return eType == eCommandLog; };
    bool                     IsCommandNew(void) const                        { return eType == eCommandNew; };
    bool                     IsCommandPrint(void) const                      { return eType == eCommandPrint; };
    bool                     IsCommandReturn(void) const                     { return eType == eCommandReturn; };
    bool                     IsCommandWhile(void) const                      { return eType == eCommandWhile; };
    static RedVSILangElement CommandIf(void)                                 { return RedVSILangElement(eCommandIf); };
    static RedVSILangElement CommandLet(void)                                { return RedVSILangElement(eCommandLet); };
    static RedVSILangElement CommandLoadCode(void)                           { return RedVSILangElement(eCommandLoadCode); };
    static RedVSILangElement CommandLog(void)                                { return RedVSILangElement(eCommandLog); };
    static RedVSILangElement CommandNew(void)                                { return RedVSILangElement(eCommandNew); };
    static RedVSILangElement CommandPrint(void)                              { return RedVSILangElement(eCommandPrint); };
    static RedVSILangElement CommandReturn(void)                             { return RedVSILangElement(eCommandReturn); };
    static RedVSILangElement CommandWhile(void)                              { return RedVSILangElement(eCommandWhile); };

    // Parse node types
    bool                     IsParse(void) const;
    bool                     IsParseFuncCall(void) const                     { return eType == eParseFuncCall; };
    bool                     IsParseValue(void) const                        { return eType == eParseValue; };
    bool                     IsParseVariable(void) const                     { return eType == eParseVariable; };
    bool                     IsParseBinaryOp(void) const                     { return eType == eParseBinaryOp; };
    bool                     IsParseUnaryOp(void) const                      { return eType == eParseUnaryOp; };
    static RedVSILangElement ParseFuncCall(void)                             { return RedVSILangElement(eParseFuncCall); };
    static RedVSILangElement ParseValue(void)                                { return RedVSILangElement(eParseValue); };
    static RedVSILangElement ParseVariable(void)                             { return RedVSILangElement(eParseVariable); };
    static RedVSILangElement ParseBinaryOp(void)                             { return RedVSILangElement(eParseBinaryOp); };
    static RedVSILangElement ParseUnaryOp(void)                              { return RedVSILangElement(eParseUnaryOp); };

    // Locations
    bool                     IsLocation(void) const;
    bool                     IsLocationHeap(void) const                      { return eType == eLocationHeap; };
    bool                     IsLocationStack(void) const                     { return eType == eLocationStack; };
    bool                     IsLocationAttribute(void) const                 { return eType == eLocationAttribute; };
    static RedVSILangElement LocationHeap(void)                              { return RedVSILangElement(eLocationHeap); };
    static RedVSILangElement LocationStack(void)                             { return RedVSILangElement(eLocationStack); };
    static RedVSILangElement LocationAttribute(void)                         { return RedVSILangElement(eLocationAttribute); };

    // Types
    bool                     IsType(void) const;
    bool                     IsTypeBool(void) const                          { return eType == eTypeBool; };
    bool                     IsTypeChar(void) const                          { return eType == eTypeChar; };
    bool                     IsTypeList(void) const                          { return eType == eTypeList; };
    bool                     IsTypeNumber(void) const                        { return eType == eTypeNumber; };
    bool                     IsTypeRecord(void) const                        { return eType == eTypeRecord; };
    bool                     IsTypeString(void) const                        { return eType == eTypeString; };
    static RedVSILangElement TypeBool(void)                                  { return RedVSILangElement(eTypeBool); };
    static RedVSILangElement TypeChar(void)                                  { return RedVSILangElement(eTypeChar); };
    static RedVSILangElement TypeList(void)                                  { return RedVSILangElement(eTypeList); };
    static RedVSILangElement TypeNumber(void)                                { return RedVSILangElement(eTypeNumber); };
    static RedVSILangElement TypeRecord(void)                                { return RedVSILangElement(eTypeRecord); };
    static RedVSILangElement TypeString(void)                                { return RedVSILangElement(eTypeString); };

    // Binary op types
    bool                     IsBinaryOp(void) const;
    bool                     IsBinaryOpAssignDivide(void) const              { return eType == eBinaryOpAssignDivide; };
    bool                     IsBinaryOpAssignEqual(void) const               { return eType == eBinaryOpAssignEqual; };
    bool                     IsBinaryOpAssignMinus(void) const               { return eType == eBinaryOpAssignMinus; };
    bool                     IsBinaryOpAssignMultiply(void) const            { return eType == eBinaryOpAssignMultiply; };
    bool                     IsBinaryOpAssignPlus(void) const                { return eType == eBinaryOpAssignPlus; };
    bool                     IsBinaryOpCompareEqual(void) const              { return eType == eBinaryOpCompareEqual; };
    bool                     IsBinaryOpCompareNotEqual(void) const           { return eType == eBinaryOpCompareNotEqual; };
    bool                     IsBinaryOpCompareLessThan(void) const           { return eType == eBinaryOpCompareLessThan; };
    bool                     IsBinaryOpCompareGreaterThan(void) const        { return eType == eBinaryOpCompareGreaterThan; };
    bool                     IsBinaryOpCompareLessThanOrEqual(void) const    { return eType == eBinaryOpCompareLessThanOrEqual; };
    bool                     IsBinaryOpCompareGreaterThanOrEqual(void) const { return eType == eBinaryOpCompareGreaterThanOrEqual; };
    bool                     IsBinaryOpDivide(void) const                    { return eType == eBinaryOpDivide; };
    bool                     IsBinaryOpLogicAnd(void) const                  { return eType == eBinaryOpLogicAnd; };
    bool                     IsBinaryOpLogicOr(void) const                   { return eType == eBinaryOpLogicOr; };
    bool                     IsBinaryOpMinus(void) const                     { return eType == eBinaryOpMinus; };
    bool                     IsBinaryOpMultiply(void) const                  { return eType == eBinaryOpMultiply; };
    bool                     IsBinaryOpPlus(void) const                      { return eType == eBinaryOpPlus; };
    bool                     IsBinaryOpPower(void) const                     { return eType == eBinaryOpPower; };
    static RedVSILangElement BinaryOpAssignDivide(void)                      { return RedVSILangElement(eBinaryOpAssignDivide); };
    static RedVSILangElement BinaryOpAssignEqual(void)                       { return RedVSILangElement(eBinaryOpAssignEqual); };
    static RedVSILangElement BinaryOpAssignMinus(void)                       { return RedVSILangElement(eBinaryOpAssignMinus); };
    static RedVSILangElement BinaryOpAssignMultiply(void)                    { return RedVSILangElement(eBinaryOpAssignMultiply); };
    static RedVSILangElement BinaryOpAssignPlus(void)                        { return RedVSILangElement(eBinaryOpAssignPlus); };
    static RedVSILangElement BinaryOpCompareEqual(void)                      { return RedVSILangElement(eBinaryOpCompareEqual); };
    static RedVSILangElement BinaryOpCompareNotEqual(void)                   { return RedVSILangElement(eBinaryOpCompareNotEqual); };
    static RedVSILangElement BinaryOpCompareLessThan(void)                   { return RedVSILangElement(eBinaryOpCompareLessThan); };
    static RedVSILangElement BinaryOpCompareGreaterThan(void)                { return RedVSILangElement(eBinaryOpCompareGreaterThan); };
    static RedVSILangElement BinaryOpCompareLessThanOrEqual(void)            { return RedVSILangElement(eBinaryOpCompareLessThanOrEqual); };
    static RedVSILangElement BinaryOpCompareGreaterThanOrEqual(void)         { return RedVSILangElement(eBinaryOpCompareGreaterThanOrEqual); };
    static RedVSILangElement BinaryOpDivide(void)                            { return RedVSILangElement(eBinaryOpDivide); };
    static RedVSILangElement BinaryOpItemAtAddr(void)                        { return RedVSILangElement(eBinaryOpItemAtAddr); };
    static RedVSILangElement BinaryOpLogicAnd(void)                          { return RedVSILangElement(eBinaryOpLogicAnd); };
    static RedVSILangElement BinaryOpLogicOr(void)                           { return RedVSILangElement(eBinaryOpLogicOr); };
    static RedVSILangElement BinaryOpMinus(void)                             { return RedVSILangElement(eBinaryOpMinus); };
    static RedVSILangElement BinaryOpMultiply(void)                          { return RedVSILangElement(eBinaryOpMultiply); };
    static RedVSILangElement BinaryOpPlus(void)                              { return RedVSILangElement(eBinaryOpPlus); };
    static RedVSILangElement BinaryOpPower(void)                             { return RedVSILangElement(eBinaryOpPower); };

    // Unary op types
    bool                     IsUnaryOp(void) const;
    bool                     IsUnaryOpMinus(void) const                      { return eType == eUnaryOpMinus; };
    bool                     IsUnaryOpLogicNot(void) const                   { return eType == eUnaryOpLogicNot; };
    static RedVSILangElement UnaryOpMinus(void)                              { return RedVSILangElement(eUnaryOpMinus); };
    static RedVSILangElement UnaryOpLogicNot(void)                           { return RedVSILangElement(eUnaryOpLogicNot); };


    // High level Query routines
    bool IsOp(void) const;
    bool IsAssignOp(void) const;
    bool IsLogicOp(void) const;
    bool IsCompareOp(void) const;

    // Data Type conversions, between the Core type, and the enumerations here for types
    static RedDataType       DataTypeForLangElemType(const RedVSILangElement& LangType);
    static RedVSILangElement LangElemTypeForDataType(const RedDataType& CoreType);

    // Operators
    void operator =(const RedVSILangElement cNewVal) { eType=cNewVal.eType; };

    int iElem(void) const { return (int)eType; };

protected:

    typedef enum TELangElem
    {
        eDefaultInvalid = 0,

        eCommandIf,
        eCommandLet,
        eCommandLoadCode,
        eCommandLog,
        eCommandNew,
        eCommandPrint,
        eCommandReturn,
        eCommandWhile,

        eParseFuncCall,
        eParseValue,
        eParseVariable,
        eParseBinaryOp,
        eParseUnaryOp,

        // Data locations
        eLocationHeap,
        eLocationStack,
        eLocationAttribute,

        // Types
        eTypeBool,
        eTypeChar,
        eTypeList,
        eTypeNumber,
        eTypeRecord,
        eTypeString,

        // Binary Ops
        eBinaryOpAssignDivide,
        eBinaryOpAssignEqual,
        eBinaryOpAssignMinus,
        eBinaryOpAssignMultiply,
        eBinaryOpAssignPlus,
        eBinaryOpCompareEqual,
        eBinaryOpCompareNotEqual,
        eBinaryOpCompareLessThan,
        eBinaryOpCompareGreaterThan,
        eBinaryOpCompareLessThanOrEqual,
        eBinaryOpCompareGreaterThanOrEqual,
        eBinaryOpDivide,
        eBinaryOpItemAtAddr,
        eBinaryOpLogicAnd,
        eBinaryOpLogicOr,
        eBinaryOpMinus,
        eBinaryOpMultiply,
        eBinaryOpPlus,
        eBinaryOpPower,

        eUnaryOpMinus,
        eUnaryOpLogicNot

    } TELangElem;

    RedVSILangElement(enum TELangElem eNewType) { eType = eNewType; };

private:

    TELangElem eType; 
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static RedVSILangElement kLangElementTypeBool                = RedVSILangElement::TypeBool();
static RedVSILangElement kLangElementTypeChar                = RedVSILangElement::TypeChar();
static RedVSILangElement kLangElementTypeList                = RedVSILangElement::TypeList();
static RedVSILangElement kLangElementTypeNumber              = RedVSILangElement::TypeNumber();
static RedVSILangElement kLangElementTypeRecord              = RedVSILangElement::TypeRecord();
static RedVSILangElement kLangElementTypeString              = RedVSILangElement::TypeString();

static RedVSILangElement kLangElementLocationHeap            = RedVSILangElement::LocationHeap();
static RedVSILangElement kLangElementLocationStack           = RedVSILangElement::LocationStack();
static RedVSILangElement kLangElementLocationAttribute       = RedVSILangElement::LocationAttribute();

static RedVSILangElement kLangElementCommandNew              = RedVSILangElement::CommandNew();
static RedVSILangElement kLangElementCommandLet              = RedVSILangElement::CommandLet();
static RedVSILangElement kLangElementCommandLoadCode         = RedVSILangElement::CommandLoadCode();
static RedVSILangElement kLangElementCommandLog              = RedVSILangElement::CommandLog();
static RedVSILangElement kLangElementCommandIf               = RedVSILangElement::CommandIf();
static RedVSILangElement kLangElementCommandReturn           = RedVSILangElement::CommandReturn();
static RedVSILangElement kLangElementCommandWhile            = RedVSILangElement::CommandWhile();

static RedVSILangElement kLangElementBinaryOpAssignDivide    = RedVSILangElement::BinaryOpAssignDivide();
static RedVSILangElement kLangElementBinaryOpAssignEqual     = RedVSILangElement::BinaryOpAssignEqual();
static RedVSILangElement kLangElementBinaryOpAssignMinus     = RedVSILangElement::BinaryOpAssignMinus();
static RedVSILangElement kLangElementBinaryOpAssignMultiply  = RedVSILangElement::BinaryOpAssignMultiply();
static RedVSILangElement kLangElementBinaryOpAssignPlus      = RedVSILangElement::BinaryOpAssignPlus();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVSILangElement& lhs, const RedVSILangElement& rhs);
bool operator!=(const RedVSILangElement& lhs, const RedVSILangElement& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


