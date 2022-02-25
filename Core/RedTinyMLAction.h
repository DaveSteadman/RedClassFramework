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

/// Class exists to provide complex actions on Core nodes. The Core node classes remain focussed
/// on their role of storage and memory management, while this class can acquire increasingly complex
/// bulky routines.
class RedTinyMLAction
{
public:

    // Set & Query Leaf elements
    static void               SetChildLeaf   (RedTinyMLNode& node, const RedDataString& leafname, const RedDataString& leafdata);
    static bool               ChildLeafExists(RedTinyMLNode& node, const RedDataString& leafname);

    // Leaf Name<->Data lookups
    static RedResult          ChildLeafDataForName(RedTinyMLNode& node, const RedDataString& inleafname, RedDataString& outleafdata);
    static RedResult          ChildLeafNameForData(RedTinyMLNode& node, const RedDataString& inleafdata, RedDataString& outleafname);

    // Search Node For Child entries
    static RedTinyMLElement*  NodeFirstNamedElement   (RedTinyMLNode& node, const RedDataString& SearchName);
    static RedTinyMLNode*     NodeFirstNamedNode      (RedTinyMLNode& node, const RedDataString& SearchName);
    static RedTinyMLLeaf*     NodeFirstNamedLeaf      (RedTinyMLNode& node, const RedDataString& SearchName);
    static unsigned           NumberOfNamedChildLeaves(RedTinyMLNode& node, const RedDataString& SearchName);

    // Tree Query
    static unsigned           TreeElementCount(RedTinyMLNode& node);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
