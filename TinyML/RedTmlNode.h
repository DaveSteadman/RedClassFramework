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

/*
  {{name} qwqwq }
  {{name} "asad }}" }
*/

#pragma once

// Include Namespaces
#include "RedCoreNamespace.h"

#include "RedTmlElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

using namespace Red::Core;

namespace Red {
namespace TinyML {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTmlNode : public RedTmlElement
{
public:

    typedef RedDoubleLinkedList<RedTmlElement*>         TmlNodeListType;
    typedef RedDoubleLinkedListIterator<RedTmlElement*> TmlNodeListItType;

    // Constructor
    RedTmlNode(const RedString& NewName) : RedTmlElement(NewName) { nodelist.Init(); };

    // Basic Queries
    const bool     IsNode(void)           const { return true; };
    const unsigned NodeElementCount(void) const { return nodelist.NumItems(); };

    // List an list-iterator accessors
    TmlNodeListType*  NodeList(void)     { return &nodelist; };
    TmlNodeListItType NodeIterator(void) { return TmlNodeListItType(&nodelist); };

    // Create child elements within the tree and return a pointer to them
    RedTmlNode*    CreateChildNode (const RedString& NewName);
    RedTmlLeaf*    CreateChildLeaf (const RedString& NewName, const RedString& NewData);

    // Add new child nodes without cloning
    void AddChildNode (RedTmlNode* pNewNode) { nodelist.AddLast((RedTmlElement*)pNewNode); };
    void AddChildLeaf (RedTmlLeaf* pNewLeaf) { nodelist.AddLast((RedTmlElement*)pNewLeaf); };

private:
    TmlNodeListType nodelist;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red


