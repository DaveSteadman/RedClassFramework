
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSITokenType.h"
#include "RedVSITokenElementMap.h"
#include "RedBufferPos.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIToken
{
public:

    RedVSIToken(void) { Init(); };
    RedVSIToken(RedVSIIOElement cNewPredef) { SetPredefined(cNewPredef); };

    void Init(void);

    // operations to construct specific tokens from a known input
    void SetNumber(RedNumber cNewNum)              { Init(); cType.SetNumber();        cNumber=cNewNum; };
    void SetName(RedString cNewStr)                { Init(); cType.SetName();          cText=cNewStr; };
    void SetStringLiteral(RedString cNewStr)       { Init(); cType.SetStringLiteral(); cText=cNewStr; };
    void SetNonPrintable(RedChar cNewChar)         { Init(); cType.SetNonPrintable();  cText=cNewChar; };
    void SetWhitespace(RedString cNewStr)          { Init(); cType.SetWhitespace();    cText=cNewStr; };
    void SetPredefined(RedVSIIOElement cNewPredef) { Init(); cType.SetPredefined();    cPredef=cNewPredef; };

    // Setup
    static RedVSIToken WhitespaceSpaceToken(void)  { RedVSIToken t; t.SetWhitespace(RedString(" "));               return t; };
    static RedVSIToken EOFToken(void)              { RedVSIToken t; t.SetPredefined(RedVSIIOElement::SymbolEOF()); return t; };

    void         SetPos(RedBufferPos cNewPos) { cCodePos = cNewPos; };
    RedBufferPos GetPos(void)                 { return cCodePos; };

    // Basic comparisons
    int IsValid(void) { return (cType.IsValid()); };
    int IsEOF(void);

    // Data Access
    RedVSITokenType Type(void) const        { return cType; };
    RedNumber       GetNumber(void) const   { return cNumber; };
    RedString       GetText(void) const     { return cText; }
    RedVSIIOElement GetPredef(void) const   { return cPredef; };
    RedString       GetDebugText(RedVSITokenElementMap& RedVSITokenMap);

    // Operators
    void operator =(const RedVSIToken& cTok);

private:
    
    // overall type, stating number, string, predefined etc.
    RedVSITokenType cType;
    
    // The text extracted from the buffer
    RedString cText;

    // If the type is predefined, this is relevant
    RedVSIIOElement cPredef;

    // If the type is number, this is relevant
    RedNumber cNumber;

    // Buffer position the token was extracted from. Useful in debugging/logging functionality
    RedBufferPos cCodePos;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedVSIToken kTokenWhitespaceSpace  = RedVSIToken::WhitespaceSpaceToken();
static const RedVSIToken kTokenEOF              = RedVSIToken::EOFToken();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

