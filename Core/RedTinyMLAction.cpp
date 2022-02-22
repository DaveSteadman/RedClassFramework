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

#include "RedTinyMLAction.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedTinyMLAction::NodeFirstNamedElement(RedTinyMLNode& node, const RedString& SearchName)
{
    Core::RedTinyMLNode::TmlNodeListItType yIt = node.NodeIterator();
    yIt.First();
    while (!yIt.IsDone())
    {
        RedTinyMLElement* pCurrElem = yIt.CurrentItem();

        if (pCurrElem->Name() == SearchName)
            return pCurrElem;
        yIt.Next();
    }

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLNode* RedTinyMLAction::NodeFirstNamedNode(RedTinyMLNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTinyMLElement* pElem = RedTinyMLAction::NodeFirstNamedElement(node, SearchName);

    // work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsNode()))
        return dynamic_cast<RedTinyMLNode*>(pElem);

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLLeaf* RedTinyMLAction::NodeFirstNamedLeaf(RedTinyMLNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTinyMLElement* pElem = RedTinyMLAction::NodeFirstNamedElement(node, SearchName);

    // Work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsLeaf()))
        return dynamic_cast<RedTinyMLLeaf*>(pElem);

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTinyMLAction::ChildLeafExists(RedTinyMLNode& node, const RedString& leafname)
{
    RedTinyMLLeaf* leafnode = RedTinyMLAction::NodeFirstNamedLeaf(node, leafname);

    if (leafnode)
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTinyMLAction::SetChildLeaf(RedTinyMLNode& node, const RedString& leafname, const RedString& leafdata)
{
    // look for the named child leaf
    RedTinyMLLeaf* leafnode = RedTinyMLAction::NodeFirstNamedLeaf(node, leafname);

    // set the leaf if we found it
    if (leafnode)
    {
        leafnode->SetData(leafdata);
    }
    // create and assign the data if we didn't
    else
    {
        node.CreateChildLeaf(leafname, leafdata);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTinyMLAction::ChildLeafDataForName(RedTinyMLNode& node, const RedString& inleafname, RedString& outleafdata)
{
    RedTinyMLLeaf* leafnode = RedTinyMLAction::NodeFirstNamedLeaf(node, inleafname);
    if (leafnode == NULL)
        return kResultFail;

    outleafdata = leafnode->Data();
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTinyMLAction::ChildLeafNameForData(RedTinyMLNode& node, const RedString& inleafdata, RedString& outleafname)
{
    RedTinyMLNode::TmlNodeListItType it = node.NodeIterator();

    it.First();
    while(!it.IsDone())
    {
        RedTinyMLElement* e = it.CurrentItem();

        if (e->IsLeaf())
        {
            RedTinyMLLeaf* l = dynamic_cast<RedTinyMLLeaf*>(e);

            if (l->Data() == inleafdata)
            {
                outleafname = l->Name();
                return kResultSuccess;
            }
        }
        it.Next();
    }
    return kResultFail;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedTinyMLAction::NumberOfNamedChildLeaves(RedTinyMLNode& node, const RedString& SearchName)
{
    RedTinyMLNode::TmlNodeListItType it = node.NodeIterator();
    unsigned matchcount = 0;

    it.First();
    while(!it.IsDone())
    {
        RedTinyMLElement* e = it.CurrentItem();

        if ((e->IsLeaf()) && (e->Name() == SearchName))
        {
            matchcount++;
        }

        it.Next();
    }

    return matchcount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedTinyMLAction::TreeElementCount(RedTinyMLNode& node)
{
    // 1 = starting node.
    unsigned currNodeCount = 1;

    Core::RedTinyMLNode::TmlNodeListItType yIt = node.NodeIterator();
    yIt.First();
    while (!yIt.IsDone())
    {
        RedTinyMLElement* pCurrElem = yIt.CurrentItem();

        if (pCurrElem->IsLeaf())
        {
            currNodeCount++;
        }
        else if (pCurrElem->IsNode())
        {
            RedTinyMLNode* pNextNode = dynamic_cast<RedTinyMLNode*>(pCurrElem);
            currNodeCount += RedTinyMLAction::TreeElementCount(*pNextNode);
        }
        yIt.Next();
    }

    return currNodeCount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

