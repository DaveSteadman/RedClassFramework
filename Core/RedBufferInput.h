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

#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"
#include "RedDataString.h"
#include "RedDataChar.h"
#include "RedBufferPos.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Input buffer constructed from a string, allowing character to be read sequentially while
/// tracking position in the file.
class RedBufferInput
{
public:

    RedBufferInput(void) { Init(); };
    RedBufferInput(const RedDataString& cNewStr) { Assign(cNewStr); };

    void      Assign(const RedDataString& cNewStr) { Init(); cStrBuffer=cNewStr; };
    void      Init(void);

    RedDataChar   GetNextChar(void);
    RedDataChar   PreviewNextChar(void);
    void      GetCharAndPreview(RedDataChar& ch, RedDataChar& previewch);

    RedDataChar   PreviewAhead(const unsigned IndexAhead);

    void      UngetChar(void) { SetPos(iCharPos-1); };
    void      SkipWhitespace(void);

    RedDataChar   GetNextNonWhitespaceChar(void)     { SkipWhitespace(); return GetNextChar(); };
    RedDataChar   PreviewNextNonWhitespaceChar(void) { SkipWhitespace(); return PreviewNextChar(); };

    void      SetStartPos(void) { SetPos(0); };
    void      SetPos(int iNewPos);
    int       GetPos(void) const { return iCharPos; };

    RedBufferPos  GetRowColPos(void) { return RedBufferPos(iRow, iCol); };

    const RedDataString   StringBuffer(void) const { return cStrBuffer; };
private:

    void AddRow(void);

    typedef RedLinkedList<int>         ListType;
    typedef RedLinkedListIterator<int> ListItType;

    ListType    cNewLineCharPosList;
    int         iCharPos;
    int         iRow;
    int         iCol;
    RedDataString   cStrBuffer;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


