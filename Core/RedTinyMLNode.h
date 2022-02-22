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
#include "RedTinyMLElement.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTinyMLNode : public RedTinyMLElement
{
public:

    typedef RedDoubleLinkedList<RedTinyMLElement*>         TmlNodeListType;
    typedef RedDoubleLinkedListIterator<RedTinyMLElement*> TmlNodeListItType;

    // Constructor
    RedTinyMLNode(const RedString& NewName) : RedTinyMLElement(NewName) { nodelist.Init(); };
    
    // Destructor - delete all items in list
    ~RedTinyMLNode();

    // Basic Queries
    bool     IsNode(void)           const { return true; };
    unsigned NodeElementCount(void) const { return nodelist.NumItems(); };

    // List an list-iterator accessors
    TmlNodeListType*  NodeList(void)     { return &nodelist; };
    TmlNodeListItType NodeIterator(void) { return TmlNodeListItType(&nodelist); };

    // Create child elements within the tree and return a pointer to them
    RedTinyMLNode*    CreateChildNode (const RedString& NewName);
    RedTinyMLLeaf*    CreateChildLeaf (const RedString& NewName, const RedString& NewData);

    // Add new child nodes without cloning
    void AddChildNode (RedTinyMLNode* pNewNode) { nodelist.AddLast(dynamic_cast<RedTinyMLElement*>(pNewNode)); };
    void AddChildLeaf (RedTinyMLLeaf* pNewLeaf) { nodelist.AddLast(dynamic_cast<RedTinyMLElement*>(pNewLeaf)); };

private:
    TmlNodeListType nodelist;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


