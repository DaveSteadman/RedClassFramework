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

#include "RedDataType.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

/// Definition of the Language Elements. This is an internal type, which does
/// not get affected by external issues such as textual or graphical
/// representations of the language.
class RedVSILangElement
{
public:

    // Constructor
    RedVSILangElement(void) { eType = eDefaultInvalid; };
    void Init(void)         { eType = eDefaultInvalid; };

    // Command types
    const bool                     IsCommand(void) const;
    const bool                     IsCommandNew(void) const                        { return eType == eCommandNew; };
    const bool                     IsCommandLet(void) const                        { return eType == eCommandLet; };
    const bool                     IsCommandIf(void) const                         { return eType == eCommandIf; };
    const bool                     IsCommandWhile(void) const                      { return eType == eCommandWhile; };
    const bool                     IsCommandReturn(void) const                     { return eType == eCommandReturn; };
    static const RedVSILangElement CommandNew(void)                                { return RedVSILangElement(eCommandNew); };
    static const RedVSILangElement CommandLet(void)                                { return RedVSILangElement(eCommandLet); };
    static const RedVSILangElement CommandIf(void)                                 { return RedVSILangElement(eCommandIf); };
    static const RedVSILangElement CommandWhile(void)                              { return RedVSILangElement(eCommandWhile); };
    static const RedVSILangElement CommandReturn(void)                             { return RedVSILangElement(eCommandReturn); };

    // Parse node types
    const bool                     IsParse(void) const;
    const bool                     IsParseFuncCall(void) const                     { return eType == eParseFuncCall; };
    const bool                     IsParseValue(void) const                        { return eType == eParseValue; };
    const bool                     IsParseVariable(void) const                     { return eType == eParseVariable; };
    const bool                     IsParseBinaryOp(void) const                     { return eType == eParseBinaryOp; };
    const bool                     IsParseUnaryOp(void) const                      { return eType == eParseUnaryOp; };
    static const RedVSILangElement ParseFuncCall(void)                             { return RedVSILangElement(eParseFuncCall); };
    static const RedVSILangElement ParseValue(void)                                { return RedVSILangElement(eParseValue); };
    static const RedVSILangElement ParseVariable(void)                             { return RedVSILangElement(eParseVariable); };
    static const RedVSILangElement ParseBinaryOp(void)                             { return RedVSILangElement(eParseBinaryOp); };
    static const RedVSILangElement ParseUnaryOp(void)                              { return RedVSILangElement(eParseUnaryOp); };

    // Locations
    const bool                     IsLocation(void) const;
    const bool                     IsLocationHeap(void) const                      { return eType == eLocationHeap; };
    const bool                     IsLocationStack(void) const                     { return eType == eLocationStack; };
    const bool                     IsLocationAttribute(void) const                 { return eType == eLocationAttribute; };
    static const RedVSILangElement LocationHeap(void)                              { return RedVSILangElement(eLocationHeap); };
    static const RedVSILangElement LocationStack(void)                             { return RedVSILangElement(eLocationStack); };
    static const RedVSILangElement LocationAttribute(void)                         { return RedVSILangElement(eLocationAttribute); };

    // Types
    const bool                     IsType(void) const;
    const bool                     IsTypeArray(void) const                         { return eType == eTypeArray; };
    const bool                     IsTypeBool(void) const                          { return eType == eTypeBool; };
    const bool                     IsTypeChar(void) const                          { return eType == eTypeChar; };
    const bool                     IsTypeNumber(void) const                        { return eType == eTypeNumber; };
    const bool                     IsTypeString(void) const                        { return eType == eTypeString; };
    static const RedVSILangElement TypeArray(void)                                 { return RedVSILangElement(eTypeArray); };
    static const RedVSILangElement TypeBool(void)                                  { return RedVSILangElement(eTypeBool); };
    static const RedVSILangElement TypeChar(void)                                  { return RedVSILangElement(eTypeChar); };
    static const RedVSILangElement TypeNumber(void)                                { return RedVSILangElement(eTypeNumber); };
    static const RedVSILangElement TypeString(void)                                { return RedVSILangElement(eTypeString); };

