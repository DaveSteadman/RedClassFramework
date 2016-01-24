// -------------------------------------------------------------------------------------------------
// File: RedBufferInput.h
// -------------------------------------------------------------------------------------------------
// Detail: Input buffer constructed from a string, allowing character to be read sequentially while
//         tracking position in the file.
// -------------------------------------------------------------------------------------------------

#pragma once

#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"
#include "RedString.h"
#include "RedChar.h"
#include "RedBufferPos.h"

namespace Red {
namespace Core {

class RedBufferInput
{
public:

    RedBufferInput(void) { Init(); };
    RedBufferInput(const RedString& cNewStr) { Assign(cNewStr); };

    void      Assign(const RedString& cNewStr) { Init(); cStrBuffer=cNewStr; };
    void      Init(void);

    RedChar   GetNextChar(void);
    RedChar   PreviewNextChar(void);
    void      GetCharAndPreview(RedChar& ch, RedChar& previewch);

    void      UngetChar(void) { SetPos(iCharPos-1); };
    void      SkipWhitespace(void);

    RedChar   GetNextNonWhitespaceChar(void)     { SkipWhitespace(); return GetNextChar(); };
    RedChar   PreviewNextNonWhitespaceChar(void) { SkipWhitespace(); return PreviewNextChar(); };

    void      SetStartPos(void) { SetPos(0); };
    void      SetPos(int iNewPos);
    int       GetPos(void) const { return iCharPos; };

    RedBufferPos  GetRowColPos(void) { return RedBufferPos(iRow, iCol); };

    const RedString   StringBuffer(void) const { return cStrBuffer; };
private:

    void AddRow(void);

    typedef RedLinkedList<int> ListType;
    typedef RedLinkedListIterator<int> ListItType;

    ListType    cNewLineCharPosList;
    int         iCharPos;
    int         iRow;
    int         iCol;
    RedString   cStrBuffer;
};

} // Core
} // Red


