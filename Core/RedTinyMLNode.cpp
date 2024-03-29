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
#include "RedTinyMLNode.h"
#include "RedTinyMLElement.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLNode::~RedTinyMLNode()
{
    RedTinyMLNode* pCurrNode = 0;
    
    // Loop until the list is empty
    while (!this->elemlist.IsEmpty())
    {
        this->elemlist.DelLast();
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLNode* RedTinyMLNode::CreateChildNode(const RedDataString& NewName)
{
    RedTinyMLNode* pNewNode = new RedTinyMLNode(NewName);
    this->elemlist.AddLast(dynamic_cast<RedTinyMLElement*>(pNewNode));

    return pNewNode;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLLeaf* RedTinyMLNode::CreateChildLeaf(const RedDataString& NewName, const RedDataString& NewData)
{
    RedTinyMLLeaf *NewLeaf = new RedTinyMLLeaf(NewName, NewData);

    this->elemlist.AddLast(dynamic_cast<RedTinyMLElement*>(NewLeaf));
    return NewLeaf;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


