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
    RedVSILangElement(void) { eType = TEVSIElem::eDefaultInvalid; };
    void Init(void)         { eType = TEVSIElem::eDefaultInvalid; };

    bool                     IsInvalid(void) const                           { return eType == TEVSIElem::eDefaultInvalid; };

    // Command types
    bool                     IsCommand(void) const;
    bool                     IsCommandIf(void) const                         { return eType == TEVSIElem::eCommandIf; };
    bool                     IsCommandLet(void) const                        { return eType == TEVSIElem::eCommandLet; };
    bool                     IsCommandLoadCode(void) const                   { return eType == TEVSIElem::eCommandLoadCode; };
    bool                     IsCommandLog(void) const                        { return eType == TEVSIElem::eCommandLog; };
    bool                     IsCommandNew(void) const                        { return eType == TEVSIElem::eCommandNew; };
    bool                     IsCommandPrint(void) const                      { return eType == TEVSIElem::eCommandPrint; };
    bool                     IsCommandReturn(void) const                     { return eType == TEVSIElem::eCommandReturn; };
    bool                     IsCommandWhile(void) const                      { return eType == TEVSIElem::eCommandWhile; };
    static RedVSILangElement CommandIf(void)                                 { return RedVSILangElement(TEVSIElem::eCommandIf); };
    static RedVSILangElement CommandLet(void)                                { return RedVSILangElement(TEVSIElem::eCommandLet); };
    static RedVSILangElement CommandLoadCode(void)                           { return RedVSILangElement(TEVSIElem::eCommandLoadCode); };
    static RedVSILangElement CommandLog(void)                                { return RedVSILangElement(TEVSIElem::eCommandLog); };
    static RedVSILangElement CommandNew(void)                                { return RedVSILangElement(TEVSIElem::eCommandNew); };
    static RedVSILangElement CommandPrint(void)                              { return RedVSILangElement(TEVSIElem::eCommandPrint); };
    static RedVSILangElement CommandReturn(void)                             { return RedVSILangElement(TEVSIElem::eCommandReturn); };
    static RedVSILangElement CommandWhile(void)                              { return RedVSILangElement(TEVSIElem::eCommandWhile); };

    // Parse node types
    bool                     IsParse(void) const;
    bool                     IsParseFuncCall(void) const                     { return eType == TEVSIElem::eParseFuncCall; };
    bool                     IsParseValue(void) const                        { return eType == TEVSIElem::eParseValue; };
    bool                     IsParseVariable(void) const                     { return eType == TEVSIElem::eParseVariable; };
    bool                     IsParseBinaryOp(void) const                     { return eType == TEVSIElem::eParseBinaryOp; };
    bool                     IsParseUnaryOp(void) const                      { return eType == TEVSIElem::eParseUnaryOp; };
    static RedVSILangElement ParseFuncCall(void)                             { return RedVSILangElement(TEVSIElem::eParseFuncCall); };
    static RedVSILangElement ParseValue(void)                                { return RedVSILangElement(TEVSIElem::eParseValue); };
    static RedVSILangElement ParseVariable(void)                             { return RedVSILangElement(TEVSIElem::eParseVariable); };
    static RedVSILangElement ParseBinaryOp(void)                             { return RedVSILangElement(TEVSIElem::eParseBinaryOp); };
    static RedVSILangElement ParseUnaryOp(void)                              { return RedVSILangElement(TEVSIElem::eParseUnaryOp); };

    // Locations
    bool                     IsLocation(void) const;
    bool                     IsLocationHeap(void) const                      { return eType == TEVSIElem::eLocationHeap; };
    bool                     IsLocationStack(void) const                     { return eType == TEVSIElem::eLocationStack; };
    bool                     IsLocationAttribute(void) const                 { return eType == TEVSIElem::eLocationAttribute; };
    static RedVSILangElement LocationHeap(void)                              { return RedVSILangElement(TEVSIElem::eLocationHeap); };
    static RedVSILangElement LocationStack(void)                             { return RedVSILangElement(TEVSIElem::eLocationStack); };
    static RedVSILangElement LocationAttribute(void)                         { return RedVSILangElement(TEVSIElem::eLocationAttribute); };

    // Types
    bool                     IsType(void) const;
    bool                     IsTypeBool(void) const                          { return eType == TEVSIElem::eTypeBool; };
    bool                     IsTypeChar(void) const                          { return eType == TEVSIElem::eTypeChar; };
    bool                     IsTypeList(void) const                          { return eType == TEVSIElem::eTypeList; };
    bool                     IsTypeNumber(void) const                        { return eType == TEVSIElem::eTypeNumber; };
    bool                     IsTypeRecord(void) const                        { return eType == TEVSIElem::eTypeRecord; };
    bool                     IsTypeString(void) const                        { return eType == TEVSIElem::eTypeString; };
    static RedVSILangElement TypeBool(void)                                  { return RedVSILangElement(TEVSIElem::eTypeBool); };
    static RedVSILangElement TypeChar(void)                                  { return RedVSILangElement(TEVSIElem::eTypeChar); };
    static RedVSILangElement TypeList(void)                                  { return RedVSILangElement(TEVSIElem::eTypeList); };
    static RedVSILangElement TypeNumber(void)                                { return RedVSILangElement(TEVSIElem::eTypeNumber); };
    static RedVSILangElement TypeRecord(void)                                { return RedVSILangElement(TEVSIElem::eTypeRecord); };
    static RedVSILangElement TypeString(void)                                { return RedVSILangElement(TEVSIElem::eTypeString); };

    // Binary op types
    bool                     IsBinaryOp(void) const;
    bool                     IsBinaryOpAssignDivide(void) const              { return eType == TEVSIElem::eBinaryOpAssignDivide; };
    bool                     IsBinaryOpAssignEqual(void) const               { return eType == TEVSIElem::eBinaryOpAssignEqual; };
    bool                     IsBinaryOpAssignMinus(void) const               { return eType == TEVSIElem::eBinaryOpAssignMinus; };
    bool                     IsBinaryOpAssignMultiply(void) const            { return eType == TEVSIElem::eBinaryOpAssignMultiply; };
    bool                     IsBinaryOpAssignPlus(void) const                { return eType == TEVSIElem::eBinaryOpAssignPlus; };
    bool                     IsBinaryOpCompareEqual(void) const              { return eType == TEVSIElem::eBinaryOpCompareEqual; };
    bool                     IsBinaryOpCompareNotEqual(void) const           { return eType == TEVSIElem::eBinaryOpCompareNotEqual; };
    bool                     IsBinaryOpCompareLessThan(void) const           { return eType == TEVSIElem::eBinaryOpCompareLessThan; };
    bool                     IsBinaryOpCompareGreaterThan(void) const        { return eType == TEVSIElem::eBinaryOpCompareGreaterThan; };
    bool                     IsBinaryOpCompareLessThanOrEqual(void) const    { return eType == TEVSIElem::eBinaryOpCompareLessThanOrEqual; };
    bool                     IsBinaryOpCompareGreaterThanOrEqual(void) const { return eType == TEVSIElem::eBinaryOpCompareGreaterThanOrEqual; };
    bool                     IsBinaryOpDivide(void) const                    { return eType == TEVSIElem::eBinaryOpDivide; };
    bool                     IsBinaryOpLogicAnd(void) const                  { return eType == TEVSIElem::eBinaryOpLogicAnd; };
    bool                     IsBinaryOpLogicOr(void) const                   { return eType == TEVSIElem::eBinaryOpLogicOr; };
    bool                     IsBinaryOpMinus(void) const                     { return eType == TEVSIElem::eBinaryOpMinus; };
    bool                     IsBinaryOpMultiply(void) const                  { return eType == TEVSIElem::eBinaryOpMultiply; };
    bool                     IsBinaryOpPlus(void) const                      { return eType == TEVSIElem::eBinaryOpPlus; };
    bool                     IsBinaryOpPower(void) const                     { return eType == TEVSIElem::eBinaryOpPower; };
    static RedVSILangElement BinaryOpAssignDivide(void)                      { return RedVSILangElement(TEVSIElem::eBinaryOpAssignDivide); };
    static RedVSILangElement BinaryOpAssignEqual(void)                       { return RedVSILangElement(TEVSIElem::eBinaryOpAssignEqual); };
    static RedVSILangElement BinaryOpAssignMinus(void)                       { return RedVSILangElement(TEVSIElem::eBinaryOpAssignMinus); };
    static RedVSILangElement BinaryOpAssignMultiply(void)                    { return RedVSILangElement(TEVSIElem::eBinaryOpAssignMultiply); };
    static RedVSILangElement BinaryOpAssignPlus(void)                        { return RedVSILangElement(TEVSIElem::eBinaryOpAssignPlus); };
    static RedVSILangElement BinaryOpCompareEqual(void)                      { return RedVSILangElement(TEVSIElem::eBinaryOpCompareEqual); };
    static RedVSILangElement BinaryOpCompareNotEqual(void)                   { return RedVSILangElement(TEVSIElem::eBinaryOpCompareNotEqual); };
    static RedVSILangElement BinaryOpCompareLessThan(void)                   { return RedVSILangElement(TEVSIElem::eBinaryOpCompareLessThan); };
    static RedVSILangElement BinaryOpCompareGreaterThan(void)                { return RedVSILangElement(TEVSIElem::eBinaryOpCompareGreaterThan); };
    static RedVSILangElement BinaryOpCompareLessThanOrEqual(void)            { return RedVSILangElement(TEVSIElem::eBinaryOpCompareLessThanOrEqual); };
    static RedVSILangElement BinaryOpCompareGreaterThanOrEqual(void)         { return RedVSILangElement(TEVSIElem::eBinaryOpCompareGreaterThanOrEqual); };
    static RedVSILangElement BinaryOpDivide(void)                            { return RedVSILangElement(TEVSIElem::eBinaryOpDivide); };
    static RedVSILangElement BinaryOpItemAtAddr(void)                        { return RedVSILangElement(TEVSIElem::eBinaryOpItemAtAddr); };
    static RedVSILangElement BinaryOpLogicAnd(void)                          { return RedVSILangElement(TEVSIElem::eBinaryOpLogicAnd); };
    static RedVSILangElement BinaryOpLogicOr(void)                           { return RedVSILangElement(TEVSIElem::eBinaryOpLogicOr); };
    static RedVSILangElement BinaryOpMinus(void)                             { return RedVSILangElement(TEVSIElem::eBinaryOpMinus); };
    static RedVSILangElement BinaryOpMultiply(void)                          { return RedVSILangElement(TEVSIElem::eBinaryOpMultiply); };
    static RedVSILangElement BinaryOpPlus(void)                              { return RedVSILangElement(TEVSIElem::eBinaryOpPlus); };
    static RedVSILangElement BinaryOpPower(void)                             { return RedVSILangElement(TEVSIElem::eBinaryOpPower); };

    // Unary op types
    bool                     IsUnaryOp(void) const;
    bool                     IsUnaryOpMinus(void) const                      { return eType == TEVSIElem::eUnaryOpMinus; };
    bool                     IsUnaryOpLogicNot(void) const                   { return eType == TEVSIElem::eUnaryOpLogicNot; };
    static RedVSILangElement UnaryOpMinus(void)                              { return RedVSILangElement(TEVSIElem::eUnaryOpMinus); };
    static RedVSILangElement UnaryOpLogicNot(void)                           { return RedVSILangElement(TEVSIElem::eUnaryOpLogicNot); };


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

    enum class TEVSIElem
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
    };

    RedVSILangElement(TEVSIElem eNewType) { eType = eNewType; };

private:

    TEVSIElem eType = TEVSIElem::eDefaultInvalid;
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


