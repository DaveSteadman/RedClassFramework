
#pragma once

#include "RedString.h"
#include "RedNumber.h"
#include "RedChar.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedBufferOutput
{
public:

    RedBufferOutput(void)               { Init(); };
    
    void Init(void)                     { cStrBuffer.Init(); cIndentStr="  "; indentlevel=0; };
    void SetIndent(const RedString str) { cIndentStr=str; };

    void Empty(void)                    { Init(); };
    const int IsEmpty(void) const       { return cStrBuffer.IsEmpty(); };

    void WriteNewLine(void)             { cStrBuffer += "\n"; };
    void WriteIndent(void)              { for(int i=0;i<indentlevel;i++) cStrBuffer += cIndentStr; };
    void WriteNewLineWithIndent(void)   { WriteNewLine(); WriteIndent(); };

    void IncreaseIndent(void)           { indentlevel++; };
    void DecreaseIndent(void)           { if(indentlevel>0) indentlevel--; };
    const int IndentLevel(void)         { return indentlevel; };
    void SetIndentLevel(const int l)    { indentlevel=l; };

    void Append(const RedString& cStr)  { cStrBuffer+=cStr; };
    void Append(const RedChar& cCh)     { cStrBuffer+=cCh; };
    void Append(const RedNumber& cNum)  { cStrBuffer+=cNum.DecimalString(); };

    RedString ExtractData(void)         { return cStrBuffer; };

    void AppendIndented(const RedString& cStr);

private:

    RedString cStrBuffer;
    RedString cIndentStr;
    int       indentlevel;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


