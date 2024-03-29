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

#include "RedCoreNamespace.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedToken::Init(void)
{
    cType.Init();
    cText.Init();

    cPredef.Init();
    cNumber.Init();
    cCodePos.Init();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedToken::IsEOF(void) const
{
    if (cPredef.IsSymbolEOF())
        return true;

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedToken::DebugText()
{
    RedDataString cRetStr;

    if (cType.IsValid()) 
    {
        if (cPredef.IsInvalid())
        {
            if      (cType.IsNumber())         { cRetStr = "[num "  + RedDataActions::StringFromNumber(cNumber) + "] ";}
            else if (cType.IsName())           { cRetStr = "[name " + cText                                     + "] ";}
            else if (cType.IsStringLiteral())  { cRetStr = "[str "  + cText                                     + "] ";}
            else if (IsEOF())                  { cRetStr = "<<EOF>> "; }
            else if (cType.IsNonPrintable())   { cRetStr = "[chr: " + RedDataActions::HexadecimalStringFromInt(cText[1]) + "] "; }
        }
        else
        {
            RedTokenPredefMap* pMap = RedTokenPredefMap::getInstance();
            RedDataString cPredefStr;
            if (pMap->FindStringFromPredef(cPredef, cPredefStr))
            {
                cRetStr = "[predef "; 
                cRetStr += cPredefStr;
                cRetStr += "] ";
            }
            else
                cRetStr = "<<Broken Predef>>";
        }
    }
    else
    {
        cRetStr = "<<Undefined>>";
    }
    return cRetStr;
}
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedToken::operator =(const RedToken& cTok)
{
    cType    = cTok.cType;
    cText    = cTok.cText;
    cNumber  = cTok.cNumber;
    cPredef  = cTok.cPredef;
    cCodePos = cTok.cCodePos;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
