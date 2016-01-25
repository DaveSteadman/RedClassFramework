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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"
#include "RedTmlNamespace.h"

namespace Red {
namespace TinyML {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef enum TESerialiseType { eDenseContent, eLinedIndentedContent } TESerialiseType;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/// Class exists to provide complex actions on TinyML nodes. The TinyML node classes remain focussed
/// on their role of storage and memory management, while this class can acquire increasingly complex
/// bulky routines.
class RedTmlAction
{
public:

    // Set & Query Leaf elements
    static void            SetChildLeaf   (RedTmlNode& node, const RedString& leafname, const RedString& leafdata);
    static const int       ChildLeafExists(RedTmlNode& node, const RedString& leafname);

    // Leaf Name<->Data lookups
    static RedResult       ChildLeafDataForName(RedTmlNode& node, const RedString& inleafname, RedString& outleafdata);
    static RedResult       ChildLeafNameForData(RedTmlNode& node, const RedString& inleafdata, RedString& outleafname);

    // Search Node For Child entries
    static RedTmlElement*  NodeFirstNamedElement   (RedTmlNode& node, const RedString& SearchName);
    static RedTmlNode*     NodeFirstNamedNode      (RedTmlNode& node, const RedString& SearchName);
    static RedTmlLeaf*     NodeFirstNamedLeaf      (RedTmlNode& node, const RedString& SearchName);
    static const int       NumberOfNamedChildLeaves(RedTmlNode& node, const RedString& SearchName);

    // Tree Query
    static const unsigned  TreeElementCount(RedTmlNode& node);

    // IO
    static const RedResult CreateTmlFromFile(const RedString& filepath, RedTmlElement** newTmlElement);
    static const RedResult CreateFileFromTml(const RedTmlElement* tmlElement, const RedString& filepath, const TESerialiseType writeStyle);
    static RedTmlElement*  ParseTinyML(RedBufferInput& inputBuf);
    static void            SerialiseTinyML(RedBufferOutput& outputBuf, const RedTmlElement* topTmlNode, const TESerialiseType eMode);

private:
    static int ReadName      (RedBufferInput& inputBuf, RedString& outputName);
    static int ReadContent   (RedBufferInput& inputBuf, RedString& outputContent);
    static int ReadTmlElement(RedBufferInput& inputBuf, RedTmlElement** newTml);

};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red
