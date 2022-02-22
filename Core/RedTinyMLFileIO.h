
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

#include "RedCoreNamespace.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef enum TESerialiseType { eDenseContent, eLinedIndentedContent } TESerialiseType;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class exists to provide complex actions on Core nodes. The Core node classes remain focussed
/// on their role of storage and memory management, while this class can acquire increasingly complex
/// bulky routines.
class RedTinyMLFileIO
{
public:

    // IO
    static RedResult          CreateTmlFromFile(const RedString& filepath, RedTinyMLElement** newTmlElement);
    static RedResult          CreateFileFromTml(const RedTinyMLElement* tmlElement, const RedString& filepath, const TESerialiseType writeStyle);
    static RedTinyMLElement*  ParseCore(const RedString& inputStr);
    static RedTinyMLElement*  ParseCore(RedBufferInput& inputBuf);
    static void               SerialiseCore(RedBufferOutput& outputBuf, const RedTinyMLElement* topTmlNode, const TESerialiseType eMode);

private:
    static bool               ReadName      (RedBufferInput& inputBuf, RedString& outputName);
    static bool               ReadContent   (RedBufferInput& inputBuf, RedString& outputContent);
    static bool               ReadTmlElement(RedBufferInput& inputBuf, RedTinyMLElement** newTml);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
