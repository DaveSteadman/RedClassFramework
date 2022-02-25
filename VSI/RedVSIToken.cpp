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

bool RedVSIToken::IsEOF(void) const
{
    if (!cType.IsNonPrintable())
        return false;
 
    RedDataString cEOFStr;
    
    cEOFStr.Append('\0');

    if (cText == cEOFStr)
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedVSIToken::DebugText(RedVSITokenElementMap& RedVSITokenMap)
{
    RedDataString cRetStr;

    if      (cType.IsNumber())         { cRetStr = "[num ";    cRetStr += cNumber.DecimalString(); cRetStr += "] "; }
    else if (cType.IsName())           { cRetStr = "[name ";   cRetStr += cText; cRetStr += "] ";}
    else if (cType.IsStringLiteral())  { cRetStr = "[str "; cRetStr += cText; cRetStr += "] ";}
    else if (IsEOF())                  { cRetStr = "<<EOF>> "; }
    else if (cType.IsNonPrintable())   { RedDataNumber cCh = cText[1]; cRetStr = "[chr: "; cRetStr += cCh.DecimalString(); cRetStr += "] "; }
    else if (cType.IsPredefined())     { cRetStr = "[predef "; RedDataString lookup; RedVSITokenMap.FindString(cPredef, lookup); cRetStr += lookup; cRetStr += "] ";}
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
