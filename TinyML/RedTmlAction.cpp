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

namespace Red {
namespace TinyML {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedChar openbr  = '{';
static const RedChar closebr = '}';

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

    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlNode* RedTmlAction::NodeFirstNamedNode(RedTmlNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTmlElement* pElem = RedTmlAction::NodeFirstNamedElement(node, SearchName);

    // work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsNode()))
        return (RedTmlNode*)pElem;

    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlLeaf* RedTmlAction::NodeFirstNamedLeaf(RedTmlNode& node, const RedString& SearchName)
{
    // Basic search for the first matching element
    RedTmlElement* pElem = RedTmlAction::NodeFirstNamedElement(node, SearchName);

    // Work out the type and if we have a match without extra logic
    if ((pElem) && (pElem->IsLeaf()))
        return (RedTmlLeaf*)pElem;

    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedTmlAction::ChildLeafExists(RedTmlNode& node, const RedString& leafname)
{
    RedTmlLeaf* l = RedTmlAction::NodeFirstNamedLeaf(node, leafname);

    if (l)
        return 1;
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTmlAction::SetChildLeaf(RedTmlNode& node, const RedString& leafname, const RedString& leafdata)
{
    // look for the named child leaf
    RedTmlLeaf* l = RedTmlAction::NodeFirstNamedLeaf(node, leafname);

    // set the leaf if we found it
    if (l)
    {
        l->SetData(leafdata);
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
    RedTmlLeaf* l = RedTmlAction::NodeFirstNamedLeaf(node, inleafname);
    if (l == REDNULL)
        return kResultFail;

    outleafdata = l->Data();
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
            RedTmlLeaf* l = (RedTmlLeaf*)e;

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

const int RedTmlAction::NumberOfNamedChildLeaves(RedTmlNode& node, const RedString& SearchName)
{
    RedTmlNode::TmlNodeListItType it = node.NodeIterator();
    int matchcount = 0;

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

const unsigned RedTmlAction::TreeElementCount(RedTmlNode& node)
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
            RedTmlNode* pNextNode = (RedTmlNode*)pCurrElem;
            currNodeCount += RedTmlAction::TreeElementCount(*pNextNode);
        }
        yIt.Next();
    }

    return currNodeCount;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma mark - Top Level IO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedResult RedTmlAction::CreateTmlFromFile(const RedString& filepath, RedTmlElement** newTmlElement)
{
    // Initialisation
    if (*newTmlElement != REDNULL)
    {
        delete *newTmlElement;
        *newTmlElement = REDNULL;
    }

    // Check the file exists to open
    if (Core::RedIOHandler::FileExists(filepath) == kResultFail)
        return kResultFail;

    // Open the file and copy into input buffer
    RedBufferInput iB;
    if (RedIOHandler::InputBufferFromFile(filepath, iB) == kResultFail)
        return kResultFail;

    // Parse the file to create TML Element
    *newTmlElement = RedTmlAction::ParseTinyML(iB);
    if (*newTmlElement == REDNULL)
        return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const RedResult RedTmlAction::CreateFileFromTml(const RedTmlElement* tmlElement, const RedString& filepath, const TESerialiseType writeStyle)
{
    // Check node is not null
    if (tmlElement == REDNULL)
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

RedTmlElement* RedTmlAction::ParseTinyML(RedBufferInput& inputBuf)
{
    RedTmlElement* retTml = REDNULL;

    if( ReadTmlElement(inputBuf, &retTml) )
        return retTml;

    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTmlAction::SerialiseTinyML(RedBufferOutput& outputBuf, const RedTmlElement* topTmlNode, const TESerialiseType eMode)
{
    outputBuf.Append(openbr);

    // write name
    outputBuf.Append(openbr);
    outputBuf.Append(topTmlNode->Name());
    outputBuf.Append(closebr);

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

    outputBuf.Append(closebr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma mark - Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTmlAction::ReadName(RedBufferInput& inputBuf, RedString& outputName)
{
    RedChar ch;
    outputName.Empty();

    // second bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != openbr) return false;
    if (ch.IsEOF()) return false;

    // read name
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;
    while (ch != closebr)
    {
        outputName.Append(ch);
        ch = inputBuf.GetNextChar();
        if (ch.IsEOF()) return false;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedTmlAction::ReadContent(RedBufferInput& inputBuf, RedString& outputContent)
{
    bool EndOfContentFound = false;
    RedString levelChars;

    outputContent.Empty();

    RedChar ch = inputBuf.PreviewNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;

    while(!EndOfContentFound)
    {
        RedChar ch = inputBuf.GetNextChar();

        // check for obvious invalid characters
        if (ch.IsEOF()) return false;

        // check for a quote level changes
        if ((ch.IsQuote()) && (ch != levelChars.LastChar())) levelChars.Append(ch);
        if ((ch.IsQuote()) && (ch == levelChars.LastChar())) levelChars.DelLastChar();

        // check for final close bracket
        if ( (ch == closebr) && (levelChars.IsEmpty()) )
        {
            inputBuf.UngetChar();
            //EndOfContentFound = true;
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

int RedTmlAction::ReadTmlElement(RedBufferInput& inputBuf, RedTmlElement** newTml)
{
    RedChar   ch;
    RedString leafname;
    //RedTmlLeaf* newleaf;

    // opening bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != openbr) return false;
    if (ch.IsEOF()) return false;
    
    // read the name
    if ( !RedTmlAction::ReadName(inputBuf, leafname) ) return false;

    // if the next character is {, its a collection
    ch = inputBuf.PreviewNextNonWhitespaceChar();

    if (ch == openbr)
    {
        RedTmlNode* newNode = new RedTmlNode(leafname);

        // move onto the next non-whitespace character
        ch = inputBuf.PreviewNextNonWhitespaceChar();

        // check we are starting the object correctly.
        if (ch != openbr)
        {
            delete newNode;
            return 0;
        }

        // Iterate across the Tml entries
        while (ch == openbr)
        {
            RedTmlElement* newChildNode;
            
            if ( RedTmlAction::ReadTmlElement(inputBuf, &newChildNode) )
                newNode->NodeList()->AddLast(newChildNode);

             ch = inputBuf.PreviewNextNonWhitespaceChar();
        }

        // read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == closebr)
        {
            *newTml = (RedTmlElement*)newNode;
            return 1;
        }
        else
        {
            delete newNode;
            return 0;
        }
    }
    else
    {
        RedString leafdata;
        RedTmlLeaf* newLeaf;

        // Attempt to read the content
        if (!RedTmlAction::ReadContent(inputBuf, leafdata))
            return 0;

        // read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == closebr)
        {
            // All read, construct returned object
            newLeaf = new RedTmlLeaf(leafname, leafdata);

            *newTml = (RedTmlElement*)newLeaf;
            return 1;
        }
    }

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red

