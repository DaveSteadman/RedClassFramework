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

#include "RedString.h"
#include "RedNumber.h"
#include "RedChar.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Output buffer class, accumulating output strings. Has additional functionality to handle indented
/// lines.
class RedBufferOutput
{
public:

    RedBufferOutput(void)                { Init(); };
    
    void Init(void)                      { cStrBuffer.Init(); cIndentStr="  "; indentlevel=0; };
    void SetIndent(const RedString& str) { cIndentStr=str; };

    void Empty(void)                     { Init(); };
    bool IsEmpty(void) const             { return cStrBuffer.IsEmpty(); };

    void WriteNewLine(void)              { cStrBuffer += "\n"; };
    void WriteIndent(void)               { for(int i=0;i<indentlevel;i++) cStrBuffer += cIndentStr; };
    void WriteNewLineWithIndent(void)    { WriteNewLine(); WriteIndent(); };

    void IncreaseIndent(void)            { indentlevel++; };
    void DecreaseIndent(void)            { if (indentlevel>0) indentlevel--; };
    int  IndentLevel(void)               { return indentlevel; };
    void SetIndentLevel(const int l)     { indentlevel=l; };

    void Append(const RedString& cStr)   { cStrBuffer+=cStr; };
    void Append(const RedChar& cCh)      { cStrBuffer+=cCh; };
    void Append(const RedNumber& cNum)   { cStrBuffer+=cNum.DecimalString(); };

    RedString ExtractData(void) const    { return cStrBuffer; };

    void AppendIndented(const RedString& cStr);

    friend RedBufferOutput& operator<<(RedBufferOutput& outputbuf, const char* newstr)      { outputbuf.Append(newstr);            return outputbuf; };
    friend RedBufferOutput& operator<<(RedBufferOutput& outputbuf, const int newval)        { outputbuf.Append(RedNumber(newval)); return outputbuf; };
    friend RedBufferOutput& operator<<(RedBufferOutput& outputbuf, const RedString& newstr) { outputbuf.Append(newstr);            return outputbuf; };
    friend RedBufferOutput& operator<<(RedBufferOutput& outputbuf, const RedChar& newch)    { outputbuf.Append(newch);             return outputbuf; };
    friend RedBufferOutput& operator<<(RedBufferOutput& outputbuf, const RedNumber& newnum) { outputbuf.Append(newnum);            return outputbuf; };
    
private:

    RedString cStrBuffer;
    RedString cIndentStr;
    int       indentlevel;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


