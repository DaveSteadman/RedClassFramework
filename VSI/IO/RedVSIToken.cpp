
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIToken.h"
#include "RedBufferInput.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIToken::Init(void)
{
    cType.Init();
    cPredef.Init();

    cNumber.Init();
    cText.Init();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIToken::IsEOF(void)
{
    if (!cType.IsNonPrintable())
        return 0;
 
    RedString cEOFStr;
    
    cEOFStr.Append('\0');
        
    if (cText == cEOFStr)
        return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedVSIToken::GetDebugText(RedVSITokenElementMap& RedVSITokenMap)
{
    RedString cRetStr;

    if      (cType.IsNumber())         { cRetStr = "[num ";    cRetStr += cNumber.DecimalString(); cRetStr += "] "; }
    else if (cType.IsName())           { cRetStr = "[name ";   cRetStr += cText; cRetStr += "] ";}
    else if (cType.IsStringLiteral())  { cRetStr = "[str "; cRetStr += cText; cRetStr += "] ";}
    else if (IsEOF())                  { cRetStr = "<<EOF>> "; }
    else if (cType.IsNonPrintable())   { RedNumber cCh = cText[1]; cRetStr = "[chr: "; cRetStr += cCh.DecimalString(); cRetStr += "] "; }
    else if (cType.IsPredefined())     { cRetStr = "[predef "; RedString lookup; RedVSITokenMap.FindString(cPredef, lookup); cRetStr += lookup; cRetStr += "] ";}
    else if (!cType.IsValid())         { cRetStr = "<<Undefined>>"; }

    return cRetStr;
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIToken::operator =(const RedVSIToken& cTok)
{
    cType    = cTok.cType;
    cText    = cTok.cText;
    cNumber  = cTok.cNumber;
    cPredef  = cTok.cPredef;
    cCodePos = cTok.cCodePos;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