    // Binary op types
    const bool                     IsBinaryOp(void) const;
    const bool                     IsBinaryOpAssignDivide(void) const              { return eType == eBinaryOpAssignDivide; };
    const bool                     IsBinaryOpAssignEqual(void) const               { return eType == eBinaryOpAssignEqual; };
    const bool                     IsBinaryOpAssignMinus(void) const               { return eType == eBinaryOpAssignMinus; };
    const bool                     IsBinaryOpAssignMultiply(void) const            { return eType == eBinaryOpAssignMultiply; };
    const bool                     IsBinaryOpAssignPlus(void) const                { return eType == eBinaryOpAssignPlus; };
    const bool                     IsBinaryOpCompareEqual(void) const              { return eType == eBinaryOpCompareEqual; };
    const bool                     IsBinaryOpCompareNotEqual(void) const           { return eType == eBinaryOpCompareNotEqual; };
    const bool                     IsBinaryOpCompareLessThan(void) const           { return eType == eBinaryOpCompareLessThan; };
    const bool                     IsBinaryOpCompareGreaterThan(void) const        { return eType == eBinaryOpCompareGreaterThan; };
    const bool                     IsBinaryOpCompareLessThanOrEqual(void) const    { return eType == eBinaryOpCompareLessThanOrEqual; };
    const bool                     IsBinaryOpCompareGreaterThanOrEqual(void) const { return eType == eBinaryOpCompareGreaterThanOrEqual; };
    const bool                     IsBinaryOpDivide(void) const                    { return eType == eBinaryOpDivide; };
    const bool                     IsBinaryOpLogicAnd(void) const                  { return eType == eBinaryOpLogicAnd; };
    const bool                     IsBinaryOpLogicOr(void) const                   { return eType == eBinaryOpLogicOr; };
    const bool                     IsBinaryOpMinus(void) const                     { return eType == eBinaryOpMinus; };
    const bool                     IsBinaryOpMultiply(void) const                  { return eType == eBinaryOpMultiply; };
    const bool                     IsBinaryOpPlus(void) const                      { return eType == eBinaryOpPlus; };
    const bool                     IsBinaryOpPower(void) const                     { return eType == eBinaryOpPower; };
    static const RedVSILangElement BinaryOpAssignDivide(void)                      { return RedVSILangElement(eBinaryOpAssignDivide); };
    static const RedVSILangElement BinaryOpAssignEqual(void)                       { return RedVSILangElement(eBinaryOpAssignEqual); };
    static const RedVSILangElement BinaryOpAssignMinus(void)                       { return RedVSILangElement(eBinaryOpAssignMinus); };
    static const RedVSILangElement BinaryOpAssignMultiply(void)                    { return RedVSILangElement(eBinaryOpAssignMultiply); };
    static const RedVSILangElement BinaryOpAssignPlus(void)                        { return RedVSILangElement(eBinaryOpAssignPlus); };
    static const RedVSILangElement BinaryOpCompareEqual(void)                      { return RedVSILangElement(eBinaryOpCompareEqual); };
    static const RedVSILangElement BinaryOpCompareNotEqual(void)                   { return RedVSILangElement(eBinaryOpCompareNotEqual); };
    static const RedVSILangElement BinaryOpCompareLessThan(void)                   { return RedVSILangElement(eBinaryOpCompareLessThan); };
    static const RedVSILangElement BinaryOpCompareGreaterThan(void)                { return RedVSILangElement(eBinaryOpCompareGreaterThan); };
    static const RedVSILangElement BinaryOpCompareLessThanOrEqual(void)            { return RedVSILangElement(eBinaryOpCompareLessThanOrEqual); };
    static const RedVSILangElement BinaryOpCompareGreaterThanOrEqual(void)         { return RedVSILangElement(eBinaryOpCompareGreaterThanOrEqual); };
    static const RedVSILangElement BinaryOpDivide(void)                            { return RedVSILangElement(eBinaryOpDivide); };
    static const RedVSILangElement BinaryOpItemAtAddr(void)                        { return RedVSILangElement(eBinaryOpItemAtAddr); };
    static const RedVSILangElement BinaryOpLogicAnd(void)                          { return RedVSILangElement(eBinaryOpLogicAnd); };
    static const RedVSILangElement BinaryOpLogicOr(void)                           { return RedVSILangElement(eBinaryOpLogicOr); };
    static const RedVSILangElement BinaryOpMinus(void)                             { return RedVSILangElement(eBinaryOpMinus); };
    static const RedVSILangElement BinaryOpMultiply(void)                          { return RedVSILangElement(eBinaryOpMultiply); };
    static const RedVSILangElement BinaryOpPlus(void)                              { return RedVSILangElement(eBinaryOpPlus); };
    static const RedVSILangElement BinaryOpPower(void)                             { return RedVSILangElement(eBinaryOpPower); };

