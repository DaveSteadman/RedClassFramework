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

#include "RedTmlAction.h"

using namespace Red::Core;

namespace Red {
namespace TinyML {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlElement* RedTmlAction::NodeFirstNamedElement(RedTmlNode& node, const RedString& SearchName)
{
    TinyML::RedTmlNode::TmlNodeListItType yIt = node.NodeIterator();
    yIt.First();
    while (!yIt.IsDone())
    {
        RedTmlElement* pCurrElem = yIt.CurrentItem();

        if (pCurrElem->Name() == SearchName)
            return pCurrElem;
        yIt.Next();
    }

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlNode* RedTmlAction::NodeFirstNamedNode(RedTmlNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTmlElement* pElem = RedTmlAction::NodeFirstNamedElement(node, SearchName);

    // work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsNode()))
        return dynamic_cast<RedTmlNode*>(pElem);

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlLeaf* RedTmlAction::NodeFirstNamedLeaf(RedTmlNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTmlElement* pElem = RedTmlAction::NodeFirstNamedElement(node, SearchName);

    // Work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsLeaf()))
        return dynamic_cast<RedTmlLeaf*>(pElem);

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTmlAction::ChildLeafExists(RedTmlNode& node, const RedString& leafname)
{
    RedTmlLeaf* leafnode = RedTmlAction::NodeFirstNamedLeaf(node, leafname);

    if (leafnode)
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTmlAction::SetChildLeaf(RedTmlNode& node, const RedString& leafname, const RedString& leafdata)
{
    // look for the named child leaf
    RedTmlLeaf* leafnode = RedTmlAction::NodeFirstNamedLeaf(node, leafname);

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

RedResult RedTmlAction::ChildLeafDataForName(RedTmlNode& node, const RedString& inleafname, RedString& outleafdata)
{
    RedTmlLeaf* leafnode = RedTmlAction::NodeFirstNamedLeaf(node, inleafname);
    if (leafnode == NULL)
        return kResultFail;

    outleafdata = leafnode->Data();
    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTmlAction::ChildLeafNameForData(RedTmlNode& node, const RedString& inleafdata, RedString& outleafname)
{
    RedTmlNode::TmlNodeListItType it = node.NodeIterator();

    it.First();
    while(!it.IsDone())
    {
        RedTmlElement* e = it.CurrentItem();

        if (e->IsLeaf())
        {
            RedTmlLeaf* l = dynamic_cast<RedTmlLeaf*>(e);

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

unsigned RedTmlAction::NumberOfNamedChildLeaves(RedTmlNode& node, const RedString& SearchName)
{
    RedTmlNode::TmlNodeListItType it = node.NodeIterator();
    unsigned matchcount = 0;

    it.First();
    while(!it.IsDone())
    {
        RedTmlElement* e = it.CurrentItem();

        if ((e->IsLeaf()) && (e->Name() == SearchName))
        {
            matchcount++;
        }

        it.Next();
    }

    return matchcount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedTmlAction::TreeElementCount(RedTmlNode& node)
{
    // 1 = starting node.
    unsigned currNodeCount = 1;

    TinyML::RedTmlNode::TmlNodeListItType yIt = node.NodeIterator();
    yIt.First();
    while (!yIt.IsDone())
    {
        RedTmlElement* pCurrElem = yIt.CurrentItem();

        if (pCurrElem->IsLeaf())
        {
            currNodeCount++;
        }
        else if (pCurrElem->IsNode())
        {
            RedTmlNode* pNextNode = dynamic_cast<RedTmlNode*>(pCurrElem);
            currNodeCount += RedTmlAction::TreeElementCount(*pNextNode);
        }
        yIt.Next();
    }

    return currNodeCount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red

