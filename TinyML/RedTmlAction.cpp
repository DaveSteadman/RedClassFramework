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

static const RedChar kOpenBracket  = '{';
static const RedChar kCloseBracket = '}';

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
// Top Level IO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTmlAction::CreateTmlFromFile(const RedString& filepath, RedTmlElement** newTmlElement)
{
    // Initialisation
    if (*newTmlElement != NULL)
    {
        delete *newTmlElement;
        *newTmlElement = NULL;
    }

    // Check the file exists to open
    if (!RedIOHandler::FileExists(filepath))
        return kResultFail;

    // Open the file and copy into input buffer
    RedBufferInput iB;
    if (RedIOHandler::InputBufferFromFile(filepath, iB) == kResultFail)
        return kResultFail;

    // Parse the file to create TML Element
    *newTmlElement = RedTmlAction::ParseTinyML(iB);
    if (*newTmlElement == NULL)
        return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTmlAction::CreateFileFromTml(const RedTmlElement* tmlElement, const RedString& filepath, const TESerialiseType writeStyle)
{
    // Check node is not null
    if (tmlElement == NULL)
        return kResultFail;

    // Write the validated tml node to the buffer
    RedBufferOutput outBuf;
    RedTmlAction::SerialiseTinyML(outBuf, tmlElement, writeStyle);

    // Final newline for asthetics
    outBuf.WriteNewLine();

    // Write buffer to file
    if (RedIOHandler::OutputBufferToFile(filepath, outBuf) != kResultSuccess)
        return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlElement* RedTmlAction::ParseTinyML(const RedString& inputStr)
{
    RedBufferInput inputBuf(inputStr);

    return RedTmlAction::ParseTinyML(inputBuf);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlElement* RedTmlAction::ParseTinyML(RedBufferInput& inputBuf)
{
    RedTmlElement* retTml = NULL;

    if ( ReadTmlElement(inputBuf, &retTml) )
        return retTml;

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTmlAction::SerialiseTinyML(RedBufferOutput& outputBuf, const RedTmlElement* topTmlNode, const TESerialiseType eMode)
{
    outputBuf.Append(kOpenBracket);

    // write name
    outputBuf.Append(kOpenBracket);
    outputBuf.Append(topTmlNode->Name());
    outputBuf.Append(kCloseBracket);

    if (topTmlNode->IsNode())
    {
        RedTmlNode* pCurrNode = (RedTmlNode*)topTmlNode;

        RedTmlNode::TmlNodeListItType ListIt = pCurrNode->NodeIterator();

        if (eMode == eLinedIndentedContent) outputBuf.IncreaseIndent();

        while (!ListIt.IsDone())
        {
            RedTmlElement* nextElem = ListIt.CurrentItem();

            if (eMode == eLinedIndentedContent) outputBuf.WriteNewLineWithIndent();

            RedTmlAction::SerialiseTinyML(outputBuf, nextElem, eMode);

            ListIt.Next();
        }

        if (eMode == eLinedIndentedContent)
        {
            outputBuf.DecreaseIndent();
            outputBuf.WriteNewLineWithIndent();
        }
    }
    else if (topTmlNode->IsLeaf())
    {
        RedTmlLeaf* pCurrLeaf = (RedTmlLeaf*)topTmlNode;
        if (pCurrLeaf->Data().NumLines() > 1)
        {
            outputBuf.IncreaseIndent();
            outputBuf.AppendIndented(pCurrLeaf->Data());
            outputBuf.DecreaseIndent();
            outputBuf.WriteNewLineWithIndent();
        }
        else
        {
            outputBuf.Append(pCurrLeaf->Data());
        }
    }

    outputBuf.Append(kCloseBracket);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTmlAction::ReadName(RedBufferInput& inputBuf, RedString& outputName)
{
    RedChar ch;
    outputName.Empty();

    // second bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != kOpenBracket) return false;
    if (ch.IsEOF())   return false;

    // read name
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;
    while (ch != kCloseBracket)
    {
        outputName.Append(ch);
        ch = inputBuf.GetNextChar();
        if (ch.IsEOF()) return false;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTmlAction::ReadContent(RedBufferInput& inputBuf, RedString& outputContent)
{
    bool EndOfContentFound = false;
    RedString levelChars;

    // Initialse the return data
    outputContent.Empty();

    // Skip whitespace
    RedChar ch = inputBuf.PreviewNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;

    // Loop until EOF or unquoted close bracket
    while(!EndOfContentFound)
    {
        RedChar ch = inputBuf.GetNextChar();

        // check for obvious invalid characters
        if (ch.IsEOF()) return false;

        // check for a quote level changes
        if ((ch.IsQuote()) && (ch != levelChars.LastChar())) levelChars.Append(ch);
        if ((ch.IsQuote()) && (ch == levelChars.LastChar())) levelChars.DelLastChar();

        // check for final close bracket
        if ( (ch == kCloseBracket) && (levelChars.IsEmpty()) )
        {
            inputBuf.UngetChar();
            return true;
        }
        else
        {
            outputContent.Append(ch);
        }
    }

    // default error return value
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTmlAction::ReadTmlElement(RedBufferInput& inputBuf, RedTmlElement** newTml)
{
    RedChar   ch;
    RedString leafname;

    // Opening bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != kOpenBracket) return false;
    if (ch.IsEOF())         return false;
    
    // Read the name
    if ( !RedTmlAction::ReadName(inputBuf, leafname) ) return false;

    // If the next character is {, its a collection
    ch = inputBuf.PreviewNextNonWhitespaceChar();

    if (ch == kOpenBracket)
    {
        RedTmlNode* newNode = new RedTmlNode(leafname);

        // Move onto the next non-whitespace character
        ch = inputBuf.PreviewNextNonWhitespaceChar();

        // Check we are starting the object correctly.
        if (ch != kOpenBracket)
        {
            delete newNode;
            return false;
        }

        // Iterate across the Tml entries
        while (ch == kOpenBracket)
        {
            RedTmlElement* newChildNode;
            
            if ( RedTmlAction::ReadTmlElement(inputBuf, &newChildNode) )
                newNode->NodeList()->AddLast(newChildNode);

             ch = inputBuf.PreviewNextNonWhitespaceChar();
        }

        // Read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == kCloseBracket)
        {
            *newTml = dynamic_cast<RedTmlElement*>(newNode);
            return true;
        }
        else
        {
            delete newNode;
            return false;
        }
    }
    else
    {
        RedString   leafdata;
        RedTmlLeaf* newLeaf;

        // Attempt to read the content
        if (!RedTmlAction::ReadContent(inputBuf, leafdata))
            return false;

        // Read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == kCloseBracket)
        {
            // All read, construct returned object
            newLeaf = new RedTmlLeaf(leafname, leafdata);

            *newTml = dynamic_cast<RedTmlElement*>(newLeaf);
            return true;
        }
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red