    // Unary op types
    const bool                     IsUnaryOp(void) const;
    const bool                     IsUnaryOpMinus(void) const                      { return eType == eUnaryOpMinus; };
    const bool                     IsUnaryOpLogicNot(void) const                   { return eType == eUnaryOpLogicNot; };
    static const RedVSILangElement UnaryOpMinus(void)                              { return RedVSILangElement(eUnaryOpMinus); };
    static const RedVSILangElement UnaryOpLogicNot(void)                           { return RedVSILangElement(eUnaryOpLogicNot); };


    // High level Query routines
    const bool IsOp(void) const;
    const bool IsAssignOp(void) const;
    const bool IsLogicOp(void) const;
    const bool IsCompareOp(void) const;

    // Data Type conversions, between the Core type, and the enumerations here for types
    static RedDataType       DataTypeForLangElemType(const RedVSILangElement& LangType);
    static RedVSILangElement LangElemTypeForDataType(const RedDataType& CoreType);

    // Operators
    void operator =(const RedVSILangElement cNewVal) { eType=cNewVal.eType; };

    const bool iElem(void) const { return (int)eType; };

protected:

    typedef enum TELangElem
    {
        eDefaultInvalid = 0,

        eCommandNew,
        eCommandLet,
        eCommandIf,
        eCommandReturn,
        eCommandWhile,

        eParseFuncCall,
        eParseValue,
        eParseVariable,
        eParseBinaryOp,
        eParseUnaryOp,

        eLocationHeap,
        eLocationStack,
        eLocationAttribute,

        eTypeArray,
        eTypeBool,
        eTypeChar,
        eTypeNumber,
        eTypeString,

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

static const RedVSILangElement kLangElementTypeArray               = RedVSILangElement::TypeArray();
static const RedVSILangElement kLangElementTypeBool                = RedVSILangElement::TypeBool();
static const RedVSILangElement kLangElementTypeChar                = RedVSILangElement::TypeChar();
static const RedVSILangElement kLangElementTypeNumber              = RedVSILangElement::TypeNumber();
static const RedVSILangElement kLangElementTypeString              = RedVSILangElement::TypeString();

static const RedVSILangElement kLangElementLocationHeap            = RedVSILangElement::LocationHeap();
static const RedVSILangElement kLangElementLocationStack           = RedVSILangElement::LocationStack();
static const RedVSILangElement kLangElementLocationAttribute       = RedVSILangElement::LocationAttribute();

static const RedVSILangElement kLangElementCommandNew              = RedVSILangElement::CommandNew();
static const RedVSILangElement kLangElementCommandLet              = RedVSILangElement::CommandLet();
static const RedVSILangElement kLangElementCommandIf               = RedVSILangElement::CommandIf();
static const RedVSILangElement kLangElementCommandReturn           = RedVSILangElement::CommandReturn();
static const RedVSILangElement kLangElementCommandWhile            = RedVSILangElement::CommandWhile();

static const RedVSILangElement kLangElementBinaryOpAssignDivide    = RedVSILangElement::BinaryOpAssignDivide();
static const RedVSILangElement kLangElementBinaryOpAssignEqual     = RedVSILangElement::BinaryOpAssignEqual();
static const RedVSILangElement kLangElementBinaryOpAssignMinus     = RedVSILangElement::BinaryOpAssignMinus();
static const RedVSILangElement kLangElementBinaryOpAssignMultiply  = RedVSILangElement::BinaryOpAssignMultiply();
static const RedVSILangElement kLangElementBinaryOpAssignPlus      = RedVSILangElement::BinaryOpAssignPlus();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVSILangElement& lhs, const RedVSILangElement& rhs);
bool operator!=(const RedVSILangElement& lhs, const RedVSILangElement& rhs);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


